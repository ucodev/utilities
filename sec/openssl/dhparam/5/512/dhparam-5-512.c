#ifndef HEADER_DH_H
#include <openssl/dh.h>
#endif
DH *get_dh512()
	{
	static unsigned char dh512_p[]={
		0xCD,0xDF,0xE5,0x9B,0x9A,0x1C,0x96,0x95,0x5C,0xA7,0xCC,0x34,
		0xAD,0xDF,0x0B,0x81,0x6D,0x01,0x9F,0x99,0x53,0xCF,0x4C,0x51,
		0x90,0x94,0x74,0x74,0x8C,0x97,0xBC,0x31,0xAB,0x1B,0x6F,0x29,
		0x4A,0x49,0xF2,0xDC,0xD1,0x22,0x86,0x9B,0x85,0x3C,0xB2,0xD6,
		0xDA,0x00,0x65,0xCE,0x0C,0x97,0x88,0xA0,0xBF,0x1E,0x88,0x13,
		0x6D,0xC3,0xAF,0x3F,
		};
	static unsigned char dh512_g[]={
		0x05,
		};
	DH *dh;

	if ((dh=DH_new()) == NULL) return(NULL);
	dh->p=BN_bin2bn(dh512_p,sizeof(dh512_p),NULL);
	dh->g=BN_bin2bn(dh512_g,sizeof(dh512_g),NULL);
	if ((dh->p == NULL) || (dh->g == NULL))
		{ DH_free(dh); return(NULL); }
	return(dh);
	}
