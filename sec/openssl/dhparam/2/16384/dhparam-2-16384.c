#ifndef HEADER_DH_H
#include <openssl/dh.h>
#endif
DH *get_dh16384()
	{
	static unsigned char dh16384_p[]={
		0xB8,0x02,0xF5,0xD3,0x9F,0x49,0x3B,0x17,0x24,0x38,0x3C,0x05,
		0x2F,0xB4,0xC5,0xFF,0xF7,0xCF,0xE5,0x2E,0xB5,0xF1,0xE5,0xA7,
		0x24,0xD3,0x83,0xE6,0x91,0xCF,0xB9,0xF8,0x17,0x67,0x80,0x7C,
		0x6D,0xB0,0x07,0x1D,0xC1,0x5C,0x38,0xE8,0x4A,0xA8,0xCB,0x15,
		0xBE,0x5B,0xA4,0xB2,0xBA,0xCC,0x91,0x66,0x17,0xE2,0x5C,0xC7,
		0x21,0xA2,0x96,0xD1,0x55,0xCD,0x89,0x74,0xF3,0xFD,0x83,0x07,
		0x26,0x21,0x7F,0x8E,0x66,0x76,0x5E,0x56,0xC2,0x8E,0xAA,0x3E,
		0x5D,0x04,0xA8,0x9A,0xF0,0x3E,0xCD,0x13,0x5D,0x68,0xE9,0xE8,
		0x83,0x10,0x7C,0x07,0xF4,0x6C,0x9D,0x73,0xC0,0x26,0x1F,0x08,
		0x8D,0xC3,0x55,0x36,0x9D,0xCD,0xC4,0xB9,0xFD,0x38,0xA9,0x0A,
		0x26,0x01,0x80,0x60,0x54,0x13,0xD5,0x41,0xE2,0xF4,0x20,0x29,
		0x7B,0x84,0xCE,0x23,0xB0,0x0C,0x37,0x6A,0xF3,0x73,0xF2,0xEC,
		0x34,0xA7,0xCE,0x37,0xCE,0xC0,0x63,0x02,0x2C,0xF9,0x96,0xB9,
		0x1F,0xED,0xCC,0x92,0x27,0xD6,0x51,0x4F,0x20,0x81,0xA2,0xA8,
		0xB4,0xC1,0xE0,0x01,0xFB,0xD0,0xC9,0x74,0xA3,0xBE,0x10,0xF5,
		0x7B,0x26,0xAD,0x72,0x24,0xE4,0x63,0xFE,0xAD,0xD1,0x5C,0x45,
		0xC8,0x04,0x31,0x4F,0x86,0xAD,0x65,0xA7,0x60,0x18,0xBD,0x30,
		0x17,0x03,0x1C,0x2C,0x76,0x65,0x4F,0xD6,0xD6,0x5F,0x3D,0x59,
		0x49,0x37,0x00,0xC8,0x1A,0xDF,0x5E,0xFE,0xDA,0x66,0x4A,0xA6,
		0x9F,0x04,0x90,0x57,0xCB,0xA7,0xF2,0xE5,0x04,0xC3,0xC9,0x1D,
		0xB5,0x9E,0x33,0x0C,0x25,0x0D,0x9D,0x4A,0x55,0xC0,0x8C,0xCD,
		0x8D,0x9C,0x98,0x09,0x9F,0xBC,0xD6,0x57,0x13,0xE1,0x3F,0xDD,
		0x7C,0x33,0x79,0x54,0x10,0xC2,0x04,0xBD,0xA8,0x42,0xA9,0x34,
		0x8A,0xDF,0x36,0xC6,0x6E,0x34,0x39,0x1B,0x15,0x1F,0x8E,0xB9,
		0xFD,0x31,0x6A,0x18,0x72,0x9A,0x22,0xC2,0x91,0x0A,0x49,0x0A,
		0x8A,0x93,0xAF,0x90,0x3F,0x84,0x68,0x2B,0x9B,0x24,0x1D,0xEB,
		0x80,0xB9,0x34,0x04,0xC4,0x52,0x42,0xFD,0x04,0xE3,0xB7,0x64,
		0x2F,0xAA,0xA4,0x5F,0xDC,0xD7,0x26,0xF9,0xC2,0xA8,0x7A,0x37,
		0x0B,0xE1,0x7B,0x4D,0xA7,0x83,0x8F,0x5D,0x70,0x10,0xBC,0x8C,
		0x8C,0x5D,0x0C,0x64,0x65,0x88,0x79,0xD3,0xBE,0x4D,0x74,0x00,
		0xB4,0xC9,0x6F,0x58,0xC4,0x0C,0x5D,0xED,0x31,0x79,0x9D,0xDB,
		0xE6,0x6A,0x90,0x94,0xA0,0xEE,0x76,0xDD,0xFD,0x84,0x93,0x7B,
		0x9E,0x61,0xC9,0x63,0x2E,0x47,0x55,0xEF,0xDF,0x96,0x5F,0xB0,
		0xBA,0x99,0xBF,0x63,0x39,0x68,0x5D,0xEE,0x8C,0x99,0x89,0xA4,
		0x5A,0xE4,0x27,0x99,0x68,0x0C,0xFC,0xD9,0xAE,0xC2,0xAA,0x19,
		0xA1,0x65,0xBE,0x18,0x5F,0x0E,0x50,0x76,0xC2,0x1B,0xD1,0x5A,
		0x67,0xA2,0x12,0x40,0x2D,0x5E,0x34,0xE3,0x67,0xED,0x3E,0x5E,
		0x6A,0x26,0x6C,0xAD,0x1E,0xBB,0x73,0x65,0x08,0xF4,0x35,0x95,
		0x76,0xD2,0x5C,0xBD,0x8B,0x53,0x81,0x8C,0x7D,0x93,0x63,0xA3,
		0x03,0xDF,0xD4,0x52,0xDB,0x12,0x0A,0x9B,0xE5,0x6C,0xDC,0x74,
		0x1A,0x3C,0xE8,0xE1,0x30,0x65,0x71,0x27,0xF1,0x98,0xC7,0x97,
		0xAC,0xD7,0x62,0x11,0x1E,0xE0,0x1E,0x77,0x6E,0x30,0xB6,0x96,
		0x00,0x9A,0x36,0x4F,0x8C,0x67,0xBF,0x4C,0x29,0xB9,0x5D,0xA6,
		0x72,0x78,0x12,0x98,0x51,0xFD,0xC8,0x90,0xA6,0x28,0xDC,0xCC,
		0xB4,0xEB,0x4A,0xE4,0x0C,0x52,0xE4,0xFB,0x19,0x0D,0xE0,0x94,
		0x62,0xA3,0x59,0x31,0x07,0x60,0x18,0x57,0xE0,0x25,0x9C,0x49,
		0x03,0x7D,0xFE,0x3C,0xE7,0xB5,0x1C,0x76,0xE1,0xB2,0xC8,0x32,
		0x01,0x30,0x4B,0x27,0x1D,0xDE,0x43,0x72,0x17,0x50,0x14,0xCA,
		0x63,0x15,0x0C,0x64,0x1B,0x9E,0x22,0x8D,0xD5,0x58,0xB0,0x90,
		0x2F,0x6E,0x6E,0x2E,0xD5,0x12,0x2A,0x33,0x42,0x87,0xF0,0xAB,
		0x10,0x2C,0x7F,0x42,0xAA,0xE8,0x88,0x78,0x06,0x78,0xF4,0x96,
		0x64,0x78,0xE2,0x0A,0xDA,0xBD,0xD1,0x5F,0x5E,0xBB,0xD0,0x15,
		0x4B,0x91,0x5B,0x42,0xD3,0x5C,0x52,0x22,0x96,0x77,0x44,0x2F,
		0xE1,0x19,0x4A,0x69,0x8B,0x19,0x97,0xEF,0x8A,0xBB,0x75,0x82,
		0x53,0x52,0x3A,0xB7,0x2A,0x14,0x1A,0xDA,0xF1,0x9A,0x64,0xED,
		0xF7,0xE5,0xBC,0x05,0xC1,0xCD,0x43,0x1A,0xCD,0xC9,0xB5,0xFF,
		0x46,0x59,0xDA,0x9A,0xD5,0xF0,0x2F,0xB5,0x6F,0x49,0x95,0x9A,
		0xD9,0xA3,0x0D,0x33,0x2F,0x25,0xBB,0x8B,0x87,0xA1,0x1B,0x91,
		0x63,0xB9,0xD4,0x17,0xFC,0xF2,0x8A,0x29,0x12,0xE4,0xBD,0xDC,
		0xBC,0x29,0x23,0xB2,0x00,0xC7,0x98,0x92,0x34,0x35,0x92,0x2D,
		0x6D,0xB1,0x31,0x82,0x60,0xDD,0x2E,0x3B,0x33,0xFF,0xC7,0x61,
		0xED,0x17,0xC5,0x2C,0xB3,0xDC,0xB1,0x92,0x5B,0x2D,0x29,0x98,
		0xF7,0x1B,0x6E,0xEE,0x42,0x11,0xA7,0x58,0xCA,0x62,0x39,0x31,
		0x2D,0xA3,0x42,0x7D,0xA3,0x6E,0x7E,0x26,0x4E,0xA9,0x25,0x67,
		0x60,0x90,0xB3,0x52,0xC7,0xA2,0xB1,0xD0,0xC5,0xA3,0x82,0xEF,
		0x6B,0x06,0xCC,0x25,0xB1,0x9E,0x53,0xF1,0xFB,0xA7,0x07,0x29,
		0x08,0xF6,0x46,0x92,0xA3,0x09,0xF2,0xE4,0x58,0xF1,0x18,0x15,
		0xAD,0xD6,0x3D,0x64,0x39,0x42,0xF3,0x9A,0x9A,0xBD,0xB7,0x20,
		0x4D,0x34,0x9B,0x7F,0x16,0x3A,0x2C,0x54,0x53,0x7A,0x9D,0x6C,
		0x55,0x2F,0x6D,0x07,0x93,0xCA,0xDA,0x89,0x0B,0x0A,0xFD,0xFE,
		0x88,0xF8,0xA0,0x11,0xD2,0x62,0x91,0x49,0xCF,0xAC,0xED,0x2B,
		0x34,0xB3,0xFD,0xB3,0x3A,0x90,0x55,0xD9,0x22,0xEA,0x5C,0x1A,
		0x73,0x78,0xB9,0xDC,0x33,0xF7,0xC1,0xD9,0xBE,0xE4,0xD9,0xC8,
		0xC5,0x68,0x90,0x17,0x07,0x69,0xA8,0x3C,0x5A,0xFD,0x2C,0x05,
		0x24,0x61,0xFF,0x26,0xAA,0xB4,0xD0,0xFE,0xF6,0xDD,0x39,0x8A,
		0x47,0x6D,0xCC,0x55,0x19,0x58,0x6B,0xB9,0xF5,0x1A,0x44,0x80,
		0x6E,0xB8,0xE2,0xAD,0x3A,0xEE,0x5B,0xC5,0xD8,0x5B,0x3F,0xEF,
		0x32,0x50,0x55,0x69,0xB3,0x27,0xB4,0x40,0xE1,0xB6,0xAB,0xBE,
		0x37,0xFC,0xCC,0x6E,0xA8,0xB9,0xE9,0xFD,0x50,0xBE,0xF2,0xAB,
		0xEC,0x44,0x0E,0xC6,0xB9,0x3B,0xCA,0xD0,0x72,0x90,0xCB,0x40,
		0xA0,0x19,0x60,0xC3,0xAC,0x08,0x4C,0x4D,0xE7,0xDE,0x01,0xC8,
		0x77,0x22,0x7F,0x26,0xCE,0x0C,0xFE,0x93,0x23,0x83,0x1A,0xD1,
		0x58,0x27,0xCF,0x46,0x6D,0xB3,0x03,0x1E,0x00,0xF9,0xF9,0x71,
		0x97,0xAE,0xFE,0x7B,0x91,0x48,0x2D,0x59,0x21,0xC1,0x05,0x93,
		0xCD,0x17,0x3D,0x7F,0x7A,0xFE,0x98,0x1C,0x34,0x2B,0x5F,0x46,
		0xBD,0x2B,0xCB,0xB3,0x99,0xAB,0x03,0xE3,0x35,0x60,0xEE,0xFC,
		0x4D,0x8D,0x68,0x48,0x4A,0x94,0x04,0xBC,0x26,0x60,0x32,0xDD,
		0x76,0xF0,0x7A,0xE0,0xF8,0xE6,0xAD,0x9D,0x72,0x50,0x63,0xF1,
		0xDB,0xA8,0xEB,0x3D,0xE0,0xDE,0x30,0xC4,0x3B,0x95,0x5E,0x8D,
		0x7B,0x4C,0xA3,0xDF,0xD9,0x73,0xC4,0xB2,0x31,0x45,0x48,0xAE,
		0x7C,0xAE,0x6C,0xD0,0xFA,0xB9,0xAD,0x99,0x1D,0xCF,0xFF,0x3C,
		0x0B,0xE0,0xCF,0xCA,0x70,0x35,0x82,0xD8,0xA0,0x6D,0xB6,0xEB,
		0x2A,0xB0,0x20,0x66,0x64,0x1A,0x58,0x15,0x7E,0x09,0x80,0x0A,
		0xA8,0xAD,0xC9,0xC6,0x49,0x43,0x5F,0x58,0x27,0x01,0x13,0x15,
		0xD1,0xA7,0x74,0x52,0xCC,0xF1,0xA8,0x8B,0x24,0x99,0x7C,0x96,
		0x45,0x79,0x0A,0xAF,0x99,0xA8,0x27,0x3B,0xF7,0x8B,0xE6,0x4C,
		0xFD,0x5C,0xBC,0xB1,0x43,0x73,0x8D,0x3E,0x0D,0xF1,0x3C,0xC1,
		0xAA,0x1A,0xE4,0x7F,0x27,0x73,0x51,0x63,0x27,0xEF,0xF0,0xA5,
		0x0E,0x84,0x8B,0x75,0x50,0x63,0x0B,0xEC,0xBC,0xA4,0x2A,0xF9,
		0xD1,0x39,0xE0,0x0C,0x3F,0xD7,0xD4,0x27,0x4D,0xAA,0xA7,0x62,
		0x41,0x46,0xF5,0x59,0x33,0x96,0x1F,0x33,0x39,0x89,0x43,0x28,
		0xFC,0x73,0x9F,0x96,0xDB,0x0D,0xC4,0xE0,0x77,0x96,0x3E,0xB3,
		0x33,0x03,0x92,0x44,0x8A,0xF8,0x80,0x0E,0xD1,0xFE,0x95,0xA1,
		0x9A,0x7E,0x83,0x08,0x60,0x98,0x3C,0xF6,0xD2,0xD6,0x67,0x6E,
		0x0B,0x18,0xC5,0x93,0x2C,0xCC,0xB9,0xF7,0x50,0x41,0xE1,0x67,
		0x5F,0x68,0x0F,0x9C,0xF1,0x1E,0xE2,0x22,0xC9,0xD8,0x0B,0xE4,
		0x75,0xB7,0x3B,0xAB,0x93,0x83,0x0A,0x2D,0x86,0xDA,0xA8,0x9E,
		0x1D,0x47,0xDF,0x7E,0x04,0xA8,0xB7,0x68,0x25,0xA1,0xBB,0x90,
		0x74,0xD1,0x3F,0xBB,0x7F,0xBD,0xAE,0xC8,0xA8,0xC0,0xA9,0x30,
		0x48,0x15,0xDE,0xC0,0xCD,0xFE,0xBF,0x31,0x63,0x8A,0x27,0x19,
		0xDA,0x19,0xA5,0x6B,0xE5,0xA2,0xD1,0x0F,0x96,0x20,0xF1,0xFF,
		0x0E,0x9A,0x15,0xBC,0x85,0x08,0x59,0x08,0x76,0x11,0xAE,0x7D,
		0x03,0x9B,0x13,0x4D,0xA9,0xFD,0x59,0x15,0x3E,0x22,0xB5,0x40,
		0x0F,0x60,0x81,0xEB,0xE8,0xDC,0x4C,0xE9,0x54,0xBE,0xB3,0xAC,
		0xAB,0xFD,0x0F,0xA5,0x80,0xDD,0xDD,0x46,0x05,0xC4,0x22,0xE7,
		0xBA,0x48,0x84,0x0F,0x57,0x1A,0x9B,0x6A,0x32,0xBC,0x72,0x12,
		0x0A,0xD8,0x8B,0xDE,0xCA,0xF6,0x99,0x8E,0x4F,0xB8,0x93,0x36,
		0x1B,0xED,0xA7,0xD4,0xCA,0xCF,0xDD,0x92,0xE8,0xFD,0x6A,0xD7,
		0x53,0x61,0x91,0x3B,0xAA,0xDA,0x7D,0x8F,0x1D,0x0B,0x16,0x84,
		0xB3,0x77,0x0F,0xC8,0xDC,0x63,0x97,0x44,0x6F,0x00,0xD5,0x8D,
		0xDE,0x8D,0x2E,0xA3,0x7C,0xFB,0xB1,0x2A,0x84,0xD5,0x19,0xB0,
		0x8F,0x97,0x89,0xC3,0xB6,0xA9,0xC2,0xBA,0x60,0xA2,0xCD,0xF3,
		0xB5,0x58,0xB3,0x26,0x65,0xA9,0xA1,0x9F,0x41,0xD4,0x91,0x22,
		0xB0,0xFF,0x86,0x3D,0xB3,0x08,0xF9,0xCE,0xC4,0x3B,0x61,0x76,
		0xC5,0xCD,0x55,0x03,0x70,0x3A,0x5C,0xF1,0xD0,0xF0,0x1C,0x75,
		0x90,0x78,0x26,0xB0,0x28,0xD7,0xDA,0x34,0x4A,0xE0,0x9C,0x4A,
		0x07,0x09,0x13,0x78,0x69,0x92,0x16,0xD1,0xB8,0x4F,0x28,0x6F,
		0x66,0x4B,0x98,0x10,0x8A,0x18,0x17,0x8F,0xDE,0x7D,0x04,0x99,
		0x0A,0x32,0xA3,0x1A,0x18,0xFF,0xA4,0x43,0x62,0xC7,0xF7,0xE5,
		0x1D,0xE8,0x48,0xFC,0x67,0x35,0xE0,0x64,0xB2,0x9F,0x69,0xDD,
		0x6F,0x9E,0xA4,0x97,0x56,0x01,0x25,0x6A,0x48,0x8B,0x3B,0xE7,
		0xDB,0x69,0xB7,0xDF,0xF2,0xAB,0x03,0x1E,0x29,0x2B,0xF0,0x24,
		0xDC,0x02,0xA5,0x0D,0x9B,0xF3,0x29,0x6F,0x09,0x5D,0x2A,0x77,
		0x0E,0xA4,0x15,0x8F,0xE4,0x94,0x2D,0x53,0x8D,0x14,0xCC,0x5C,
		0xEA,0xD1,0xBB,0x1B,0x1C,0x24,0xCE,0x2C,0x81,0xE8,0xDF,0xA6,
		0xE5,0xB9,0x30,0x5E,0x20,0x27,0x5F,0xD1,0x76,0x7D,0x9F,0x9F,
		0xFF,0x5A,0xA8,0xC9,0x94,0x9C,0xAB,0x5C,0xF3,0x16,0xFB,0xDB,
		0xE7,0xA0,0xBF,0xB3,0xF3,0x38,0x63,0x60,0x40,0xB4,0x19,0x4D,
		0xE4,0x2B,0xF6,0x66,0x9D,0x07,0xA7,0x0B,0x4F,0x0C,0x9E,0xA3,
		0x20,0x82,0xD7,0xD1,0x88,0xE3,0xDD,0x92,0xE0,0x56,0xC1,0xC2,
		0x29,0x15,0x0B,0xCB,0x42,0xC7,0x67,0x09,0xC4,0xA7,0x2B,0x68,
		0x3E,0x35,0x1D,0x4A,0xB8,0x9E,0x67,0xF6,0x7D,0x06,0x84,0x52,
		0x60,0xB4,0xE3,0x4E,0xF6,0x27,0x0E,0xB9,0x97,0x9C,0x13,0x89,
		0x6A,0x39,0x19,0x4D,0x01,0x5C,0x34,0x82,0x4C,0xC7,0x7C,0xBF,
		0x2C,0x52,0x05,0x99,0xFE,0xE6,0x44,0x4D,0x78,0xB9,0x20,0x30,
		0xCA,0x4B,0xC6,0x54,0xF1,0x58,0x16,0x77,0xDC,0x5D,0x2E,0xBA,
		0x97,0x1F,0xAE,0xA4,0x16,0xB1,0x56,0xCA,0xF6,0x72,0x63,0xF8,
		0x69,0x20,0x8C,0x07,0x66,0xBD,0x7E,0x5E,0x05,0xA4,0xCD,0x93,
		0x44,0x0D,0x4A,0x64,0xB1,0xF1,0xD6,0x0A,0xAD,0x69,0x1A,0xD7,
		0xCE,0x60,0x87,0xE7,0x6E,0xC6,0x38,0x84,0x0F,0x1A,0x9D,0x7B,
		0x9F,0x27,0x8C,0x58,0x88,0x6B,0xA7,0xD9,0xA2,0x2E,0x99,0xB7,
		0x0C,0xB5,0x45,0xD5,0xA9,0x8D,0xB6,0xD8,0xB7,0xB1,0x18,0xB0,
		0x66,0x94,0xA8,0xA9,0x49,0x32,0x98,0x50,0xF5,0x05,0xB4,0x73,
		0xB4,0xDD,0x88,0x72,0xD4,0xF8,0x7D,0x1E,0x07,0x7C,0x17,0x99,
		0x49,0xFB,0x8C,0xF9,0x23,0x03,0xED,0x53,0xE5,0x6E,0x99,0x52,
		0x1A,0xCD,0x26,0xDE,0x78,0xA7,0x87,0x73,0x97,0x91,0xCD,0x37,
		0x76,0x04,0x0C,0x80,0x91,0xDF,0x1D,0x1D,0x1B,0x9F,0xE9,0xAC,
		0x25,0x82,0x0C,0x1C,0xE6,0x91,0x51,0xFB,0xF6,0x26,0x3E,0x2D,
		0xF2,0x92,0x3E,0xC8,0x6D,0x35,0xD9,0x91,0xA2,0x99,0xEB,0xB5,
		0x9B,0xAF,0x5F,0x45,0x75,0x5B,0x1A,0x32,0x21,0xDE,0x96,0x14,
		0xD1,0x56,0xC9,0x30,0xD1,0x2A,0x42,0x31,0xE0,0xD7,0x57,0x6C,
		0x6C,0x86,0x00,0xCB,0x22,0x1C,0x71,0x7F,0x63,0x27,0xF4,0xCF,
		0x10,0xFB,0x6C,0x10,0xEA,0xDD,0x69,0xAA,0x88,0xF0,0xF7,0x05,
		0x37,0xE2,0xAD,0xC3,0x18,0x3F,0xF6,0x2C,0xFB,0x5C,0x53,0xF7,
		0x38,0x11,0x24,0x3A,0x04,0xE3,0x0E,0xCE,0xE7,0x3D,0x39,0xF1,
		0x00,0xA2,0x78,0xF0,0x4C,0x39,0xEF,0xFC,0x83,0x25,0x20,0xD1,
		0x21,0xB8,0x4D,0x36,0x0E,0x94,0xD2,0x11,0xFE,0x1C,0x86,0x2F,
		0xCA,0x7C,0x78,0x27,0x5E,0xD5,0x53,0x4A,0xD9,0x6C,0x4C,0x2B,
		0x82,0x24,0xCC,0x39,0xD9,0xB1,0x93,0x48,0xC5,0x75,0xAE,0xAB,
		0x99,0x80,0xD9,0xA3,0x0B,0x2F,0x74,0xF9,0xA8,0x48,0xA5,0x8B,
		0x64,0x67,0x9C,0xA2,0x96,0x22,0xF1,0x2B,
		};
	static unsigned char dh16384_g[]={
		0x02,
		};
	DH *dh;

	if ((dh=DH_new()) == NULL) return(NULL);
	dh->p=BN_bin2bn(dh16384_p,sizeof(dh16384_p),NULL);
	dh->g=BN_bin2bn(dh16384_g,sizeof(dh16384_g),NULL);
	if ((dh->p == NULL) || (dh->g == NULL))
		{ DH_free(dh); return(NULL); }
	return(dh);
	}
