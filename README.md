# gz-cpp-util

## Features
- Extensive logger using variadic templates to log almost anything
- VecX classes
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
- Add `-lgzutil` to your linker flags
- Include the wanted header: `#include <gz-util/*dir*/*header.hpp*>`
### Documentation
The documentation for this library can be generated using **doxygen**. 
Install doxygen and run `make docs`.


## Changelog
### 2022-09-05
- initial version
