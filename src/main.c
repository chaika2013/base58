#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "base58.h"

static char out[1024];
static size_t out_len;

void test_base58_encode_function_exists(void) {
    out_len = sizeof(out);
    base58_encode("some text", 9, out, &out_len);
}

void test_base58_encode_empty_string(void) {
    out_len = 1;
    base58_encode("", 0, out, &out_len);
    assert(out_len == 0);
}

void test_base58_encode_simple_bytes(void) {
    out_len = sizeof(out);
    base58_encode("\x01", 1, out, &out_len);
    assert(memcmp(out, "2", 1) == 0);
    assert(out_len == 1);
}

void test_base58_encode_simple_bytes2(void) {
    out_len = sizeof(out);
    base58_encode("\x02", 1, out, &out_len);
    assert(memcmp(out, "3", 1) == 0);
    assert(out_len == 1);
}

void test_base58_encode_simple_bytes3(void) {
    out_len = sizeof(out);
    base58_encode("\x39", 1, out, &out_len);
    assert(memcmp(out, "z", 1) == 0);
    assert(out_len == 1);
}

void test_base58_encode_simple_bytes4(void) {
    out_len = sizeof(out);
    base58_encode("\x3A", 1, out, &out_len);
    assert(memcmp(out, "21", 2) == 0);
    assert(out_len == 2);
}

void test_base58_encode_simple_bytes5(void) {
    out_len = sizeof(out);
    base58_encode("\xFF", 1, out, &out_len);
    assert(memcmp(out, "5Q", 2) == 0);
    assert(out_len == 2);
}

void test_base58_encode_double_bytes(void) {
    out_len = sizeof(out);
    base58_encode("\x01\x01", 2, out, &out_len);
    assert(memcmp(out, "5S", 2) == 0);
    assert(out_len == 2);
}

void test_base58_encode_multiple_bytes(void) {
    out_len = sizeof(out);
    base58_encode("\x19\x28\x3A\xFF\x0D", 5, out, &out_len);
    assert(memcmp(out, "3qcw5BS", 7) == 0);
    assert(out_len == 7);
}

void test_base58_encode_multiple_bytes_with_zeroes_at_start(void) {
    out_len = sizeof(out);
    base58_encode("\x00\x00\x19\x28\x3A\xFF\x0D", 7, out, &out_len);
    assert(memcmp(out, "113qcw5BS", 9) == 0);
    assert(out_len == 9);
}

void test_base58_encode_multiple_bytes_with_zeroes_at_end(void) {
    out_len = sizeof(out);
    base58_encode("\x19\x28\x3A\xFF\x0D\x00", 6, out, &out_len);
    assert(memcmp(out, "DXbbfT3M", 8) == 0);
    assert(out_len == 8);
}

void test_base58_encode_multiple_bytes_with_zeroes_at_end2(void) {
    out_len = sizeof(out);
    base58_encode("\x19\x28\x3A\xFF\x0D\x00\x00", 7, out, &out_len);
    assert(memcmp(out, "xJ3hzhwMH", 9) == 0);
    assert(out_len == 9);
}

void test_base58_encode_multiple_bytes_with_only_zeroes(void) {
    out_len = sizeof(out);
    base58_encode("\x00\x00\x00", 3, out, &out_len);
    assert(memcmp(out, "111", 3) == 0);
    assert(out_len == 3);
}

void test_base58_encode_some_text(void) {
    out_len = sizeof(out);
    base58_encode("sometext", 8, out, &out_len);
    assert(memcmp(out, "LJsGR4F7kFD", 11) == 0);
    assert(out_len == 11);
}

void test_base58_decode_function_exists(void) {
    out_len = sizeof(out);
    base58_decode("LJsGR4F7kFD", 11, out, &out_len);
}

void test_base58_decode_empty_string(void) {
    out_len = 1;
    base58_decode("", 0, out, &out_len);
    assert(out_len == 0);
}

void test_base58_decode_simple_data(void) {
    out_len = sizeof(out);
    base58_decode("2", 1, out, &out_len);
    assert(memcmp(out, "\x01", 1) == 0);
    assert(out_len == 1);
}

void test_base58_decode_simple_data2(void) {
    out_len = sizeof(out);
    base58_decode("3", 1, out, &out_len);
    assert(memcmp(out, "\x02", 1) == 0);
    assert(out_len == 1);
}

void test_base58_decode_simple_data3(void) {
    out_len = sizeof(out);
    base58_decode("21", 2, out, &out_len);
    assert(memcmp(out, "\x3A", 1) == 0);
    assert(out_len == 1);
}

