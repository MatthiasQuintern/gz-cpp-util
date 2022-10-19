# gz-util - About
This c++20 library contains multiple useful functions, most of them are focused on working with strings.
Documentation is [available here](https://docs.quintern.xyz/gz-cpp-util/index.html).

Please report bugs on the [github page](https://github.com/MatthiasQuintern/gz-cpp-util)!



## Features
- Extensive logger using variadic templates to log almost anything
- Some containers like a thread safe queue and a ringbuffer
- Regex that works with std::string_view
- Type conversion utility (from string to int/float/uint/bool)
- Settings manager which can store settings of different types and load/save them from/to a file
- Python script that generates an array of strings for your enumerations, so that you can get the name of an enum value


## Installation
### Arch Linux (ABS)
- Download PKGBUILD: `wget https://raw.github.com/MatthiasQuintern/gz-cpp-util/main/PKGBUILD`
- Build and install with the Arch Build System: `makepkg -si`

### Linux
- Make a clone of this repo: `git clone https://github.com/MatthiasQuintern/gz-cpp-util`
- Build and install: `cd src && make && make DESTDIR=/usr/local install`

### Windows
I do not delevop on windows, but you'll figure it out. 
The library does not contain platform specific code and should compile with mvsc.

### Documentation
The documentation is for this library is [available here](https://docs.quintern.xyz/), but it can also be generated using **doxygen**. 
   cd gz-cpp-util/src
   make docs
   firefox ../docs/html/index.html
Replace `firefox` with your web browser


## Usage
### Library
- Add `-lgzutil` to your linker flags
- Include the wanted header: `#include <gz-util/*dir*/*header.hpp*>`
- The name of the library is `gz-util` and not `gz-cpp-util` like the git repo!

### Enumeration-to-string script
- The gen_enum_str.py script will be installed to `/usr/(local)/bin/gz-enum-str`.
- Run `gz-enum-str -h` to list available options.


## Changelog
### 2022-10-19 [1.3.1] [1.3.2]
- Changes to logger (log.hpp):
   - Added create info struct constructor
   - Timestamp can be disabled
   - Added different log levels that can be turned off/on at compile time
### 2022-09-26 [1.3]
- Added SettingsManager
- Renamed getXXX to getXXXOr
- Added more type conversion utility
    - from_string<T>()
    - to_string()
- Logger now uses to_string
- Restructured files
- Added more documentation
### 2022-09-17 [1.2]
- Moved math part to its own repository/library [here](https://github.com/MatthiasQuintern/gzm)
### 2022-09-10 [1.1]
- Added matrices to math lib
- Improved logger
### 2022-09-05 [1.0]
- initial version
