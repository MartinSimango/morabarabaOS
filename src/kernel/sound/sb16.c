#include "sb16.h"
#include "idt.h"
#include "io.h"
#include "math.h"
#include "memory.h"
#include "status.h"
#include "timer.h"
#include "tty.h"

#define DSP_RESET 0x06
#define DSP_DATAAVAIL 0x0E
#define DSP_DATA 0x0A
#define DSP_WRITE 0x0C
#define DSP_READ 0x0A

#define DSP_START_DAC_8 0x14 // DMA Mode
#define DSP_START_ADC_8 0x24 // DMA Mode
#define DSP_SET_BLOCK_SIZE 0x48

#define DSP_SET_TIME_CONSTANT 0x40
#define DSP_SET_RATE 0x41
#define DSP_SPEAKER_ON 0xD1
#define DSP_SPEAKER_OFF 0xD3
#define DSP_PAUSE_DMA_8 0xD0
#define DSP_CONTINUE_DMA_8 0xD4
#define DSP_PAUSE_DMA_16 0xD5
#define DSP_CONTINUE_DMA_16 0xD6
#define DSP_STOP_END_OF_BLOCK 0xD9
#define DSP_VERSION 0xE1

#define DSP_MIXER_PORT 0x224
#define DSP_MIXER_DATA_PORT 0x225
#define DSP_SET_MASTER_VOLUME 0x22
#define DSP_SET_IRQ 0x80
#define DSP_IRQ 0x02 // this corresponds to IRQ 5

// using channel 5 from DMAC-2 (16-bit) chip
#define DMA_CHANNEL_16 5
#define DMA_WRITE_SINGLE_MASK 0xD4
#define DMA_CHANNEL_ADDRESS 0xC4
#define DMA_COUNT_PORT 0xC6
#define DMA_PAGE_REGISTER 0x8B

#define DMA_WRITE_MODE 0xD6
#define DMA_FLIP_FLOP 0xD8

#define DMA_ENABLE_CHANNEL 0x00  // 0b000
#define DMA_DISABLE_CHANNEL 0x04 // 0b100

// TOdo: need to inspect
#define DMA_SINGLE_CYCLE_PLAYBACK_MODE 0x48
#define DMA_AUTO_INITIALIZED_PLAYBACK_MODE 0x58

#define DSP_PROG_16 0xB0
#define DSP_PROG_8 0xC0
#define DSP_AUTO_INIT 0x06
#define DSP_PLAY 0x00
#define DSP_RECORD 0x08
#define DSP_MONO 0x00
#define DSP_STEREO 0x20
#define DSP_UNSIGNED 0x00
#define DSP_SIGNED 0x10
#define DSP_ACK_16 0x22F

void extern int25h_sound();

int16 sb16_sound_buffer[BUFFER_SIZE];

static uint8 bufferflip = 0;
static float64 sample_scale = 10000;

void fill(int16 *buf, uint16 len) {
  for (int i = 0; i < len; i++) {
    float64 val = 0;
    for (int n = 0; n < sb16_card.notes_length; n++) {
      // if (i==0){
      // tty_print_default(" ");
      // tty_print_int_default(sb16_card.notes[n].freq);
      // }
      Note *note = &sb16_card.notes[n];
      // if(note->volume == 0) {

      //}
      val += music_get_sample(*note, SAMPLE_RATE, note->volume, sample_scale);
      note->sample_count += (1.0 / sample_scale);
      if (note->sample_count > SAMPLE_RATE / note->freq) {
        note->sample_count = 0;
      }
    }

    int16 total = (int16)(val * 255);
    buf[i] = total;
  }
}

void int25h_sound_handler() {
  bufferflip = !bufferflip;
  fill(&sb16_sound_buffer[bufferflip ? 0 : (BUFFER_SIZE / 2)],
       (BUFFER_SIZE / 2));
  insb(DSP_ACK_16);
  irq_end_of_interrupt();
}

void sb16_init() {

  fill(sb16_sound_buffer, BUFFER_SIZE);

  // reset DSP
  sb16_DSP_reset();

  tty_print_default("\nSound blaster 16 sound card is present!\n");

  // SET IRQ
  outb(DSP_MIXER_PORT, DSP_SET_IRQ);
  outb(DSP_MIXER_DATA_PORT, DSP_IRQ);

  outb(DSP_MIXER_PORT, 0x22);
  outb(DSP_MIXER_DATA_PORT, 0x00);

  // program DMA
  sb16_program_DMA_16(sb16_sound_buffer, BUFFER_SIZE);

  // set sample rate
  sb16_DSP_set_sample_rate(SAMPLE_RATE);

  // Write command
  sb16_DSP_write(DSP_PROG_16 | DSP_PLAY | DSP_AUTO_INIT);

  // Write mode
  sb16_DSP_write(DSP_SIGNED | DSP_MONO);

  // write block size
  uint16 block_size = (BUFFER_SIZE / 2) - 1;
  sb16_DSP_write(low_byte(block_size));
  sb16_DSP_write(high_byte(block_size));

  // turn speaker on
  // does this even need to be there?
  sb16_DSP_write(DSP_SPEAKER_ON);
  sb16_DSP_write(DSP_CONTINUE_DMA_16);
}

