#ifndef J65_H
#define J65_H

#include <stdint.h>

enum j65_event {
    J65_NULL        = 0,
    J65_FALSE       = 1,
    J65_TRUE        = 2,
    J65_INTEGER     = 3,        /* integer and string */
    J65_NUMBER      = 4,        /* string */
    J65_STRING      = 5,        /* string */
    J65_KEY         = 6,        /* string */
    J65_START_OBJ   = 7,
    J65_END_OBJ     = 8,
    J65_START_ARRAY = 9,
    J65_END_ARRAY   = 10,
};

enum j65_status {
    J65_DONE      = 1,
    J65_WANT_MORE = 2,

    /* errors */
    J65_PARSE_ERROR        = -128,
    J65_ILLEGAL_CHAR,
    J65_ILLEGAL_ESCAPE,
    J65_NESTING_TOO_DEEP,
    J65_STRING_TOO_LONG,
    J65_EXPECTED_STRING,
    J65_EXPECTED_COLON,
    J65_EXPECTED_COMMA,
    J65_EXPECTED_OBJ_END,
    J65_EXPECTED_ARRAY_END,
    J65_USER_ERROR,             /* must be last.  not generated by parser. */
};

typedef struct {
    uint8_t dummy[512];
} j65_state;

typedef int8_t __fastcall__ (*j65_callback)(j65_state *s, uint8_t event);

void __fastcall__ j65_init(j65_state *s, void *ctx, j65_callback cb, uint8_t max_depth);

int8_t __fastcall__ j65_parse(j65_state *s, const char *buf, size_t len);

const char * __fastcall__ j65_get_string(const j65_state *s);
size_t __fastcall__ j65_get_length(const j65_state *s);

int32_t __fastcall__ j65_get_integer(const j65_state *s);

uint32_t __fastcall__ j65_get_line_offset(const j65_state *s);
uint32_t __fastcall__ j65_get_line_number(const j65_state *s);
uint32_t __fastcall__ j65_get_column_number(const j65_state *s);

uint8_t __fastcall__ j65_get_max_depth(const j65_state *s);
void * __fastcall__ j65_get_context(const j65_state *s);

#endif  /* J65_H */
