
#include <Arduino.h>
#include "comm_module.h"
#include "global_declarations.h"
#include "interrupt_callbacks.h"
#include "config.h"

bool button_state = false;

void setup() {
    Serial.begin(9600);
    commInit();

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    xTaskCreatePinnedToCore(listener, "Listener", 10000, nullptr, 1, nullptr, 1);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == HIGH && !button_state) {
        button_close();
    }
    else if (digitalRead(BUTTON_PIN) == LOW && button_state) {
        button_open();
    }
}