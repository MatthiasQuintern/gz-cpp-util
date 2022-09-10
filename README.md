# gz-cpp-util
cpp-20 utility library for my projects

## Features
- Extensive logger using variadic templates to log almost anything
- vecX and matMxN vector and matrix classes
- Some containers like a thread safe queue and a ringbuffer
- Regex that works with std::string_view
- Type conversion utility (from string to int/float/uint/bool)


## Installation
### Arch Linux (ABS)
- Download PKGBUILD: `wget https://raw.github.com/MatthiasQuintern/gz-cpp-util/main/PKGBUILD`
- Build and install with the Arch Build System: `makepkg -si`

### Linux
- Make a clone of this repo: `git clone https://github.com/MatthiasQuintern/gz-cpp-util`
- Build and install: `cd src && make && make install`


## Usage
### Library
- Add `-lgzutil` to your linker flags
- Include the wanted header: `#include <gz-util/*dir*/*header.hpp*>`

### Enumeration-to-string script
- The gen_enum_str.py script will be installed to `/usr/bin/gz-enum-str`.
- Run `gz-enum-str -h` to list available options.

### Documentation
The documentation for this library can be generated using **doxygen**. 
Install doxygen and run `make docs`, then open `docs/html/index.html`.


## Changelog
### 2022-09-10
- Added matrices to math lib
- Improved logger
### 2022-09-05
- initial version
