#ifndef HEADER_DH_H
#include <openssl/dh.h>
#endif
DH *get_dh2048()
	{
	static unsigned char dh2048_p[]={
		0xF9,0x20,0x18,0xA8,0x7B,0x64,0x58,0x3B,0xAA,0x99,0xA7,0xBB,
		0xEF,0x22,0x12,0x13,0x8F,0x34,0x25,0x88,0x83,0xD0,0x04,0xD5,
		0x6D,0x1A,0xD2,0x87,0x81,0x60,0x2B,0x06,0x7B,0xE6,0x47,0x22,
		0x0C,0xE6,0xBD,0xF0,0xBC,0xA9,0xF5,0xAA,0x90,0x67,0xA9,0x2C,
		0x40,0x25,0xAD,0xFC,0xF3,0x40,0x42,0x97,0x98,0x72,0x04,0x1A,
		0xC2,0xF5,0x0E,0x62,0x2E,0xFF,0xF4,0xCB,0x8D,0x19,0x55,0x19,
		0x27,0x5E,0xF4,0x26,0x4C,0xFF,0xCE,0x96,0x83,0x8E,0x51,0xEC,
		0xE3,0xF8,0x85,0xF3,0x45,0xCA,0xC9,0xCC,0x47,0x2E,0x77,0x2C,
		0xEF,0xC8,0xA8,0xFC,0xD7,0xDD,0x38,0x95,0xBA,0xCA,0x08,0x98,
		0xDF,0x4C,0xF2,0xC7,0x48,0x5F,0xB1,0xC3,0x91,0x15,0xB2,0x3C,
		0x69,0xAB,0x2D,0x2D,0xB1,0x22,0xD3,0xDB,0x86,0x22,0xF4,0x88,
		0x28,0x0B,0xD8,0xD5,0x95,0xCC,0xBF,0x92,0x2D,0xEF,0x0A,0xAA,
		0x2E,0xF6,0xC6,0xAC,0xF5,0x54,0x37,0x30,0xC4,0xD5,0xB2,0xCB,
		0xD3,0xE5,0x43,0x08,0x81,0xF9,0x71,0x8A,0xDB,0x58,0xAC,0xC0,
		0x68,0x9A,0x00,0xA3,0x96,0xA8,0xA8,0xC5,0x6A,0xDB,0x3B,0x42,
		0x09,0xDA,0x4A,0x6C,0x65,0x1E,0xA5,0xD5,0x4A,0x55,0xD3,0x02,
		0x83,0x57,0xE5,0x8F,0x14,0xDE,0x3B,0x51,0xAD,0xA6,0x32,0x72,
		0x63,0x0A,0x5C,0x4D,0x06,0x25,0x26,0x67,0x67,0xA2,0x8E,0x7F,
		0x62,0x9E,0x70,0xB0,0x4D,0x30,0x30,0xF4,0x1B,0x02,0xA9,0xB1,
		0x9A,0xFE,0x68,0x91,0x50,0xFD,0x16,0x31,0x20,0xDF,0xCC,0x64,
		0xB3,0x99,0xD8,0x62,0x4D,0x7D,0x3D,0x5C,0x9A,0xD1,0x0A,0x9C,
		0x0E,0x88,0x23,0xDB,
		};
	static unsigned char dh2048_g[]={
		0x02,
		};
	DH *dh;

	if ((dh=DH_new()) == NULL) return(NULL);
	dh->p=BN_bin2bn(dh2048_p,sizeof(dh2048_p),NULL);
	dh->g=BN_bin2bn(dh2048_g,sizeof(dh2048_g),NULL);
	if ((dh->p == NULL) || (dh->g == NULL))
		{ DH_free(dh); return(NULL); }
	return(dh);
	}
