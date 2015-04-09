#ifndef HEADER_DH_H
#include <openssl/dh.h>
#endif
DH *get_dh4096()
	{
	static unsigned char dh4096_p[]={
		0xE6,0xA5,0xAA,0xE7,0xD9,0xC3,0x12,0xB8,0xB6,0x3D,0x1F,0x16,
		0x18,0x13,0xDC,0x56,0xAA,0xC3,0xE9,0xFD,0x2B,0x33,0x22,0xFC,
		0x80,0xB3,0x79,0x9F,0xB2,0xF8,0x96,0x57,0xEB,0x7C,0x28,0xDE,
		0x0F,0x48,0x92,0x29,0x94,0x41,0xC3,0xF9,0x47,0x52,0x33,0xEC,
		0xAD,0x33,0xE3,0xAC,0x17,0xC8,0x35,0xA4,0xF9,0x0F,0xE7,0xEA,
		0xE9,0xFA,0x9D,0xEE,0x39,0xF6,0xEF,0x2E,0x5F,0x3D,0xED,0x84,
		0xAB,0x7E,0x2B,0xDE,0x03,0xCE,0xDC,0x67,0x2C,0xAF,0x72,0xC6,
		0x5A,0xB0,0x9C,0x65,0x91,0x04,0x2D,0x0D,0xDD,0x96,0x1A,0xB0,
		0x65,0xD2,0x90,0xEA,0x77,0xA2,0x24,0xE2,0xA5,0xFA,0xF0,0xA0,
		0x0A,0x7C,0xE4,0x40,0xB0,0x7E,0x4F,0xB8,0xCE,0xC7,0xA7,0xCB,
		0x17,0xD7,0x0F,0x91,0x26,0xAA,0x94,0x38,0xEF,0x9E,0x77,0xF9,
		0xD0,0xD3,0x7C,0x20,0xFD,0x94,0xAC,0x11,0x4F,0x94,0x16,0x28,
		0x2F,0x06,0xA8,0x96,0xF4,0xDD,0x37,0x80,0x4B,0xF2,0xC9,0xC7,
		0x8C,0x3B,0x67,0xB3,0x09,0xEE,0x79,0xFF,0x18,0xDA,0xC2,0xBB,
		0x4F,0x05,0x2D,0x6C,0x65,0x66,0x9E,0x61,0x8C,0x40,0x1A,0x6F,
		0xA0,0x71,0xF1,0x58,0xAD,0xB8,0x29,0x87,0x95,0x9F,0x71,0x05,
		0x13,0xB5,0x22,0xBD,0x63,0x63,0xC4,0x0C,0x6E,0x47,0x54,0x43,
		0xB1,0x47,0x68,0xFE,0x31,0x06,0x53,0xBB,0x73,0x72,0x65,0x06,
		0x94,0x0A,0x68,0x49,0x26,0xF0,0x27,0x03,0xE3,0xCD,0x57,0x58,
		0xE7,0x7B,0x0F,0x83,0x3E,0x85,0x9C,0x2C,0x0A,0x5D,0x70,0xAF,
		0x11,0xA6,0x8E,0xB0,0x23,0x15,0xE9,0xC2,0xA8,0xD6,0x48,0x26,
		0x98,0x01,0x87,0x6C,0xE7,0xF3,0x94,0x36,0x47,0x96,0x67,0xDA,
		0xB0,0x3B,0x88,0xC4,0x1F,0xAB,0x35,0xF7,0x76,0x26,0xA5,0xC6,
		0xE6,0xEE,0x55,0x42,0xB0,0x2C,0x8F,0xA2,0xDA,0x06,0xA3,0x71,
		0xFE,0x4F,0x94,0x7A,0xCF,0xAB,0xE0,0xE9,0x00,0x27,0xC1,0xF8,
		0xA0,0x68,0x6A,0x44,0x41,0x03,0x80,0x5B,0x44,0xB0,0x6D,0x79,
		0xF2,0xCB,0x17,0x4A,0xD0,0xE0,0xC6,0x4A,0x8F,0x15,0x51,0x27,
		0x24,0x22,0x66,0x30,0x4B,0xC2,0xB3,0x3E,0xB1,0x3D,0x6B,0x1C,
		0xE4,0x11,0x1F,0x3A,0x64,0x2D,0x22,0x7B,0x40,0x1D,0x1E,0x45,
		0x42,0x2C,0xB7,0x62,0x76,0x17,0xFD,0x2C,0x7C,0x53,0x4D,0xBA,
		0x2B,0x8F,0x9F,0x84,0x48,0x6C,0x35,0x0A,0xCD,0x6B,0x6C,0x7F,
		0xB3,0xEB,0xDB,0x55,0x99,0x74,0xC0,0xA4,0x9D,0xE5,0x8F,0x29,
		0xCE,0xB3,0xD7,0xAB,0x3C,0xDE,0xB5,0x71,0xE1,0x03,0x1E,0x05,
		0x26,0xFD,0x3C,0xB5,0x2F,0x48,0xA0,0x8A,0x70,0x9C,0x20,0xF2,
		0x22,0xCF,0xBD,0x75,0x42,0x91,0x5B,0x8B,0x11,0x6B,0x69,0x94,
		0x25,0xFA,0xDB,0x97,0x92,0xCE,0xD7,0x3A,0x83,0xD5,0x7B,0x86,
		0x57,0x87,0xE6,0x1E,0x55,0xFE,0xE1,0x27,0x76,0x73,0xE3,0xC0,
		0x18,0x2B,0xDE,0xD5,0xF6,0x56,0x3F,0x5D,0xE6,0x3A,0xF3,0x69,
		0x0D,0xAB,0x7A,0x7B,0xE4,0x2C,0x76,0x4B,0xD6,0xD8,0x33,0xF9,
		0x2E,0xCC,0xCB,0xF8,0x69,0x6F,0xD1,0x40,0xF6,0xD2,0x05,0x44,
		0xE3,0x2D,0x34,0x4A,0xF8,0xC2,0xD8,0x2D,0x87,0x94,0xA2,0x65,
		0xDE,0xA1,0xBB,0x3E,0x99,0x35,0x18,0x10,0xA8,0xB0,0xB0,0x15,
		0xE7,0xAC,0x86,0x61,0x76,0x52,0x49,0x9B,
		};
	static unsigned char dh4096_g[]={
		0x02,
		};
	DH *dh;

	if ((dh=DH_new()) == NULL) return(NULL);
	dh->p=BN_bin2bn(dh4096_p,sizeof(dh4096_p),NULL);
	dh->g=BN_bin2bn(dh4096_g,sizeof(dh4096_g),NULL);
	if ((dh->p == NULL) || (dh->g == NULL))
		{ DH_free(dh); return(NULL); }
	return(dh);
	}
