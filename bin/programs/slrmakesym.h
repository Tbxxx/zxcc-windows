char tpa[] = {
0x31,0xbb,0x05,0x11,0x21,0x05,0x0e,0x09,0xcd,0x05,0x00,0x18,0x21,0x43,0x6f,0x70,0x79,0x72,0x69,0x67,
0x68,0x74,0x20,0x28,0x43,0x29,0x20,0x31,0x39,0x38,0x35,0x20,0x62,0x79,0x20,0x53,0x4c,0x52,0x20,0x53,
0x79,0x73,0x74,0x65,0x6d,0x73,0x21,0x80,0x00,0x7e,0xb7,0x28,0x35,0x2c,0x5d,0x4f,0x06,0x00,0x09,0x36,
0x0d,0x6b,0x78,0xb1,0x28,0x54,0x3e,0x2f,0xed,0xb1,0x20,0x4e,0x7e,0x2c,0x11,0xf5,0x04,0xfe,0x50,0x28,
0x1f,0x11,0xf7,0x04,0xfe,0x44,0x28,0x18,0x11,0xf9,0x04,0xfe,0x43,0x28,0x11,0xfe,0x55,0x20,0x07,0x3e,
0xff,0x32,0xf4,0x04,0x18,0xd4,0x11,0x1b,0x04,0xc3,0x4b,0x02,0xd5,0xeb,0x21,0x00,0x00,0x1a,0xd6,0x30,
0x38,0x14,0xfe,0x0a,0x38,0x06,0xd6,0x07,0xfe,0x10,0x30,0x0a,0x29,0x29,0x29,0x29,0x85,0x6f,0x13,0x0d,
0x20,0xe7,0xeb,0xe3,0x73,0x23,0x72,0xe1,0x18,0xa8,0x11,0x65,0x00,0x1a,0xfe,0x20,0x20,0x08,0x21,0xfb,
0x04,0x01,0x03,0x00,0xed,0xb0,0xaf,0x32,0x68,0x00,0x11,0x5c,0x00,0x0e,0x0f,0xcd,0x05,0x00,0x3c,0x11,
0xc7,0x03,0xca,0x4b,0x02,0xaf,0x32,0x7c,0x00,0x21,0x5c,0x00,0x11,0xfe,0x04,0x01,0x09,0x00,0xed,0xb0,
0x11,0xfe,0x04,0x0e,0x13,0xcd,0x05,0x00,0x11,0xfe,0x04,0x0e,0x16,0xcd,0x05,0x00,0x3c,0x11,0xd6,0x03,
0x28,0x6d,0xaf,0x32,0x1e,0x05,0x21,0x96,0x03,0x06,0x0e,0xcd,0x51,0x02,0x38,0x34,0xbe,0x20,0xf3,0x23,
0x10,0xf5,0xcd,0x72,0x02,0x38,0xeb,0x3a,0x59,0x05,0xfe,0x20,0x28,0x1d,0xfe,0x23,0x28,0xf0,0x2a,0xf5,
0x04,0xfe,0x27,0x28,0x0a,0x2a,0xf7,0x04,0xfe,0x22,0x28,0x03,0x2a,0xf9,0x04,0xed,0x5b,0x57,0x05,0x19,
0x22,0x57,0x05,0xcd,0xef,0x02,0x18,0xd2,0xed,0x5b,0x51,0x05,0x21,0x00,0x10,0xb7,0xed,0x52,0x28,0x0e,
0x11,0x7f,0x00,0x19,0x29,0x44,0x2a,0x4f,0x05,0x36,0x1a,0xcd,0xcb,0x02,0x11,0xfe,0x04,0x0e,0x10,0xcd,
0x05,0x00,0x3c,0x11,0xe5,0x03,0x28,0x03,0x11,0x0e,0x04,0x0e,0x09,0xcd,0x05,0x00,0xc7,0xe5,0x2a,0x55,
0x05,0x7c,0xb5,0xcc,0x60,0x03,0x38,0x13,0x2b,0x22,0x55,0x05,0x2a,0x53,0x05,0x7e,0x23,0x22,0x53,0x05,
0xe1,0xfe,0x1a,0x28,0x03,0xb7,0xc9,0xe1,0x37,0xc9,0xcd,0x51,0x02,0x38,0xa9,0xfe,0x0c,0x37,0xc8,0xfe,
0x21,0x38,0xf3,0x21,0x00,0x00,0x06,0x04,0x29,0x29,0x29,0x29,0xd6,0x30,0x38,0x35,0xfe,0x0a,0x38,0x06,
0xd6,0x07,0xfe,0x10,0x30,0x2b,0x85,0x6f,0xcd,0x51,0x02,0x38,0x29,0x10,0xe5,0x22,0x57,0x05,0x32,0x59,
0x05,0xcd,0x51,0x02,0x38,0x1c,0xfe,0x20,0x20,0x13,0x21,0x5a,0x05,0xcd,0x51,0x02,0x38,0x10,0x77,0x23,
0xfe,0x21,0x30,0xf5,0x2b,0x36,0x00,0xb7,0xc9,0x11,0xf2,0x03,0x18,0x85,0x11,0xa4,0x03,0x18,0x80,0x11,
0xbb,0x15,0x21,0x80,0x00,0x19,0xe5,0xc5,0x0e,0x1a,0xcd,0x05,0x00,0x11,0xfe,0x04,0x0e,0x15,0xcd,0x05,
0x00,0xb7,0x20,0x05,0xc1,0xd1,0x10,0xe6,0xc9,0x11,0xbc,0x03,0xc3,0x4b,0x02,0x2a,0x57,0x05,0x7c,0xcd,
0x3d,0x03,0x7d,0xcd,0x3d,0x03,0x3e,0x20,0xcd,0x16,0x03,0x21,0x5a,0x05,0x18,0x07,0xcd,0x50,0x03,0xcd,
0x16,0x03,0x23,0x7e,0xb7,0x20,0xf5,0x3e,0x0d,0xcd,0x16,0x03,0x3e,0x0a,0xe5,0x2a,0x4f,0x05,0x77,0x23,
0x22,0x4f,0x05,0x2a,0x51,0x05,0x2b,0x22,0x51,0x05,0x7c,0xb5,0x20,0x11,0x06,0x20,0xcd,0xcb,0x02,0x21,
0xbb,0x15,0x22,0x4f,0x05,0x21,0x00,0x10,0x22,0x51,0x05,0xe1,0xc9,0xf5,0x1f,0x1f,0x1f,0x1f,0xcd,0x46,
0x03,0xf1,0xe6,0x0f,0xc6,0x90,0x27,0xce,0x40,0x27,0x18,0xc6,0x47,0x3a,0xf4,0x04,0xb7,0x78,0xc8,0xfe,
0x61,0xd8,0xfe,0x7b,0xd0,0xe6,0x5f,0xc9,0xd5,0xc5,0x11,0xbb,0x05,0xed,0x53,0x53,0x05,0x06,0x20,0x21,
0x80,0x00,0x19,0xe5,0xc5,0x0e,0x1a,0xcd,0x05,0x00,0x11,0x5c,0x00,0x0e,0x14,0xcd,0x05,0x00,0xb7,0xc1,
0xd1,0x20,0x02,0x10,0xe6,0x3e,0x20,0x90,0x67,0x2e,0x00,0xcb,0x3c,0xcb,0x1d,0x7c,0xb5,0xc1,0xd1,0xc0,
0x37,0xc9,0x0a,0x53,0x79,0x6d,0x62,0x6f,0x6c,0x20,0x54,0x61,0x62,0x6c,0x65,0x3a,0x55,0x6e,0x65,0x78,
0x70,0x65,0x63,0x74,0x65,0x64,0x20,0x45,0x4f,0x46,0x2c,0x20,0x41,0x62,0x6f,0x72,0x74,0x65,0x64,0x24,
0x44,0x69,0x73,0x6b,0x20,0x46,0x75,0x6c,0x6c,0x21,0x24,0x46,0x69,0x6c,0x65,0x20,0x4e,0x6f,0x74,0x20,
0x46,0x6f,0x75,0x6e,0x64,0x24,0x44,0x69,0x72,0x65,0x63,0x74,0x6f,0x72,0x79,0x20,0x46,0x75,0x6c,0x6c,
0x24,0x53,0x79,0x73,0x74,0x65,0x6d,0x20,0x45,0x72,0x72,0x6f,0x72,0x24,0x45,0x72,0x72,0x6f,0x72,0x20,
0x44,0x65,0x63,0x6f,0x64,0x69,0x6e,0x67,0x20,0x53,0x79,0x6d,0x62,0x6f,0x6c,0x20,0x56,0x61,0x6c,0x75,
0x65,0x24,0x2e,0x53,0x59,0x4d,0x20,0x63,0x72,0x65,0x61,0x74,0x65,0x64,0x24,0x46,0x69,0x6c,0x65,0x6e,
0x61,0x6d,0x65,0x20,0x6f,0x66,0x20,0x6c,0x69,0x73,0x74,0x20,0x66,0x69,0x6c,0x65,0x20,0x72,0x65,0x71,
0x75,0x69,0x72,0x65,0x64,0x2c,0x20,0x77,0x69,0x74,0x68,0x20,0x6f,0x70,0x74,0x69,0x6f,0x6e,0x61,0x6c,
0x20,0x70,0x61,0x72,0x61,0x6d,0x65,0x74,0x65,0x72,0x73,0x2e,0x0d,0x0a,0x55,0x73,0x65,0x3a,0x20,0x20,
0x20,0x4d,0x41,0x4b,0x45,0x53,0x59,0x4d,0x20,0x46,0x69,0x6c,0x65,0x6e,0x61,0x6d,0x65,0x5b,0x2e,0x65,
0x78,0x74,0x5d,0x5b,0x2f,0x50,0x58,0x58,0x58,0x58,0x5d,0x5b,0x2f,0x44,0x58,0x58,0x58,0x58,0x5d,0x5b,
0x2f,0x43,0x58,0x58,0x58,0x58,0x5d,0x5b,0x2f,0x55,0x5d,0x0d,0x0a,0x77,0x68,0x65,0x72,0x65,0x20,0x58,
0x58,0x58,0x58,0x20,0x69,0x73,0x20,0x61,0x20,0x48,0x65,0x78,0x20,0x6f,0x66,0x66,0x73,0x65,0x74,0x20,
0x74,0x6f,0x20,0x62,0x65,0x20,0x61,0x64,0x64,0x65,0x64,0x20,0x74,0x6f,0x20,0x52,0x65,0x6c,0x6f,0x63,
0x61,0x74,0x61,0x62,0x6c,0x65,0x20,0x69,0x74,0x65,0x6d,0x73,0x2c,0x20,0x61,0x6e,0x64,0x0d,0x0a,0x2f,
0x55,0x20,0x73,0x65,0x6c,0x65,0x63,0x74,0x73,0x20,0x75,0x70,0x70,0x65,0x72,0x20,0x63,0x61,0x73,0x65,
0x20,0x63,0x6f,0x6e,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4c,
0x53,0x54,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x53,0x59,0x4d,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4d,0x41,0x4b,
0x45,0x53,0x59,0x4d,0x20,0x2d,0x20,0x43,0x6f,0x70,0x79,0x72,0x69,0x67,0x68,0x74,0x20,0x28,0x63,0x29,
0x20,0x31,0x39,0x38,0x35,0x20,0x62,0x79,0x20,0x53,0x4c,0x52,0x20,0x53,0x79,0x73,0x74,0x65,0x6d,0x73,
0x0d,0x0a,0x24,0xbb,0x15,0x00,0x10,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
