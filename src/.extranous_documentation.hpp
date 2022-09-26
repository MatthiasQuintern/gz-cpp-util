namespace gz {
    // deactivated to use readme as mainpage
    /*
     * @mainpage
     * @section main_about About
     *  This c++20 library contains multiple useful functions, most of them are focused on working with strings.
     *
     *  Please report bugs on the <a href="https://github.com/MatthiasQuintern/gz-cpp-util">github page</a>!
     *
     * @section main_features Features
     *  @subsubsection main_f1 1. Logger
     *   an @ref Log "extensive and extendable logger" using variadic templates to log almost anything
     *  @subsubsection main_f2 2. Container
     *   containers like a thread safe @ref Queue "queue" and a @ref RingBuffer "ringbuffer"
     *  @subsubsection main_f3 3. Regex
     *   regex that works with std::string_view
     *  @subsubsection main_f4 4. String type conversion
     *   - @ref sc_to_string "converting types to string" (including numbers, vectors, ranges, maps...)
     *   - @ref sc_from_string "constructing types from string"
     *   - @ref getIntOr "constructing types from string" or return fallback
     *  @subsubsection main_f5 5. Settings Manager
     *   a @ref SettingsManager "settings manager" which can store settings of different types and load/save them from/to a file
     *  @subsubsection main_f6 6. Enum-String generation script (python)
     *   a script that generates an array of strings for your enumerations, so that you can get the name of an enum value
     *
     * @section main_installation Installation
     *  @subsection main_i_linux Linux
     *   - Make a clone of this repo: `git clone --recursive https://github.com/MatthiasQuintern/gz-cpp-util`
     *   - Build and install: `cd src && make && make install`
     *  @subsection main_i_arch Arch Linux (ABS)
     *   - Download PKGBUILD: `wget https://raw.github.com/MatthiasQuintern/gz-cpp-util/main/PKGBUILD`
     *   - Build and install with the Arch Build System: `makepkg -si`
     *  @subsection main_i_docs Documentation
     *   The documentation for this library can be generated using **doxygen**. 
     *   @code
     *    cd gz-cpp-util/src
     *    make docs
     *    firefox ../docs/html/index.html
     *   @endcode
     *   Replace `firefox` with your web browser.
     *
     * @section main_usage Usage
     *  @subsection main_usage_lib Library
     *   - Add `-lgzutil` to your linker flags
     *   - Include the wanted header: `#include <gz-util/dir/header.hpp>`
     *  
     *  @subsection main_usage_p Enumeration-to-string script
     *   - The gen_enum_str.py script will be installed to `/usr/bin/gz-enum-str`.
     *   - Run `gz-enum-str -h` to list available options.
     *
     *  
     */
}
