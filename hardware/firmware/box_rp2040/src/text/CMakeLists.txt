cmake_minimum_required(VERSION 3.12)

project(mcufont)

set(MCUFONT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../vendor/mcufont)

ExternalProject_Add(mcufont_encoder
    PREFIX mcufont_encoder
    SOURCE_DIR ${MCUFONT_DIR}/encoder
    CMAKE_ARGS "-DCMAKE_MAKE_PROGRAM:FILEPATH=${CMAKE_MAKE_PROGRAM}"
    BINARY_DIR ${CMAKE_BINARY_DIR}/mcufont_encoder
    BUILD_ALWAYS 1
    INSTALL_COMMAND ""
)

set(MCUFONT_ENCODER ${CMAKE_BINARY_DIR}/mcufont_encoder/mfencoder)
set(COMPILED_FONT_DIR ${CMAKE_BINARY_DIR}/fonts)
set(COMPILED_FONT_NAMES)
set(COMPILED_FONT_FILES)

function(GENERATE_FONT NAME SRC GLYPHS SIZE)
    set(DEST ${COMPILED_FONT_DIR}/${NAME}.cin)
    set(COMPILED_FONT_NAMES ${COMPILED_FONT_NAMES} ${NAME} PARENT_SCOPE)
    set(COMPILED_FONT_FILES ${COMPILED_FONT_FILES} ${DEST} PARENT_SCOPE)
    add_custom_command(
        OUTPUT ${DEST}
        COMMAND mkdir -p ${COMPILED_FONT_DIR}
        COMMAND cp ${SRC} ${DEST}.ttf
        COMMAND "${MCUFONT_ENCODER}" import_ttf ${DEST}.ttf ${SIZE}
        COMMAND "${MCUFONT_ENCODER}" filter ${DEST}${SIZE}.dat ${GLYPHS}
        COMMAND "${MCUFONT_ENCODER}" rlefont_optimize ${DEST}${SIZE}.dat 50
        COMMAND "${MCUFONT_ENCODER}" rlefont_export ${DEST}${SIZE}.dat ${DEST}
        DEPENDS ${SRC}
        DEPENDS mcufont_encoder
        VERBATIM
    )
endfunction()

# specify required fonts here
# generate_font(dejavu_sans_12
#     ${MCUFONT_DIR}/fonts/DejaVuSans.ttf
#     "0-255 0x2010-0x2015"
#     12
# )
#
# generate_font(dejavu_serif_12
#     ${MCUFONT_DIR}/fonts/DejaVuSerif.ttf
#     "0-255 0x2010-0x2015"
#     12
# )

generate_font(comic_shanns_18
    "${CMAKE_CURRENT_LIST_DIR}/../../vendor/comic-shanns/v2/comic shanns 2.ttf"
    "0-255 0x2010-0x2015"
    18
)

set(MCUFONT_CONF_HEADER ${CMAKE_CURRENT_LIST_DIR}/mf_config.h)
set(FONTS_INCLUDE_INTERNAL ${COMPILED_FONT_DIR}/fonts_internal.cin)
set(FONT_HEADER_DIR ${COMPILED_FONT_DIR}/include)
set(FONT_HEADER ${FONT_HEADER_DIR}/fonts.h)

add_custom_command(
    # yes, mcufont is designed so that "fonts.h" *includes* the generated fonts
    # they make sure to include it in only one place
    OUTPUT ${FONTS_INCLUDE_INTERNAL}
    COMMAND bash -c "echo -n > ${FONTS_INCLUDE_INTERNAL}"
    COMMAND bash -c "while read -d ';' font; do echo '#include \"'\${font}.cin'\"' >> ${FONTS_INCLUDE_INTERNAL}; done <<< '${COMPILED_FONT_NAMES};'"
    DEPENDS ${COMPILED_FONT_FILES}
    VERBATIM
)

add_custom_command(
    # generate a `fonts.h` that contains extern definitions for all font structs
    OUTPUT ${FONT_HEADER}
    COMMAND mkdir -p ${FONT_HEADER_DIR}
    COMMAND bash -c "echo -n > ${FONT_HEADER}"
    COMMAND bash -c "while read -d ';' font; do echo 'extern const struct mf_rlefont_s mf_rlefont_'\${font}';' >> ${FONT_HEADER}; done <<< '${COMPILED_FONT_NAMES};'"
    DEPENDS ${COMPILED_FONT_FILES}
    VERBATIM
)

add_library(mcufont_text ${FONTS_INCLUDE_INTERNAL} ${FONT_HEADER})

target_sources(mcufont_text PRIVATE
    ${MCUFONT_DIR}/decoder/mf_bwfont.c
    ${MCUFONT_DIR}/decoder/mf_encoding.c
    ${MCUFONT_DIR}/decoder/mf_font.c
    ${MCUFONT_DIR}/decoder/mf_justify.c
    ${MCUFONT_DIR}/decoder/mf_kerning.c
    ${MCUFONT_DIR}/decoder/mf_rlefont.c
    ${MCUFONT_DIR}/decoder/mf_scaledfont.c
    ${MCUFONT_DIR}/decoder/mf_wordwrap.c
)

# override the default config with ours
target_compile_options(mcufont_text BEFORE PRIVATE -include ${MCUFONT_CONF_HEADER})

target_include_directories(mcufont_text
    PRIVATE
        ${COMPILED_FONT_DIR}
    PUBLIC
        ${FONT_HEADER_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
        ${MCUFONT_DIR}/decoder
)
