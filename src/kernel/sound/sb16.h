#ifndef _SB16_H_
#define _SB16_H_

#include "notes.h"
#include "types.h"

#define SAMPLE_RATE 44100

#define BUFFER_SIZE 1324 //((size_t)(SAMPLE_RATE * (BUFFER_MS / 1000.0)))

static struct sb16 {
  uint16 dsp_base_port;
  uint16 dsp_read_port;
  uint16 dsp_write_port;
  uint16 dsp_read_status_port;
  int16 samples[BUFFER_SIZE];
  Note *notes;
  uint8 notes_length;
} sb16_card;

static bool sb16_supported = false;
// Possible DSP_BASE_PORT's:
// 0x220, 0x230, 0x240, 0x250, 0x260 or 0x280
static const uint16 DSP_BASE_PORTS[] = {0x220, 0x230, 0x240,
                                        0x250, 0x260, 0x280};

#define DSP_BASE_PORTS_NUM sizeof DSP_BASE_PORTS / sizeof DSP_BASE_PORTS[0]

// 1. Write a 1 to the reset port (2x6)
// 2. Wait for 3 microseconds
// 3. Write a 0 to the reset port (2x6)
// 4. Poll the read-buffer status port (2xE) until bit 7 is set 5. Poll the read
// data port (2xA) until you receive an AA

// todo have mode for samples or notes
void sb16_init();

void sb16_DSP_reset();

void sb16_DSP_write(uint8 byte);

uint8 sb16_DSP_read();

void sb16_program_DMA_16(void *buffer, uint16 buffer_len);

void sb16_DSP_set_sample_rate(uint16 hz);

void sb16_pause_sound();

void sb16_play_sound();

void sb16_set_notes(Note *notes, uint8 len);

uint16 sb16_set_samples(int16 *samples, uint16 buffer_len);

struct sb16 get_sb16_card();

bool is_sb16_supported();

int16 *get_buffer();

#endif