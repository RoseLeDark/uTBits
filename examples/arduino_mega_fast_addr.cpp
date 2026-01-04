#include <Arduino.h>
#include "utfast_addr.h"

#define DDRB  (*(volatile uint8_t *)0x24)
#define PB5 5  // Pin 13 on Arduino Mega

void setup() {
    Serial.begin(9600);

    Serial.println("Setting Arduino Mega Pin 13 as output using fast_addr...");
    // AVR – DDRB
    auto ddrb = utb::create_fast_view<uint8_t>(DDRB);
    ddrb->set(PB5, true); 

    Serial.print("DDRB value: 0b");
    for(int i = 7; i >= 0; i--) {
        Serial.print(ddrb->get(i) ? '1' : '0');
    }   

    Serial.println("Arduino Mega Pin 13 set as output");
}

void loop() {}