# µTBits

 [![License](https://img.shields.io/badge/license-EUPL--1.2-blue?style=flat-square)](https://github.com/RoseLeDark/uTBits/blob/main/LICENCE.md) [![PlatformIO](https://img.shields.io/badge/PlatformIO-compatible-green?style=flat-square)](https://platformio.org/lib) [![Stars](https://img.shields.io/github/stars/RoseLeDark/uTBits?style=flat-square)](https://github.com/RoseLeDark/uTBits/stargazers)

### Overview

**µTBits** is a header‑only C++ utility library focused on embedded and systems programming. It provides lightweight, typed memory/register views, simple color and math helpers, and compact PlatformIO examples. The library aims for **maximum portability**, **minimal dependencies**, and **direct, safe control of hardware registers**.

---

### Key Features

- **Header-only**: drop-in headers, no build dependencies.  
- **`fast_addr_t` / `fast_register_view`**: typed, safe bit views for memory and peripheral registers.  
- **Color utilities**: `utb::grafic::color` for float-based color handling and conversions.  
- **Low-level examples**: native, AVR (Arduino Mega), ESP32, and WS2812 low-level drivers that use only uTBits APIs.  
- **License**: EUPL‑1.2.

---

### Quick Install (PlatformIO)

Add the library from the PlatformIO registry or clone the repository and include the `include/` directory in your project. The library is framework- and platform-agnostic.

**Minimal `platformio.ini` for native tests**

```ini
[env:native]
platform = native
lib_deps = 
  https://github.com/RoseLeDark/uTBits.git

[env:mega]
platform = atmelavr
board = megaatmega2560
framework = arduino
lib_deps = 
  https://github.com/RoseLeDark/uTBits.git
```

**Include in code**

```cpp
#include <utfast_addr.h>
#include <utcolor.h>
```

---

### Example: WS2812 (low-level, API-first)

This example demonstrates a WS2812 driver that uses only uTBits APIs: `create_fast_view<T>(address)`, `set(pos, bool)`, `flip(pos)`, and `utb::math::color`. It uses timer polling for deterministic timing and avoids `digitalWrite()` or direct register macros.

**Snippet**

```cpp
// create fast views for DDR and PORT
ddrd  = utb::create_fast_view<uint8_t>(0x2A);
portd = utb::create_fast_view<uint8_t>(0x2B);

// set pin as output via DDR
ddrd->set(LED_BIT, true);

// send a color (utb::math::color uses floats 0.0..1.0)
utb::math::color c(1.0f, 0.0f, 0.0f);
sendColor(c);
```

Full examples are available in the `examples/` files: `arduino_mega_fast_addr.cpp`, `esp32_fast_addr.cpp`, `arduino_mega_WS2812.cpp`, and `native_fast_addr.cpp`.

---

### API Summary

- **`fast_addr_t<T>` / `fast_register_view<T, Bits>`**  
  - `create_fast_view<T>(address)` — create a typed view to a memory/register address.  
  - `set(pos, bool)` — set a single bit (bounds-checked).  
  - `flip()` / `flip(pos)` — toggle all bits or a single bit.  
  - `num_ones()` / `num_zeros()` — bit statistics.  
  - `value` union member exposes the underlying numeric value when needed.

- **Color utilities**  
  - `utb::math::color` — float-based color types (0.0f..1.0f).  
  - `from_name<T>(color_name)` — construct a color from predefined names.

---

### Examples & Tests

- **Examples**: `examples/` contains ready-to-run PlatformIO examples for native, AVR, and ESP32.  
- **Tests**: `test/` contains Unity-based native tests for core functionality.

---

### Contribution

Contributions are welcome. Please open issues for bugs or feature requests. Pull requests should:

- Keep the library header-only and portable.  
- Include small, focused changes with tests or example updates when applicable.  
- Document API changes in the README or add example snippets.

---

### License

This project is licensed under **EUPL‑1.2**. See `LICENCE.md` for details.
