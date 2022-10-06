set(lexer_lib_name Php)

add_library(${lexer_lib_name} STATIC)

find_package(ANTLR REQUIRED)

set(antlr_lexer_target_name Antlr${lexer_lib_name}Lexer)
antlr_target(
    ${antlr_lexer_target_name}
    ${lexer_lib_name}Lexer.g4
    LEXER
)

set(antlr_parser_target_name Antlr${lexer_lib_name}Parser)
antlr_target(
    ${antlr_parser_target_name}
    ${lexer_lib_name}Parser.g4
    PARSER
    VISITOR
    DEPENDS_ANTLR ${antlr_lexer_target_name}
    COMPILE_FLAGS -lib ${ANTLR_AntlrPhpLexer_OUTPUT_DIR}
)


include(CompileOptions)
target_set_cxx_standard(${lexer_lib_name})

target_sources(
    ${lexer_lib_name}
    PRIVATE
        ${ANTLR_${antlr_lexer_target_name}_CXX_OUTPUTS}
        ${ANTLR_${antlr_parser_target_name}_CXX_OUTPUTS}
)

target_include_directories(
    ${lexer_lib_name}
    PUBLIC
        ${ANTLR_${antlr_lexer_target_name}_OUTPUT_DIR}
        ${ANTLR_${antlr_parser_target_name}_OUTPUT_DIR}
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(
    ${lexer_lib_name}
    PUBLIC
        antlr4
        Threads::Threads
)
