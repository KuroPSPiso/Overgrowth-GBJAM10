#include "./bg.h"

unsigned char sprite_bg_cls[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char sprite_bg_top[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x01,0x01,0x03,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x01,0x01,0x03,0x03,
  0x07,0x07,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
  0x8D,0x8D,0xC1,0xC1,0x61,0x61,0xF1,0xF1,
  0x02,0x02,0x03,0x03,0x09,0x09,0x0C,0x0C,
  0x26,0x26,0x33,0x33,0x19,0x19,0x0C,0x0C,
  0x06,0x06,0x03,0x03,0x01,0x01,0x01,0x01,
  0x03,0x03,0x1F,0x1F,0x3F,0x23,0x7F,0x42,
  0x00,0x00,0x00,0x00,0x82,0x80,0xC7,0xC0,
  0x6D,0x60,0x37,0x30,0x92,0x90,0xB8,0xB8,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
  0xDE,0xDE,0xE0,0xE0,0xF8,0x18,0xF8,0x08,
  0xFF,0xC3,0xFF,0xE1,0xFF,0x11,0xFF,0x0F,
  0xFF,0x82,0xFF,0xE3,0xFF,0x3D,0xFF,0xF1,
  0xFF,0xC3,0xFF,0x83,0xFE,0x83,0xFD,0x82,
  0xFD,0x02,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xF8,0x08,0xF0,0x90,0xE0,0xE0,0x80,0x80,
  0x80,0x80,0x8F,0x8F,0x30,0x3F,0xF0,0xFF,
  0xC0,0xFF,0xE1,0x7F,0xE3,0x3F,0xF2,0x3F,
  0xF4,0x1F,0xFC,0x1F,0xF8,0x0F,0xFF,0x1F,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x81,0x01,0x02,0x03,0x07,0x07,0x07,0x04,
  0x7F,0x7F,0x80,0xFF,0x80,0xFF,0xFE,0xFF,
  0x0F,0x0F,0x1F,0x1F,0x3F,0x20,0x3F,0x20,
  0x00,0x00,0x1F,0x1F,0x61,0x7F,0x80,0xFF,
  0x00,0xFF,0x00,0xFF,0xFE,0xFF,0xFF,0x01,
  0xFF,0xFE,0x01,0xFF,0x00,0xFF,0x00,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1E,
  0x3F,0x20,0x1F,0x1E,0x0F,0x0F,0x1F,0x1F,
  0x1F,0x1F,0xDF,0xDF,0xCF,0xC8,0x7F,0xF8,
  0x9F,0xFF,0x8E,0xFF,0x1B,0xFE,0x31,0xFF,
  0x20,0xFF,0x60,0xFF,0xC0,0xFF,0x80,0xFF,
  0xFF,0x00,0xFF,0x00,0xDF,0xE0,0xEF,0xF0,
  0xF7,0xE8,0xF7,0xE8,0xF7,0x08,0xF7,0x08,
  0x7F,0x80,0x3F,0xC3,0xFC,0x07,0xF8,0xFF,
  0x18,0xFF,0x10,0xFF,0x11,0xFF,0x31,0xFF,
  0x00,0x00,0x07,0x07,0xCF,0xCF,0x33,0xF2,
  0x0B,0xFA,0x09,0xF9,0x08,0xF8,0xC8,0xF8,
  0xF8,0x78,0xF8,0x88,0xF8,0xF8,0x38,0xF8,
  0x0E,0xFE,0xFB,0xFB,0xFE,0x9E,0xFC,0x1C,
  0xC0,0xC0,0xE0,0x20,0xF0,0x30,0xF0,0xD0,
  0xE0,0xA0,0xC0,0xC0,0x00,0x00,0x00,0x00,
  0xFC,0x1C,0xFC,0x1C,0xFC,0x24,0xEC,0x14,
  0xEC,0x14,0xFC,0x0C,0xF8,0x38,0xCE,0xFE,
  0x87,0xFF,0x09,0xFF,0x18,0xFF,0x23,0xFF,
  0x44,0xFC,0xC5,0xFD,0x9D,0xFD,0x14,0xF4,
  0x00,0x00,0x80,0x80,0xE0,0xE0,0xE0,0xE0,
  0x20,0x20,0xA0,0xA0,0xB8,0xB8,0x28,0x28,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char sprite_bg_bottom[] = 
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x01,0x01,0x03,0x02,0x07,0x04,0x0F,0x08,
  0x1F,0x11,0x3F,0x23,0x3F,0x21,0x7F,0x47,
  0x7F,0x40,0x7F,0x4F,0xBF,0xC8,0xBF,0xC3,
  0xF1,0x91,0xFF,0x9F,0x7F,0x47,0xFD,0x9D,
  0xFB,0x1B,0xFA,0x3B,0xFC,0xFF,0xF8,0x0F,
  0xF0,0xFF,0xA0,0xBF,0xA0,0xBF,0xE0,0xFF,
  0xE0,0x7F,0xE0,0xFF,0xE0,0xFF,0xF0,0xFF,
  0xBF,0xC7,0xBF,0xC0,0x5F,0x67,0x5F,0x63,
  0xAF,0xB1,0xD7,0x58,0x57,0xD8,0x59,0xDE,
  0x44,0xC7,0x32,0xF3,0x11,0xF1,0x89,0xF9,
  0x8F,0xFF,0x90,0xFF,0x87,0xF8,0xC7,0xF8,
  0xFC,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xF5,0xFF,0xF5,0xFF,0x54,0xFF,0x06,
  0xFF,0x00,0x3F,0xC0,0xCF,0xF3,0x9F,0xE3,
  0x36,0xCF,0x79,0x86,0xFF,0x00,0xC0,0x3F,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0xC3,0x3F,0xFF,0x01,0xFF,0x00,0xFF,
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,
  0x00,0xFF,0x00,0xFF,0x08,0xFF,0x3E,0xFF,
  0xF1,0x11,0xF1,0x31,0xEE,0x3F,0xE0,0xFF,
  0x40,0x7F,0xC0,0xFF,0x80,0xFF,0x80,0xFF,
  0x00,0xFF,0x03,0xFF,0x04,0xFF,0x08,0xFF,
  0x08,0xFF,0x08,0xFF,0x04,0xFF,0x43,0xFF,
  0x0E,0xFF,0x06,0xFF,0x06,0xFF,0x87,0xFF,
  0xC7,0xFD,0xEF,0xBD,0xFF,0x99,0xFE,0xC2,
  0xFC,0x04,0xFF,0x1F,0xFF,0xF8,0xBF,0xC0,
  0x7F,0x80,0xF0,0x0F,0x87,0x7F,0x38,0xF8,
  0x60,0xFF,0x20,0xFF,0x3C,0xFF,0x0F,0xFF,
  0x80,0xFF,0x7F,0x7F,0x00,0x00,0x00,0x00,
  0x00,0x00,0xE7,0xE7,0xFF,0x38,0xFF,0x00,
  0xFF,0x03,0x1C,0xFC,0xE0,0xE0,0x00,0x00,
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0xC0,0xFF,
  0x7F,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,
  0x00,0xFF,0x80,0xFF,0x70,0xFF,0x1C,0xFF,
  0x04,0xFF,0x04,0xFF,0x0C,0xFF,0xF0,0xFF,
  0x22,0xFF,0x43,0xFF,0x43,0xFF,0x43,0xFE,
  0xFF,0xFE,0x4F,0xCC,0x87,0x84,0x4F,0xCC,
  0x37,0xFC,0x03,0xFE,0x03,0xFE,0x03,0xFE,
  0x01,0xFF,0x00,0xFF,0x01,0xFF,0x01,0xFF,
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0xC0,0xFF,
  0xC0,0xFF,0x40,0xFF,0xC0,0xFF,0x7F,0x7F,
  0x7F,0x7F,0xFF,0xFF,0xFF,0x01,0xFF,0x3D,
  0xFF,0xBC,0xFF,0x87,0xFF,0xF0,0xFF,0xFF,
  0x01,0xFF,0x01,0xFF,0x01,0xFF,0x02,0xFE,
  0x02,0xFE,0x02,0xFE,0x02,0xFE,0xE2,0xFE,
  0xFE,0xFE,0xFE,0xFA,0xFE,0xFA,0xFF,0xE3,
  0xFF,0x0F,0xFF,0xFF,0xFF,0x1F,0xFF,0xFF,
  0x33,0xF3,0xF0,0xF0,0xF8,0x18,0xFE,0x07,
  0xCF,0x3C,0x0F,0xF8,0xFF,0x08,0xFE,0x0D,
  0xFB,0x3F,0xF6,0x4E,0xFB,0x87,0xF9,0x87,
  0xFD,0x83,0xFF,0xC1,0x7F,0x41,0x3F,0x27,
  0xC8,0xC8,0x08,0x08,0x10,0x10,0x60,0xE0,
  0xF0,0x10,0xF8,0x08,0xE8,0x18,0x18,0xF8,
  0xF8,0xF8,0x4C,0x74,0xDE,0xE2,0x3E,0xC2,
  0xFE,0x02,0xFE,0x02,0xFC,0x0C,0xE4,0xFC,
  0x1A,0x1F,0x13,0x1E,0x13,0x1E,0x21,0x3F,
  0x20,0x3F,0x20,0x3F,0x40,0x7F,0x40,0x7F,
  0x40,0x7F,0x40,0x7F,0x20,0x3F,0x1F,0x1F,
  0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
  0x0E,0xF2,0xFE,0x02,0xFE,0x02,0xFE,0x02,
  0xFC,0x8C,0x74,0xFC,0x02,0xFE,0x02,0xFE,
  0x02,0xFE,0x02,0xFE,0x04,0xFC,0xF8,0xF8,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};