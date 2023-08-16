
#include "comm_module.h"
#include "config.h"
#include <HardwareSerial.h>


HardwareSerial serial(1);


void commInit() {
    serial = HardwareSerial(1);
    serial.begin(AS69_BAUDRATE, SERIAL_8N1, AS69_TX_PIN, AS69_RX_PIN);

    pinMode(AS69_MD0_PIN, OUTPUT);
    pinMode(AS69_MD1_PIN, OUTPUT);
    pinMode(AS69_AUX_PIN, INPUT);

    // Wait for comm module initialization
    if (digitalRead(AS69_AUX_PIN) == LOW) {
        Serial.println("Radio initiating");
        while(digitalRead(AS69_AUX_PIN) == LOW);
        Serial.println("Radio initialized");
    }

    // Set module to normal mode
    digitalWrite(AS69_MD0_PIN, HIGH);
    digitalWrite(AS69_MD1_PIN, LOW);
    Serial.println("Radio initialized");
}




void listener(void* param) {
    uint8_t current_byte;
    Serial.println("Listener started");

    while (true) {
        while (serial.available() == 0);
        current_byte = serial.read();
        switch (current_byte) {
            case 0x01:
                digitalWrite(LED_PIN, HIGH); break;
            case 0x02:
                digitalWrite(LED_PIN, LOW); break;
            default:
                break;
        }
    }
}