void test_base58_decode_multiple_bytes_data(void) {
    out_len = sizeof(out);
    base58_decode("3qcw5BS", 7, out, &out_len);
    assert(memcmp(out, "\x19\x28\x3A\xFF\x0D", 5) == 0);
    assert(out_len == 5);
}

void test_base58_decode_multiple_bytes_data_with_leading_ones(void) {
    out_len = sizeof(out);
    base58_decode("1113qcw5BS", 10, out, &out_len);
    assert(memcmp(out, "\x00\x00\x00\x19\x28\x3A\xFF\x0D", 8) == 0);
    assert(out_len == 8);
}

void test_base58_decode_multiple_bytes_data_with_only_ones(void) {
    out_len = sizeof(out);
    base58_decode("111111", 6, out, &out_len);
    assert(memcmp(out, "\x00\x00\x00\x00\x00\x00", 6) == 0);
    assert(out_len == 6);
}

void test_base58_decode_multiple_bytes_data_to_sometext(void) {
    out_len = sizeof(out);
    base58_decode("LJsGR4F7kFD", 11, out, &out_len);
    assert(memcmp(out, "sometext", 8) == 0);
    assert(out_len == 8);
}

void test_base58_encode_overflow_to_empty_string(void) {
    out[0] = 0;
    out_len = 0;
    assert(base58_encode("some text", 9, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[0] == 0);
}

void test_base58_encode_non_overflow_empty_to_empty_string(void) {
    out[0] = 0;
    out_len = 0;
    assert(base58_encode("", 0, out, &out_len) == 0);
    assert(out_len == 0);
    assert(out[0] == 0);
}

void test_base58_encode_overflow_when_got_leading_zeroes(void) {
    out[2] = 0;
    out_len = 2;
    assert(base58_encode("\x00\x00\x00", 3, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[2] == 0);
}

void test_base58_encode_overflow_when_got_leading_zeroes_and_data_after(void) {
    out[7] = 0;
    out_len = 7;
    assert(base58_encode("\x00\x00\x19\x28\x3A\xFF\x0D", 7, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[7] == 0);
}

void test_base58_decode_overflow_to_empty_string(void) {
    out[0] = 0;
    out_len = 0;
    assert(base58_decode("LJsGR4F7kFD", 11, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[0] == 0);
}

void test_base58_decode_overflow_to_nonempty_string(void) {
    out[7] = 0;
    out_len = 7;
    assert(base58_decode("LJsGR4F7kFD", 11, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[7] == 0);
}

void test_base58_decode_overflow_to_nonempty_string_with_leading_ones(void) {
    out[2] = 0;
    out_len = 2;
    assert(base58_decode("1113qcw5BS", 10, out, &out_len) == -1);
    assert(out_len == 0);
    assert(out[2] == 0);
}

void test_base58_decode_bad_input(void) {
    out_len = sizeof(out);
    assert(base58_decode("0000", 10, out, &out_len) == -1);
    assert(out_len == 0);
}

int main(int argc, char *argv[]) {
    /* encoding tests */
    test_base58_encode_function_exists();
    test_base58_encode_empty_string();
    test_base58_encode_simple_bytes();
    test_base58_encode_simple_bytes2();
    test_base58_encode_simple_bytes3();
    test_base58_encode_simple_bytes4();
    test_base58_encode_simple_bytes5();
    test_base58_encode_double_bytes();
    test_base58_encode_multiple_bytes();
    test_base58_encode_multiple_bytes_with_zeroes_at_start();
    test_base58_encode_multiple_bytes_with_zeroes_at_end();
    test_base58_encode_multiple_bytes_with_zeroes_at_end2();
    test_base58_encode_multiple_bytes_with_only_zeroes();
    test_base58_encode_some_text();

    /* decoding tests */
    test_base58_decode_function_exists();
    test_base58_decode_empty_string();
    test_base58_decode_simple_data();
    test_base58_decode_simple_data2();
    test_base58_decode_simple_data3();
    test_base58_decode_multiple_bytes_data();
    test_base58_decode_multiple_bytes_data_with_leading_ones();
    test_base58_decode_multiple_bytes_data_with_only_ones();
    test_base58_decode_multiple_bytes_data_to_sometext();

    /* encoding overflow tests */
    test_base58_encode_overflow_to_empty_string();
    test_base58_encode_non_overflow_empty_to_empty_string();
    test_base58_encode_overflow_when_got_leading_zeroes();
    test_base58_encode_overflow_when_got_leading_zeroes_and_data_after();

    /* decoding overflow and bad input tests */
    test_base58_decode_overflow_to_empty_string();
    test_base58_decode_overflow_to_nonempty_string();
    test_base58_decode_overflow_to_nonempty_string_with_leading_ones();
    test_base58_decode_bad_input();
    return 0;
}
