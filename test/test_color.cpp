#include <unity.h>
#include "utcolor.h"

void test_color_rgba32() {
    utb::color c(0xFF00FFFF); // RRGGBBAA

    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0f, c.r);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0f, c.g);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0f, c.b);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1.0f, c.a);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_color_rgba32);
    return UNITY_END();
}

