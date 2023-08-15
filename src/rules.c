#include "rules.h"

/* ================================================================ */

void rule_0(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    for (; i < size; i++) {

        current[i] = 0;
    }

    return ;
}

/* ================================ */

void rule_1(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && !middle && !right;
    }

    return ;
}

/* ================================ */

void rule_2(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && !middle && right;
    }

    return ;
}

/* ================================ */

void rule_3(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && !middle;
    }

    return ;
}

/* ================================ */

void rule_4(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && middle && !right;
    }

    return ;
}

/* ================================ */

void rule_5(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;


    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && !right; 
    }

    return ;
}

/* ================================ */

void rule_6(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && middle && !right) || (!left && !middle && right);
    }

    return ;
}

/* ================================ */

void rule_7(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && !right) || (!left && !middle);
    }

    return ;
}

/* ================================ */

void rule_8(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && middle && right;
    }

    return ;
}

/* ================================ */

void rule_9(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && !middle && !right) || (!left && middle && right);
    }

    return ;
}

/* ================================ */

void rule_10(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && !right;
    }

    return ;
}

/* ================================ */

void rule_11(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && !middle) || (!left && right);
    }

    return ;
}

/* ================================ */

void rule_12(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left && middle;
    }

    return ;
}

/* ================================ */

void rule_13(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && !right) || (!left && middle);
    }

    return ;
}

/* ================================ */

void rule_14(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && middle) || (!left && right);
    }

    return ;
}

/* ================================ */

void rule_15(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !left;
    }

    return ;
}

/* ================================ */

void rule_16(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = left && !middle && !right;
    }

    return ;
}

/* ================================ */

void rule_17(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = !middle && !right;
    }

    return ;
}

/* ================================ */

void rule_18(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && !middle && right);
    }

    return ;
}

/* ================================ */

void rule_19(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!middle && !right) || (!left && !middle);
    }

    return ;
}

/* ================================ */

void rule_20(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && middle && !right);
    }

    return ;
}

/* ================================ */

void rule_21(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!middle && !right) || (!left && !right);
    }

    return ;
}

/* ================================ */

void rule_22(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && middle && !right) || (!left && !middle && right);
    }

    return ;
}

/* ================================ */

void rule_23(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!middle && !right) &&  (!left && !right) && (!left && !middle);
    }

    return ;
}

/* ================================ */

void rule_24(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && middle && right);
    }

    return ;
}

/* ================================ */

void rule_25(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!left && middle && right) || (!middle && !right);
    }

    return ;
}

/* ================================ */

void rule_26(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && right);
    }

    return ;
}

/* ================================ */

void rule_27(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!middle && !right) || (!left && right);
    }

    return ;
}

/* ================================ */

void rule_28(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (left && !middle && !right) || (!left && middle);
    }

    return ;
}

/* ================================ */

void rule_29(unsigned char* current, unsigned char* previous, size_t size) {
    ssize_t i = 0;

    char left;
    char middle;
    char right;

    for (; i < size; i++) {

        left = ((i - 1) < 0) ? previous[size - 1] : previous[i - 1];
        middle = previous[i];
        right = ((i + 1) >= size) ? previous[0] : previous[i + 1];

        current[i] = (!middle && !right) || (!left && middle);
    }

    return ;
}