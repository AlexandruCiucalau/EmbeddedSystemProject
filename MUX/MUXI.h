#ifndef MUXI_h
#define MUXI_h
#define MUX__DEBUG

/* Mapping MUX Control Pins */
#define MUX__COM 34
#define MUX__EN 5
#define MUX__S0 32
#define MUX__S1 33
#define MUX__S2 25
#define MUX__S3 26

#define MUX__DELAY 1000
#define MUX__LENGTH 16
#define MUX__MASK0 0x1  // first bit 0001
#define MUX__MASK1 0x2  // 2nd bit 0010
#define MUX__MASK2 0x4  // 3rd bit 0100
#define MUX__MASK3 0x8  // 4th bit 1000

MUX_unInputs unMuxInputs;

#endif