static uint8 sb16_check_DSP_base_port(uint16 base) {
  uint16 dsp_reset_port = base + DSP_RESET;
  uint16 dsp_data_available = base + DSP_DATAAVAIL;
  uint16 dsp_data_read = base + DSP_READ;

  outb(dsp_reset_port, 1);
  timer_sleep(1);
  outb(dsp_reset_port, 0);
  timer_sleep(1);

  if (insb(dsp_data_available) & 0x80 && insb(dsp_data_read) == 0xAA) {
    sb16_card.dsp_base_port = base;
    sb16_card.dsp_write_port = base + DSP_WRITE;
    sb16_card.dsp_read_port = dsp_data_read;
    sb16_card.dsp_read_status_port = dsp_data_available;
    return 0;
  }
  return -ENOSOUND;
}

void sb16_DSP_reset() {
  int8 error_num = -ENOSOUND;

  for (uint8 i = 0; i < DSP_BASE_PORTS_NUM; i++) {
    error_num = sb16_check_DSP_base_port(DSP_BASE_PORTS[i]);
    if (error_num == 0) {
      return;
    }
  }

  if (error_num < 0) {
    tty_kernel_panic(error_num * -1);
  }
}

void sb16_DSP_write(uint8 byte) {
  while (insb(sb16_card.dsp_write_port) & 0x80)
    ;
  outb(sb16_card.dsp_write_port, byte);
}

uint8 sb16_DSP_read() {
  while (!(insb(sb16_card.dsp_read_status_port) & 0x80))
    ;
  return insb(sb16_card.dsp_read_port);
}

void sb16_DSP_set_sample_rate(uint16 hz) {
  sb16_DSP_write(DSP_SET_RATE);
  sb16_DSP_write(high_byte(hz));
  sb16_DSP_write(low_byte(hz));
}

void sb16_program_DMA_16(void *buf, uint16 buffer_len) {

  // disable DMA channel
  outb(DMA_WRITE_SINGLE_MASK, (DMA_CHANNEL_16 % 4) | DMA_DISABLE_CHANNEL);

  // Clear the byte pointer flip-flop
  outb(DMA_FLIP_FLOP, 1);

  // Write the DMA mode for the transfer
  outb(DMA_WRITE_MODE,
       DMA_AUTO_INITIALIZED_PLAYBACK_MODE | (DMA_CHANNEL_16 % 4));

  uint16 offset = (((uint32)buf) / 2) % 65536;

  // Write buffer offset to base address (low bit followed by high bit)
  outb(DMA_CHANNEL_ADDRESS, low_byte(offset));
  outb(DMA_CHANNEL_ADDRESS, high_byte(offset));

  // Write buffer length -1 to count address
  outb(DMA_COUNT_PORT, low_byte(buffer_len - 1));
  outb(DMA_COUNT_PORT, high_byte(buffer_len - 1));

  // Write buffer page to page address
  uint16 page = ((uint32)(buf)) >> 16;
  outw(DMA_PAGE_REGISTER, page);

  // enable DMA channel
  outb(DMA_WRITE_SINGLE_MASK, DMA_ENABLE_CHANNEL | (DMA_CHANNEL_16 % 4));
}

void sb16_pause_sound() { sb16_DSP_write(DSP_PAUSE_DMA_16); }

void sb16_play_sound() { sb16_DSP_write(DSP_CONTINUE_DMA_16); }

void sb16_set_notes(Note *notes, uint8 len) {
  // memset(sb16_card.notes, 0, sizeof(sb16_card.notes));
  sb16_card.notes = notes;
  // memcpy(sb16_card.notes, notes, len * sizeof(Note));
  sb16_card.notes_length = len;
}

uint16 sb16_set_samples(int16 *samples, uint16 buffer_len) {

  memset(sb16_card.samples, 0, sizeof(sb16_card.samples));
  // copy min of buffer_len and buffer
  memcpy(sb16_card.samples, samples, (size_t)min(buffer_len, BUFFER_SIZE));

  return min(buffer_len, BUFFER_SIZE);
}

struct sb16 get_sb16_card() {
  return sb16_card;
}