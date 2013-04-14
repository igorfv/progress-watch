#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

void itoa1(int num, char* buffer) {
    const char digits[10] = "0123456789";
    buffer[0] = digits[num % 10];
}

void itoa2(int num, char* buffer) {
    const char digits[10] = "0123456789";
    if(num > 99) {
        buffer[0] = '9';
        buffer[1] = '9';
        return;
    } else if(num > 9) {
        buffer[0] = digits[num / 10];
    } else {
        buffer[0] = '0';
    }
    buffer[1] = digits[num % 10];
}