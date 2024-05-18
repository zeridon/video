/* Configuration constants for mcufont. */

#pragma once

#include <stdint.h>
#define PROGMEM
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const uint16_t *)(addr))


/*******************************************************
 * Configuration settings related to build environment *
 *******************************************************/

/* Name of the file that contains all the included fonts. */
#ifndef MF_FONT_FILE_NAME
#define MF_FONT_FILE_NAME "fonts_internal.cin"
#endif

#define MF_DEFAULT_FONT mf_rlefont_comic_shanns_18.font

/*****************************************
 * Configuration settings related to API *
 *****************************************/

/* Encoding for the input data.
 * With the unicode encodings, the library supports the range of unicode
 * characters 0x0000-0xFFFF (the Basic Multilingual Plane).
 *
 * ASCII: Plain ascii (somewhat works with ISO8859-1 also)
 * UTF8:  UTF8 encoding (variable number of bytes)
 * UTF16: UTF16 encoding (2 bytes per character, compatible with UCS-2)
 * WCHAR: Use compiler's wchar_t (usually same as UTF16)
 */
#define MF_ENCODING_ASCII 0
#define MF_ENCODING_UTF8  1
#define MF_ENCODING_UTF16 2
#define MF_ENCODING_WCHAR 3
#ifndef MF_ENCODING
#define MF_ENCODING MF_ENCODING_UTF8
#endif


/************************************************************************
 * Configuration settings related to visual appearance of rendered text *
 ************************************************************************/

/* Minimum space between characters, in percents of the glyph width.
 * Increasing this causes the kerning module to leave more space between
 * characters.
 */
#ifndef MF_KERNING_SPACE_PERCENT
#define MF_KERNING_SPACE_PERCENT 15
#endif

/* Minimum space between characters, in pixels. Added to the percentual
 * spacing. This pixel-based value guarantees enough space even with small
 * fonts.
 */
#ifndef MF_KERNING_SPACE_PIXELS
#define MF_KERNING_SPACE_PIXELS 3
#endif

/* Maximum adjustment done by the kerning algorithm, as percent of the
 * glyph width.
 */
#ifndef MF_KERNING_LIMIT
#define MF_KERNING_LIMIT 20
#endif

/* Spacing of tabulator stops. The value is multiplied by the width of the
 * 'm' character in the current font.
 */
#ifndef MF_TABSIZE
#define MF_TABSIZE 8
#endif


/*************************************************************************
 * Configuration settings to strip down library to reduce resource usage *
 *************************************************************************/

/* Enable or disable the kerning module.
 * Disabling it saves some code size and run time, but causes the spacing
 * between characters to be less consistent.
 * Can be safely disabled when using a monospace font.
 * Makes text rendering about twice slower.
 */
#ifndef MF_USE_KERNING
#define MF_USE_KERNING 0
#endif

/* Enable or disable the advanced word wrap algorithm.
 * If disabled, uses a simpler algorithm.
 */
#ifndef MF_USE_ADVANCED_WORDWRAP
#define MF_USE_ADVANCED_WORDWRAP 0
#endif

/* Enable of disable the justification algorithm.
 * If disabled, mf_render_justified renders just left-aligned.
 */
#ifndef MF_USE_JUSTIFY
#define MF_USE_JUSTIFY 0
#endif

/* Enable or disable the center and right alignment code.
 * If disabled, any alignment results in MF_ALIGN_LEFT.
 */
#ifndef MF_USE_ALIGN
#define MF_USE_ALIGN 1
#endif

/* Enable or disable the support for tab alignment.
 * If disabled, tabs will be rendered as regular space character.
 */
#ifndef MF_USE_TABS
#define MF_USE_TABS 0
#endif

/* Number of vertical zones to use when computing kerning.
 * Larger values give more accurate kerning, but are slower and use somewhat
 * more memory. There is no point to increase this beyond the height of the
 * font.
 */
#ifndef MF_KERNING_ZONES
#define MF_KERNING_ZONES 16
#endif
