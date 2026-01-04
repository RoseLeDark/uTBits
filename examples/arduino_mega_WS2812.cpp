#include <Arduino.h>
#include <utfast_addr.h>
#include <utcolor.h>
#include <utcolors.h>

// AVR Register-Adressen
#define DDRD_ADDR  0x2A
#define PORTD_ADDR 0x2B
#define LED_BIT    6   // PD6



// Fast-Views auf die Register
static utb::fast_addr_t<uint8_t>* ddrd  = nullptr;
static utb::fast_addr_t<uint8_t>* portd = nullptr;



// Timer-basierte Wartefunktion
static inline void waitTicks(uint16_t ticks) {
    uint16_t start = TCNT1;
    while ((uint16_t)(TCNT1 - start) < ticks) {
        // busy wait
    }
}

static inline void sendBit(bool bit) {
    if (bit) {
        // ---- Bit 1 ----
        portd->set(LED_BIT, true);   // HIGH
        waitTicks(11);               // ~700 ns
        portd->set(LED_BIT, false);  // LOW
        waitTicks(9);                // ~600 ns
    } else {
        // ---- Bit 0 ----
        portd->set(LED_BIT, true);   // HIGH
        waitTicks(5);                // ~350 ns
        portd->set(LED_BIT, false);  // LOW
        waitTicks(14);               // ~900 ns
    }
}

static inline void sendByte(uint8_t b) {
    for (uint8_t i = 0; i < 8; i++) {
        sendBit(b & 0x80);
        b <<= 1;
    }
}

static inline void sendColor(const utb::math::color& c) {
    // WS2812 = GRB
    sendByte((uint8_t)(c.g * 255));
    sendByte((uint8_t)(c.r * 255));
    sendByte((uint8_t)(c.b * 255));
}

void setup() {
    // Fast-Views erzeugen
    ddrd  = utb::create_fast_view<uint8_t>(DDRD_ADDR);
    portd = utb::create_fast_view<uint8_t>(PORTD_ADDR);

    // Pin als Output setzen
    ddrd->set(LED_BIT, true);

    // Timer1: no prescaler → 16 MHz
    TCCR1A = 0;
    TCCR1B = (1 << CS10);

    utb::math::color red = utb::from_name<utb::math::color>(utb::color_name::Red);

    sendColor(red);
    delayMicroseconds(60);
}

void loop() {
    static float t = 0.0f;

    // t läuft langsam durch den Farbkreis
    t += 0.02f;
    if (t > 1.0f)
        t -= 1.0f;

    // Regenbogen über drei Sinusphasen
    float r = fabsf(sinf(6.28318f * t + 0.0f));     // 0°
    float g = fabsf(sinf(6.28318f * t + 2.094f));   // +120°
    float b = fabsf(sinf(6.28318f * t + 4.188f));   // +240°

    utb::math::color c(r, g, b);

    sendColor(c);

    // WS2812 Reset-Latch
    delayMicroseconds(60);
}
