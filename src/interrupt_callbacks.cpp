
#include "interrupt_callbacks.h"
#include "global_declarations.h"

void button_close() {
    button_state = !button_state;
    Serial.println("close");
    serial.write(0x01);
}

void button_open() {
    button_state = !button_state;
    Serial.println("open");
    serial.write(0x02);
}