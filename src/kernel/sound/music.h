#ifndef _MUSIC_H
#define _MUSIC_H

#include "types.h"

#define NUM_OCTAVES 7
#define OCTAVE_SIZE 12

static const float64 NOTES[NUM_OCTAVES * OCTAVE_SIZE] = {
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
  wave_type wave_type;
  float64 sample_count;
  uint8 volume;

} Note;

typedef struct Chord {
  Note *notes;
  float64 duration;
} Chord;

typedef struct Melody {
  Note *notes;
} Melody;

typedef struct Beat {
  Note *notes;
} Beat;



#define C_NOTE(o,w,v) (Note) {NOTES[(o - 1) * 12], w, 0, v}
#define CS_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 1], w, 0, v}
#define D_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 2], w, 0, v}
#define DS_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 3], w, 0, v}
#define E_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 4], w, 0, v}
#define F_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 5], w, 0, v}
#define FS_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 6], w, 0, v}
#define G_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 7], w, 0, v}
#define GS_NOTE(o,w,v)(Note) {  NOTES[(o - 1) * 12 + 8], w, 0, v}
#define A_NOTE(o,w,v)  (Note) {NOTES[(o - 1) * 12 + 9], w, 0, v}
#define AS_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 10], w, 0, v}
#define B_NOTE(o,w,v) (Note) { NOTES[(o - 1) * 12 + 11], w, 0, v}


void music_init();

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                            uint16 sample_scale);
#endif
