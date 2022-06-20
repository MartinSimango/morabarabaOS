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
#define WAVE_NOISE 2
#define WAVE_TRIANGLE 3

typedef struct Note {
  float64 freq;
  uint8 octave;
  uint8 offset;
  wave_type wave_type;
  float64 sample_count;
  uint8 volume;

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

#define C1(w, v) C_Note(1, w, v)
#define C2(w, v) C_Note(2, w, v)
#define C3(w, v) C_Note(3, w, v)
#define C4(w, v) C_Note(4, w, v)
#define C5(w, v) C_Note(5, w, v)
#define C6(w, v) C_Note(6, w, v)
#define C7(w, v) C_Note(7, w, v)

#define Cs1(w, v) CSharp_Note(1, w, v)
#define Cs2(w, v) CSharp_Note(2, w, v)
#define Cs3(w, v) CSharp_Note(3, w, v)
#define Cs4(w, v) CSharp_Note(4, w, v)
#define Cs5(w, v) CSharp_Note(5, w, v)
#define Cs6(w, v) CSharp_Note(6, w, v)
#define Cs7(w, v) CSharp_Note(7, w, v)

#define Cf1(w, v) CFlat_Note(1, w, v)
#define Cf2(w, v) CFlat_Note(2, w, v)
#define Cf3(w, v) CFlat_Note(3, w, v)
#define Cf4(w, v) CFlat_Note(4, w, v)
#define Cf5(w, v) CFlat_Note(5, w, v)
#define Cf6(w, v) CFlat_Note(6, w, v)
#define Cf7(w, v) CFlat_Note(7, w, v)

#define D1(w, v) D_Note(1, w, v)
#define D2(w, v) D_Note(2, w, v)
#define D3(w, v) D_Note(3, w, v)
#define D4(w, v) D_Note(4, w, v)
#define D5(w, v) D_Note(5, w, v)
#define D6(w, v) D_Note(6, w, v)
#define D7(w, v) D_Note(7, w, v)

#define Ds1(w, v) DSharp_Note(1, w, v)
#define Ds2(w, v) DSharp_Note(2, w, v)
#define Ds3(w, v) DSharp_Note(3, w, v)
#define Ds4(w, v) DSharp_Note(4, w, v)
#define Ds5(w, v) DSharp_Note(5, w, v)
#define Ds6(w, v) DSharp_Note(6, w, v)
#define Ds7(w, v) DSharp_Note(7, w, v)

#define Df1(w, v) DFlat_Note(1, w, v)
#define Df2(w, v) DFlat_Note(2, w, v)
#define Df3(w, v) DFlat_Note(3, w, v)
#define Df4(w, v) DFlat_Note(4, w, v)
#define Df5(w, v) DFlat_Note(5, w, v)
#define Df6(w, v) DFlat_Note(6, w, v)
#define Df7(w, v) DFlat_Note(7, w, v)

#define E1(w, v) E_Note(1, w, v)
#define E2(w, v) E_Note(2, w, v)
#define E3(w, v) E_Note(3, w, v)
#define E4(w, v) E_Note(4, w, v)
#define E5(w, v) E_Note(5, w, v)
#define E6(w, v) E_Note(6, w, v)
#define E7(w, v) E_Note(7, w, v)

#define Es1(w, v) ESharp_Note(1, w, v)
#define Es2(w, v) ESharp_Note(2, w, v)
#define Es3(w, v) ESharp_Note(3, w, v)
#define Es4(w, v) ESharp_Note(4, w, v)
#define Es5(w, v) ESharp_Note(5, w, v)
#define Es6(w, v) ESharp_Note(6, w, v)
#define Es7(w, v) ESharp_Note(7, w, v)

#define Ef1(w, v) EFlat_Note(1, w, v)
#define Ef2(w, v) EFlat_Note(2, w, v)
#define Ef3(w, v) EFlat_Note(3, w, v)
#define Ef4(w, v) EFlat_Note(4, w, v)
#define Ef5(w, v) EFlat_Note(5, w, v)
#define Ef6(w, v) EFlat_Note(6, w, v)
#define Ef7(w, v) EFlat_Note(7, w, v)

#define F1(w, v) F_Note(1, w, v)
#define F2(w, v) F_Note(2, w, v)
#define F3(w, v) F_Note(3, w, v)
#define F4(w, v) F_Note(4, w, v)
#define F5(w, v) F_Note(5, w, v)
#define F6(w, v) F_Note(6, w, v)
#define F7(w, v) F_Note(7, w, v)

#define Fs1(w, v) FSharp_Note(1, w, v)
#define Fs2(w, v) FSharp_Note(2, w, v)
#define Fs3(w, v) FSharp_Note(3, w, v)
#define Fs4(w, v) FSharp_Note(4, w, v)
#define Fs5(w, v) FSharp_Note(5, w, v)
#define Fs6(w, v) FSharp_Note(6, w, v)
#define Fs7(w, v) FSharp_Note(7, w, v)

#define Ff1(w, v) FFlat_Note(1, w, v)
#define Ff2(w, v) FFlat_Note(2, w, v)
#define Ff3(w, v) FFlat_Note(3, w, v)
#define Ff4(w, v) FFlat_Note(4, w, v)
#define Ff5(w, v) FFlat_Note(5, w, v)
#define Ff6(w, v) FFlat_Note(6, w, v)
#define Ff7(w, v) FFlat_Note(7, w, v)

#define G1(w, v) G_Note(1, w, v)
#define G2(w, v) G_Note(2, w, v)
#define G3(w, v) G_Note(3, w, v)
#define G4(w, v) G_Note(4, w, v)
#define G5(w, v) G_Note(5, w, v)
#define G6(w, v) G_Note(6, w, v)
#define G7(w, v) G_Note(7, w, v)

#define Gs1(w, v) GSharp_Note(1, w, v)
#define Gs2(w, v) GSharp_Note(2, w, v)
#define Gs3(w, v) GSharp_Note(3, w, v)
#define Gs4(w, v) GSharp_Note(4, w, v)
#define Gs5(w, v) GSharp_Note(5, w, v)
#define Gs6(w, v) GSharp_Note(6, w, v)
#define Gs7(w, v) GSharp_Note(7, w, v)

#define Gf1(w, v) GFlat_Note(1, w, v)
#define Gf2(w, v) GFlat_Note(2, w, v)
#define Gf3(w, v) GFlat_Note(3, w, v)
#define Gf4(w, v) GFlat_Note(4, w, v)
#define Gf5(w, v) GFlat_Note(5, w, v)
#define Gf6(w, v) GFlat_Note(6, w, v)
#define Gf7(w, v) GFlat_Note(7, w, v)

#define A1(w, v) A_Note(1, w, v)
#define A2(w, v) A_Note(2, w, v)
#define A3(w, v) A_Note(3, w, v)
#define A4(w, v) A_Note(4, w, v)
#define A5(w, v) A_Note(5, w, v)
#define A6(w, v) A_Note(6, w, v)
#define A7(w, v) A_Note(7, w, v)

#define As1(w, v) ASharp_Note(1, w, v)
#define As2(w, v) ASharp_Note(2, w, v)
#define As3(w, v) ASharp_Note(3, w, v)
#define As4(w, v) ASharp_Note(4, w, v)
#define As5(w, v) ASharp_Note(5, w, v)
#define As6(w, v) ASharp_Note(6, w, v)
#define As7(w, v) ASharp_Note(7, w, v)

#define Af1(w, v) AFlat_Note(1, w, v)
#define Af2(w, v) AFlat_Note(2, w, v)
#define Af3(w, v) AFlat_Note(3, w, v)
#define Af4(w, v) AFlat_Note(4, w, v)
#define Af5(w, v) AFlat_Note(5, w, v)
#define Af6(w, v) AFlat_Note(6, w, v)
#define Af7(w, v) AFlat_Note(7, w, v)

#define B1(w, v) B_Note(1, w, v)
#define B2(w, v) B_Note(2, w, v)
#define B3(w, v) B_Note(3, w, v)
#define B4(w, v) B_Note(4, w, v)
#define B5(w, v) B_Note(5, w, v)
#define B6(w, v) B_Note(6, w, v)
#define B7(w, v) B_Note(7, w, v)

#define Bs1(w, v) BSharp_Note(1, w, v)
#define Bs2(w, v) BSharp_Note(2, w, v)
#define Bs3(w, v) BSharp_Note(3, w, v)
#define Bs4(w, v) BSharp_Note(4, w, v)
#define Bs5(w, v) BSharp_Note(5, w, v)
#define Bs6(w, v) BSharp_Note(6, w, v)
#define Bs7(w, v) BSharp_Note(7, w, v)

#define Bf1(w, v) BFlat_Note(1, w, v)
#define Bf2(w, v) BFlat_Note(2, w, v)
#define Bf3(w, v) BFlat_Note(3, w, v)
#define Bf4(w, v) BFlat_Note(4, w, v)
#define Bf5(w, v) BFlat_Note(5, w, v)
#define Bf6(w, v) BFlat_Note(6, w, v)
#define Bf7(w, v) BFlat_Note(7, w, v)

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