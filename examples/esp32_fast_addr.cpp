#include <Arduino.h>
#include "utfast_addr.h"

#define GPIO_OUT_REG 0x3FF44004  // Adresse des GPIO-Ausgangsregisters auf dem ESP32
#define GPIO2_BIT    2           // Bit-Position für GPIO2

void setup() {
    Serial.begin(115200);

    Serial.println("Setting ESP32 GPIO2 HIGH as output using fast_addr...");
    // GPIO_OUT_REG = 0x3FF44004
    auto gpio_out = utb::create_fast_view<uint32_t>(GPIO_OUT_REG);

    // GPIO2 HIGH setzen
    gpio_out->set(GPIO2_BIT, true);

    Serial.print("gpio_out value: 0b");
    for(int i = 7; i >= 0; i--) {
        Serial.print(gpio_out->get(i) ? '1' : '0');
    }   

    Serial.println("GPIO2 set HIGH");
}

void loop() {}
