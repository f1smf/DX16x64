/*
 * System10x16
 * The font data are defined as
 *
 * struct _FONT_ {
 *    uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *    uint8_t   font_Width_in_Pixel_for_fixed_drawing;
 *    uint8_t   font_Height_in_Pixel_for_all_characters;
 *    unit8_t   font_First_Char;
 *    uint8_t   font_Char_Count;
 *
 *    uint8_t   font_Char_Widths[font_Last_Char - font_First_Char +1];
 *              // for each character the separate width in pixels,
 *              // characters < 128 have an implicit virtual right empty row
 *
 *    uint8_t   font_data[];
 *              // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef SYSTEM10x16_H
#define SYSTEM10x16_H

#define SYSTEM10x16_WIDTH 10
#define SYSTEM10x16_HEIGHT 16

#define SystemFont10x16 System10x16

static uint8_t System10x16[] PROGMEM = {
   0x0, 0x0, // size of zero indicates fixed width font, actual length is width * height
   0x0a, // width
   0x010, // height
   0x20, // first char
   0x60, // char count

   // font data
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // (space)
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x0D, // !
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00, // "
     0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x80,0x00,0x90,0x0C,0xD0,0x03,0xBC,0x00,0x93,0x0C, // #
     0xD0,0x03,0xBC,0x00,0x93,0x00,0x90,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x0E,0x0C,0x13,0x08,0x21,0x08, // $
     0xFF,0x1F,0xC1,0x08,0x81,0x07,0x00,0x00,0x00,0x00,
     0x0E,0x08,0x11,0x04,0x11,0x02,0x91,0x01,0x4E,0x00, // %
     0x20,0x07,0x98,0x08,0x84,0x08,0x82,0x08,0x01,0x07,
     0x80,0x03,0x40,0x04,0x2E,0x08,0x31,0x08,0xD1,0x08, // &
     0x99,0x09,0x0E,0x0E,0x00,0x0C,0x00,0x0B,0xC0,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00, // '
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x03,0x0C,0x0C, // (
     0x06,0x18,0x02,0x10,0x01,0x20,0x01,0x20,0x00,0x00,
     0x00,0x00,0x01,0x20,0x01,0x20,0x02,0x10,0x06,0x18, // )
     0x0C,0x0C,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x04,0x00,0x0C,0x00,0x78,0x00,0x27,0x00, // *
     0x78,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
     0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0xF0,0x0F, // +
     0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4C,0x00,0x3C, // ,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00, // -
     0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x0C, // .
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x20,0x00,0x18,0x00,0x06,0x80,0x01, // /
     0x60,0x00,0x18,0x00,0x06,0x00,0x01,0x00,0x00,0x00,
     0x00,0x00,0xF8,0x01,0x06,0x06,0x01,0x08,0x01,0x08, // 0
     0x01,0x08,0x06,0x06,0xF8,0x01,0x00,0x00,0x00,0x00,
     0x00,0x00,0x02,0x08,0x02,0x08,0x02,0x08,0xFF,0x0F, // 1
     0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0x03,0x0C,0x01,0x0A,0x01,0x09,0x81,0x08, // 2
     0x61,0x08,0x1E,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x01,0x08,0x21,0x08,0x21,0x08, // 3
     0x21,0x08,0xDE,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
     0x80,0x01,0x60,0x01,0x10,0x01,0x0C,0x01,0x02,0x01, // 4
     0xFF,0x0F,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x1F,0x08,0x11,0x08,0x11,0x08, // 5
     0x21,0x04,0xC1,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0xF8,0x03,0x26,0x04,0x11,0x08,0x11,0x08, // 6
     0x11,0x08,0x21,0x04,0xC0,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0x01,0x00,0x01,0x0C,0x81,0x03,0x61,0x00, // 7
     0x19,0x00,0x05,0x00,0x03,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x8E,0x07,0x51,0x08,0x21,0x08,0x21,0x08, // 8
     0x51,0x08,0xD1,0x04,0x0E,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3C,0x00,0x42,0x08,0x81,0x08,0x81,0x08, // 9
     0x81,0x08,0x42,0x06,0xFC,0x01,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0C,0x30,0x0C, // :
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x4C,0x30,0x3C, // ;
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x80,0x01,0x80,0x01,0x40,0x02, // <
     0x40,0x02,0x20,0x04,0x20,0x04,0x10,0x08,0x00,0x00,
     0x00,0x00,0x40,0x02,0x40,0x02,0x40,0x02,0x40,0x02, // =
     0x40,0x02,0x40,0x02,0x40,0x02,0x40,0x02,0x00,0x00,
     0x00,0x00,0x10,0x08,0x20,0x04,0x20,0x04,0x40,0x02, // >
     0x40,0x02,0x80,0x01,0x80,0x01,0x00,0x00,0x00,0x00,
     0x00,0x00,0x07,0x00,0x01,0x00,0x81,0x0D,0x41,0x00, // ?
     0x21,0x00,0x13,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
     0xF8,0x01,0x0C,0x06,0x02,0x0C,0xF1,0x09,0x09,0x0A, // @
     0x05,0x0B,0xC5,0x0D,0xFE,0x03,0x00,0x02,0x00,0x02,
     0x00,0x08,0x00,0x07,0xC0,0x01,0x38,0x01,0x0C,0x01, // A
     0x18,0x01,0x60,0x01,0x80,0x01,0x00,0x06,0x00,0x08,
     0x00,0x00,0xFC,0x0F,0x44,0x08,0x44,0x08,0x44,0x08, // B
     0x44,0x08,0xA4,0x08,0x18,0x07,0x00,0x00,0x00,0x00,
     0xE0,0x01,0x18,0x06,0x08,0x04,0x04,0x08,0x04,0x08, // C
     0x04,0x08,0x04,0x08,0x0C,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x04,0x08,0x04,0x08,0x04,0x08, // D
     0x04,0x08,0x08,0x04,0xF0,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x84,0x08,0x84,0x08,0x84,0x08, // E
     0x84,0x08,0x84,0x08,0x04,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x84,0x00,0x84,0x00,0x84,0x00, // F
     0x84,0x00,0x84,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0xE0,0x01,0x18,0x06,0x08,0x04,0x04,0x08, // G
     0x04,0x08,0x84,0x08,0x84,0x08,0x8C,0x0F,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x80,0x00,0x80,0x00,0x80,0x00, // H
     0x80,0x00,0x80,0x00,0xFC,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0x04,0x08,0x04,0x08,0x04,0x08,0xFC,0x0F, // I
     0x04,0x08,0x04,0x08,0x04,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x08,0x04,0x08,0x04,0x08, // J
     0x04,0x08,0xFC,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x40,0x00,0xC0,0x00,0x20,0x01, // K
     0x10,0x02,0x08,0x02,0x04,0x04,0x00,0x08,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x00,0x08,0x00,0x08,0x00,0x08,// L
     0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00, 
     0xFC,0x0F,0x1C,0x00,0xF0,0x00,0x80,0x03,0x00,0x03, // M
     0xE0,0x00,0x1C,0x00,0xFC,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x08,0x00,0x30,0x00,0xC0,0x00, // N
     0x00,0x03,0x00,0x04,0xFC,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0xF0,0x03,0x08,0x04,0x04,0x08,0x04,0x08, // O
     0x04,0x08,0x04,0x08,0x08,0x04,0xF0,0x03,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x84,0x00,0x84,0x00,0x84,0x00, // P
     0x84,0x00,0x44,0x00,0x38,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0xF0,0x03,0x08,0x04,0x04,0x08,0x04,0x08, // Q
     0x04,0x08,0x04,0x18,0x08,0x24,0xF0,0x23,0x00,0x00,
     0x00,0x00,0xFC,0x0F,0x84,0x00,0x84,0x00,0x84,0x01, // R
     0x44,0x02,0x38,0x04,0x00,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0x38,0x0C,0x24,0x08,0x44,0x08,0x44,0x08, // S
     0x84,0x08,0x84,0x04,0x0C,0x07,0x00,0x00,0x00,0x00,
     0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0xFC,0x0F, // T
     0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x00,0x00,
     0x00,0x00,0xFC,0x03,0x00,0x0C,0x00,0x08,0x00,0x08, // U
     0x00,0x08,0x00,0x04,0xFC,0x03,0x00,0x00,0x00,0x00,
     0x04,0x00,0x18,0x00,0xE0,0x00,0x00,0x03,0x00,0x0C, // V
     0x00,0x0C,0x80,0x03,0x60,0x00,0x18,0x00,0x04,0x00,
     0x0C,0x00,0xF0,0x01,0x00,0x0E,0x80,0x07,0x70,0x00, // W
     0xE0,0x00,0x00,0x07,0x00,0x0E,0xF0,0x01,0x0C,0x00,
     0x04,0x08,0x08,0x04,0x10,0x02,0x20,0x01,0xC0,0x00, // X
     0xC0,0x00,0x20,0x01,0x10,0x02,0x08,0x04,0x04,0x08,
     0x04,0x00,0x08,0x00,0x30,0x00,0x40,0x00,0x80,0x0F, // Y
     0x40,0x00,0x20,0x00,0x10,0x00,0x08,0x00,0x04,0x00,
     0x00,0x00,0x04,0x0C,0x04,0x0A,0x04,0x09,0x84,0x08, // Z
     0x44,0x08,0x24,0x08,0x14,0x08,0x0C,0x08,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x3F,0x01,0x20, // [
     0x01,0x20,0x01,0x20,0x01,0x20,0x00,0x00,0x00,0x00,
     0x00,0x00,0x01,0x00,0x06,0x00,0x18,0x00,0x60,0x00, // "\"
     0x80,0x01,0x00,0x06,0x00,0x18,0x00,0x20,0x00,0x00,
     0x00,0x00,0x01,0x20,0x01,0x20,0x01,0x20,0x01,0x20, // ]
     0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x01,0x20,0x01,0x20,0x01,0x20,0x01,0x20, // ]
     0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x02,0x80,0x01,0x70,0x00,0x1C,0x00, // ^
     0x07,0x00,0x38,0x00,0xC0,0x01,0x00,0x02,0x00,0x00,
     0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10, // _
     0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // `
     0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x06,0x10,0x09,0x90,0x08,0x90,0x08, // a
     0x90,0x04,0xE0,0x0F,0x00,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFF,0x0F,0x20,0x04,0x10,0x08,0x10,0x08, // b
     0x10,0x08,0x30,0x04,0xC0,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0x20,0x04,0x10,0x08,0x10,0x08, // c
     0x10,0x08,0x10,0x08,0x10,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0x20,0x0C,0x10,0x08,0x10,0x08, // d
     0x10,0x08,0x20,0x04,0xFF,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0xA0,0x04,0x90,0x08,0x90,0x08, // e
     0x90,0x08,0x90,0x08,0xE0,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0x10,0x00,0x10,0x00,0xFE,0x0F,0x12,0x00, // f
     0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0x20,0x4C,0x10,0x48,0x10,0x48, // g
     0x10,0x48,0x20,0x24,0xF0,0x1F,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFF,0x0F,0x40,0x00,0x20,0x00,0x10,0x00, // h
     0x10,0x00,0x10,0x00,0xE0,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0x10,0x00,0x10,0x00,0x13,0x00,0xF3,0x0F, // i
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x40,0x10,0x40,0x10,0x40,0x13,0x40, // j
     0xF3,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0xFF,0x0F,0x80,0x00,0x80,0x01,0x40,0x02, // k
     0x20,0x02,0x20,0x04,0x10,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00, // l
     0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0xF0,0x0F,0x20,0x00,0x10,0x00,0x10,0x00,0xE0,0x0F, // m
     0x20,0x00,0x10,0x00,0x10,0x00,0xE0,0x0F,0x00,0x00,
     0x00,0x00,0xF0,0x0F,0x60,0x00,0x20,0x00,0x10,0x00, // n
     0x10,0x00,0x10,0x00,0xE0,0x0F,0x00,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0x20,0x04,0x10,0x08,0x10,0x08, // o
     0x10,0x08,0x20,0x04,0xC0,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0xF0,0x7F,0x20,0x04,0x10,0x08,0x10,0x08, // p
     0x10,0x08,0x30,0x04,0xC0,0x03,0x00,0x00,0x00,0x00,
     0x00,0x00,0xC0,0x03,0x20,0x0C,0x10,0x08,0x10,0x08, // q
     0x10,0x08,0x20,0x04,0xF0,0x7F,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0xF0,0x0F,0x40,0x00,0x20,0x00, // r
     0x10,0x00,0x10,0x00,0x70,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x60,0x0C,0x90,0x08,0x90,0x08,0x10,0x09, // s
     0x10,0x09,0x10,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x10,0x00,0x10,0x00,0xFC,0x07,0x10,0x08, // t
     0x10,0x08,0x10,0x08,0x10,0x08,0x00,0x00,0x00,0x00,
     0x00,0x00,0xF0,0x07,0x00,0x08,0x00,0x08,0x00,0x08, // u
     0x00,0x04,0xF0,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
     0x10,0x00,0xE0,0x00,0x00,0x03,0x00,0x0C,0x00,0x08, // v
     0x00,0x06,0x80,0x01,0x60,0x00,0x10,0x00,0x00,0x00,
     0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x07,0xE0,0x00, // w
     0xC0,0x00,0x00,0x07,0x00,0x0C,0xC0,0x03,0x30,0x00,
     0x00,0x00,0x10,0x08,0x20,0x04,0x40,0x02,0x80,0x01, // x
     0x80,0x01,0x40,0x02,0x20,0x04,0x10,0x08,0x00,0x00,
     0x10,0x40,0x60,0x40,0x80,0x41,0x00,0x23,0x00,0x1C, // y
     0x00,0x0C,0x00,0x03,0x80,0x00,0x60,0x00,0x10,0x00,
     0x00,0x00,0x10,0x08,0x10,0x0C,0x10,0x0A,0x10,0x09, // z
     0x90,0x08,0x50,0x08,0x30,0x08,0x10,0x08,0x00,0x00,
     0x00,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x7E,0x1F, // {
     0x01,0x20,0x01,0x20,0x01,0x20,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x3F, // |
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x01,0x20,0x01,0x20,0x01,0x20, // }
     0x7E,0x1F,0x80,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x1E,0x00,0x21,0x00,0x21,0x00, // ->
     0x21,0x00,0x21,0x00,0x1E,0x00,0x00,0x00,0x00,0x00};
     0x00,0x00,0x00,0x00,0x1E,0x00,0x21,0x00,0x21,0x00, // ->
     0x21,0x00,0x21,0x00,0x1E,0x00,0x00,0x00,0x00,0x00};
     0x00,0x00,0x00,0x00,0x1E,0x00,0x21,0x00,0x21,0x00, //  <-
     0x21,0x00,0x21,0x00,0x1E,0x00,0x00,0x00,0x00,0x00}; 
};
#endif
// No newline at end of file
