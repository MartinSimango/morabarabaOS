#ifndef _NOTES_H
#define _NOTES_H

#include "kheap.h"
#include "memory.h"
#include "types.h"

#define NUM_OCTAVES 7
#define OCTAVE_SIZE 12

#define NUM_NOTES NUM_OCTAVES *OCTAVE_SIZE

static const float64 NOTES[NUM_NOTES] = {
    // O1
    32.703195662574764,
    34.647828872108946,
    36.708095989675876,
    38.890872965260044,
    41.203444614108669,
    43.653528929125407,
    46.249302838954222,
    48.99942949771858,
    51.913087197493056,
    54.999999999999915,
    58.270470189761156,
    61.735412657015416,

    // O2
    65.406391325149571,
    69.295657744217934,
    73.416191979351794,
    77.781745930520117,
    82.406889228217381,
    87.307057858250872,
    92.4986056779085,
    97.998858995437217,
    103.82617439498618,
    109.99999999999989,
    116.54094037952237,
    123.4708253140309,

    // O3
    130.8127826502992,
    138.59131548843592,
    146.83238395870364,
    155.56349186104035,
    164.81377845643485,
    174.61411571650183,
    184.99721135581709,
    195.99771799087452,
    207.65234878997245,
    219.99999999999989,
    233.08188075904488,
    246.94165062806198,

    // O4
    261.62556530059851,
    277.18263097687202,
    293.66476791740746,
    311.12698372208081,
    329.62755691286986,
    349.22823143300383,
    369.99442271163434,
    391.99543598174927,
    415.30469757994513,
    440,
    466.16376151808993,
    493.88330125612413,

    // O5
    523.25113060119736,
    554.36526195374427,
    587.32953583481526,
    622.25396744416196,
    659.25511382574007,
    698.456462866008,
    739.98884542326903,
    783.99087196349899,
    830.60939515989071,
    880.00000000000034,
    932.32752303618031,
    987.76660251224882,

    // O6
    1046.5022612023952,
    1108.7305239074892,
    1174.659071669631,
    1244.5079348883246,
    1318.5102276514808,
    1396.9129257320169,
    1479.977690846539,
    1567.9817439269987,
    1661.2187903197821,
    1760.000000000002,
    1864.6550460723618,
    1975.5332050244986,

    // O7
    2093.0045224047913,
    2217.4610478149793,
    2349.3181433392633,
    2489.0158697766506,
    2637.020455302963,
    2793.8258514640347,
    2959.9553816930793,
    3135.9634878539991,
    3322.437580639566,
    3520.0000000000055,
    3729.3100921447249,
    3951.0664100489994,
};

typedef uint8 wave_type;

#define WAVE_SIN 0
#define WAVE_SQUARE 1
#define WAVE_TRIANGLE 2
#define WAVE_PIANO_1 3
#define WAVE_PIANO_2 4

extern uint8 NOTE_WAVE;
extern uint8 NOTE_VOLUME;

static inline void note_set_note_wave(uint8 wave) { NOTE_WAVE = wave; }

static inline void note_set_note_volume(uint8 volume) { NOTE_VOLUME = volume; }

static inline uint8 note_get_note_wave() { return NOTE_WAVE; }

static inline uint8 note_get_note_volume() { return NOTE_VOLUME; }

typedef struct Note {
  float64 freq;
  uint8 octave;
  uint8 offset;
  wave_type wave_type;
  float64 sample_count;
  uint8 volume;
  bool extended_note;
  uint8 extended_note_count;
  uint8 extended_note_index;

} Note;

static inline uint8 fix_octave(uint8 octave) {
  octave = octave > 6 ? 6 : octave;
  octave = octave < 1 ? 1 : octave;
  return octave;
}

static inline Note C_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12], octave, 0, wave, 0, volume};
}

static inline Note CSharp_Note(uint8 octave, wave_type wave, uint8 volume) {

  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 1], octave, 1, wave, 0, volume};
}

static inline Note D_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 2], octave, 2, wave, 0, volume};
}
static inline Note DSharp_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 3], octave, 3, wave, 0, volume};
}
static inline Note E_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 4], octave, 4, wave, 0, volume};
}
static inline Note F_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 5], octave, 5, wave, 0, volume};
}
static inline Note FSharp_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 6], octave, 6, wave, 0, volume};
}

static inline Note G_Note(uint8 octave, wave_type wave, uint8 volume) {

  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 7], octave, 7, wave, 0, volume};
}

static inline Note GSharp_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 8], octave, 8, wave, 0, volume};
}
static inline Note A_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 9], octave, 9, wave, 0, volume};
}

static inline Note ASharp_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 10], octave, 10, wave, 0, volume};
}

