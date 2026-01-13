# CHANGELOG.md

## **1.8.5‑beta**

### Added
- add the `history` (uthistory.h): class a fixed‑size sliding buffer with min/max/avg and direct indexing
- add `range` (utrange.h): Basic range template class for generating compile-time sequences 
- add `step` (utstep.h) : A class that iterates through a range with a fixed step size.
- add `xstep` (utstep.h): An extended step iterator that allows dynamic modification of the step size.
- add comments for doxygen, start with
### Changed
- Classified `float` correctly as `is_rational`

### Fixed
- Removed duplicate semicolons

---

## **1.8.3 – 2026‑01‑06**

### Added
- `buffer` (global buffer view) and `buffer_iterator`
- `endian` helper
- Atomic support including `atomic_bool`, `atomic_char`, and atomic variants for all fundamental types  
  *(currently GCC‑only compatible)*
- `UTB_CONFIG_ENABLE_ATOMIC` added to `utconfig.h` and set to `UTB_YES` by default  
  *(atomic support disabled when set to `UTB_NO`)*
- Murmur3 hash implementation in `uthash`
- `utlimits.h`
- `shared_ptr` and `weak_ptr`  
  *(uses atomics only when `UTB_CONFIG_ENABLE_ATOMIC == UTB_YES`)*
- `utacounter.h` — atomic counter (enabled only when atomics are active)

### Changed
- `utarray`: `difference_type = utb::ptrdiff_t` replaced with plain `ptrdiff_t`
- Fixed issues in `utiterator.h`

---

## **1.8.2**

### Added
- utb::size_t — platform‑dependent size type based on CPU pointer width
- `utb::optional`
- Added `UTB_SIZE_TYPE` to `utconfig` and set default to `UTB_SIZE_TYPE_AUTO`  
  *(auto‑detects utb::size_t based on pointer width: 16/32/64 bit)*  
  Available options:  
  - `UTB_SIZE_TYPE_16` → `unsigned short`  
  - `UTB_SIZE_TYPE_32` → `unsigned int`  
  - `UTB_SIZE_TYPE_64` → `unsigned long long`
- Added `UTB_CONFIG_DEFAULT_STACK_SIZE` with automatic platform‑dependent selection  
  *(auto‑detects default stack size only when explicitly set to AUTO, independent of UTB_SIZE_TYPE)*
        - 16: UTB_CONFIG_DEFAULT_STACK_SIZE 16 for utstack max entrys
        - 32: UTB_CONFIG_DEFAULT_STACK_SIZE 32 for utstack max entrys
        - 64: UTB_CONFIG_DEFAULT_STACK_SIZE 64 for utstack max entrys
        - UTB_SIZE_TYPE_AUTO → selects 16/32/64 based on pointer width
### Changed
- Moved colors to `utb::grafic::color`
- Namespace corrections
- `base_fastbit(unsigned char b)` is no longer explicit; `base_fastbit(bool b)` remains explicit
- Replaced all `size_t` with `utb::size_t` in:  
  `utalgorithm`, `utalignment`, `utfast_addr`, `utfunction`, `utfunctionals`,  
  `utmap`, `utstack`, `utquaternion`

---

## **0.6.2 – 1.1.0**

### Added
- Math system: Introduced a foundational math module providing essential vector and geometry types for 2D and 3D operations:
        - `vector2`: 2D vector type
        - `vector3`: 3D vector type
        - `vector4`: 4D vector type
        - `ray`: ray representation for geometric calculations
        - `rectangle`: axis‑aligned rectangle type
        - `quaternion`: Quaternion class for 3D rotations and orientations
- Added float‑based RGBA color class
- Added a curated set of 140 predefined colors for consistent rendering and UI usage
### Documentation
- Added initial  with project overview and usage information
### 	PlatformIO integration
- Added PlatformIO library metadata
- Updated naming and structure to comply with PlatformIO registry requirements
- Published the library under version 1.1.0

---

## **0.5.11**

### Added
- `utalgorithms`: The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating) that operate on ranges of elements.
- `utalignment`: utils is_aligned, alignment_for, type_with_alignment - helper tools vor alignment
- `utarray`: a fixed size array
- `utconfig`: the config file
- `utebo`: Empty base optimization pair
- `utfast_addr`: View für ein Register oder einen Wert als Ganzes und als Bit-Feld.  Erzeugt eine View auf eine gegebene Speicheradresse.
- `utfunctional`: Lightweight, non-allocating function wrapper.
- `utstack`: A simple template for a Stack
- `utvector`:  Fixed-size vector container with in-place storage.
- `uttypetraits`: Type traits for extracting type information
- `utvoid`:  A dummy class with value-type semantics, mostly useful as a template argument.
- Initial public release
