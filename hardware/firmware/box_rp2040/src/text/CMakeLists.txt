cmake_minimum_required(VERSION 3.12)

project(mcufont)

add_library(mcufont_decoder INTERFACE)

set(MCUFONT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../vendor/mcufont)

target_sources(mcufont_decoder INTERFACE
    ${MCUFONT_DIR}/decoder/mf_bwfont.c
    ${MCUFONT_DIR}/decoder/mf_encoding.c
    ${MCUFONT_DIR}/decoder/mf_font.c
    ${MCUFONT_DIR}/decoder/mf_justify.c
    ${MCUFONT_DIR}/decoder/mf_kerning.c
    ${MCUFONT_DIR}/decoder/mf_rlefont.c
    ${MCUFONT_DIR}/decoder/mf_scaledfont.c
    ${MCUFONT_DIR}/decoder/mf_wordwrap.c
)

target_include_directories(mcufont_decoder INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/mcufont/decoder
)