static inline Note B_Note(uint8 octave, wave_type wave, uint8 volume) {
  return (Note){
      NOTES[(fix_octave(octave) - 1) * 12 + 11], octave, 11, wave, 0, volume};
}

static inline Note Rest_Note() { return (Note){0, 0, 0, 0, 0, 0}; }

// ### Alias Notes ###
#define CFlat_Note B_Note
#define DFlat_Note CSharp_Note
#define EFlat_Note DSharp_Note
#define FFlat_Note E_Note
#define GFlat_Note FSharp_Note
#define AFlat_Note GSharp_Note
#define BFlat_Note ASharp_Note

#define ESharp_Note F_Note
#define BSharp_Note C_Note

/// ### NOTE MACROS ###

#define C1 C_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define C2 C_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define C3 C_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define C4 C_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define C5 C_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define C6 C_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define C7 C_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Cs1 CSharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Cs2 CSharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Cs3 CSharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Cs4 CSharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Cs5 CSharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Cs6 CSharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Cs7 CSharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Cf1 CFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Cf2 CFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Cf3 CFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Cf4 CFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Cf5 CFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Cf6 CFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Cf7 CFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define D1 D_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define D2 D_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define D3 D_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define D4 D_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define D5 D_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define D6 D_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define D7 D_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Ds1 DSharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Ds2 DSharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Ds3 DSharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Ds4 DSharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Ds5 DSharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Ds6 DSharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Ds7 DSharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Df1 DFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Df2 DFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Df3 DFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Df4 DFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Df5 DFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Df6 DFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Df7 DFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define E1 E_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define E2 E_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define E3 E_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define E4 E_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define E5 E_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define E6 E_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define E7 E_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Es1 ESharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Es2 ESharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Es3 ESharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Es4 ESharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Es5 ESharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Es6 ESharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Es7 ESharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Ef1 EFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Ef2 EFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Ef3 EFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Ef4 EFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Ef5 EFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Ef6 EFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Ef7 EFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define F1 F_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define F2 F_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define F3 F_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define F4 F_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define F5 F_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define F6 F_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define F7 F_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Fs1 FSharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Fs2 FSharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Fs3 FSharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Fs4 FSharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Fs5 FSharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Fs6 FSharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Fs7 FSharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Ff1 FFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Ff2 FFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Ff3 FFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Ff4 FFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Ff5 FFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Ff6 FFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Ff7 FFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define G1 G_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define G2 G_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define G3 G_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define G4 G_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define G5 G_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define G6 G_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define G7 G_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Gs1 GSharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Gs2 GSharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Gs3 GSharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Gs4 GSharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Gs5 GSharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Gs6 GSharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Gs7 GSharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Gf1 GFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Gf2 GFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Gf3 GFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Gf4 GFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Gf5 GFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Gf6 GFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Gf7 GFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define A1 A_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define A2 A_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define A3 A_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define A4 A_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define A5 A_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define A6 A_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define A7 A_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define As1 ASharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define As2 ASharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define As3 ASharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define As4 ASharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define As5 ASharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define As6 ASharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define As7 ASharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Af1 AFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Af2 AFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Af3 AFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Af4 AFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Af5 AFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Af6 AFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Af7 AFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define B1 B_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define B2 B_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define B3 B_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define B4 B_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define B5 B_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define B6 B_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define B7 B_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Bs1 BSharp_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Bs2 BSharp_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Bs3 BSharp_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Bs4 BSharp_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Bs5 BSharp_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Bs6 BSharp_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Bs7 BSharp_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define Bf1 BFlat_Note(1, NOTE_WAVE, NOTE_VOLUME)
#define Bf2 BFlat_Note(2, NOTE_WAVE, NOTE_VOLUME)
#define Bf3 BFlat_Note(3, NOTE_WAVE, NOTE_VOLUME)
#define Bf4 BFlat_Note(4, NOTE_WAVE, NOTE_VOLUME)
#define Bf5 BFlat_Note(5, NOTE_WAVE, NOTE_VOLUME)
#define Bf6 BFlat_Note(6, NOTE_WAVE, NOTE_VOLUME)
#define Bf7 BFlat_Note(7, NOTE_WAVE, NOTE_VOLUME)

#define RST Rest_Note()

static inline Note *new_note() { return (Note *)kmalloc(sizeof(Note)); }

static inline Note *new_note_from_note(Note n) {
  Note *note = new_note();
  memcpy(note, &n, sizeof(n));
  return note;
}

static inline Note *new_notes_from_notes(Note *notes, uint8 num_of_notes) {
  Note *note_array = (Note *)kmalloc(num_of_notes * sizeof(Note));
  memcpy(note_array, &notes, num_of_notes * sizeof(Note));
  return note_array;
}

#endif