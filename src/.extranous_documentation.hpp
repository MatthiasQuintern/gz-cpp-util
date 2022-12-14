namespace gz {
    /**
     * @mainpage
     * @section main_about About
     *  This c++20 library contains multiple useful functions, most of them are focused on working with strings.
     *
     *  Please report bugs on the <a href="https://github.com/MatthiasQuintern/gz-cpp-util">github page</a>!
     *
     *  For the changelog, have a look at the @ref README.md "readme".
     *
     * @section main_features Features
     *  -# @ref Log "extensive and extendable logger" using variadic templates to log @ref sc_toStringImplemented "almost anything"
     *  -# containers like a thread safe @ref Queue "queue" and a @ref RingBuffer "ringbuffer"
     *  -# @ref regex.hpp "regex that works with std::string_view"
     *  -# @subpage string_conversion "string <-> type conversion"
     *   - @ref sc_toString "converting types to string" (including numbers, vectors, ranges, maps...)
     *   - @ref sc_fromString "constructing types from string"
     *   - @ref getIntOr "constructing types from string" or return fallback
     *  -# @ref SettingsManager "Settings Manager" which can store settings of different types and load/save them from/to a file
     *  -# @subpage gen-enum-str "a script that generates an array of strings for your enumerations", so that you can get the name of an enum value
     *
     * @section main_installation Installation
     *  @subsection main_i_linux Linux
     *   - Make a clone of this repo: `git clone https://github.com/MatthiasQuintern/gz-cpp-util`
     *   - Build and install: `cd src && make && make DESTDIR=/usr/local install`
     *  @subsection main_i_arch Arch Linux (ABS)
     *   - Download PKGBUILD: `wget https://raw.github.com/MatthiasQuintern/gz-cpp-util/main/PKGBUILD`
     *   - Build and install with the Arch Build System: `makepkg -si`
     *  @subsection main_i_windows Windows
     *   I do not delevop on windows, but you'll figure it out. 
     *   The only platform specific code is the color support of the logger, which wont work properly on windows (I will address that in the future).
     *   It should compile with mvsc.
     *
     *  @subsection main_i_usage Usage
     *   - Add `-lgzutil` to your linker flags
     *   - Include the wanted header: `#include <gz-util/dir/header.hpp>`
     *  
     */


    /**
     * @page gen-enum-str Enumeration - String Conversion Script
     * @section ges_about About
     *  gen_enum_str is a python script included in the github repository of this library.
     *  It generates toString and fromString functions for all enumerations.
     * @section ges_how How it works
     *  The script first searches all enumerations in .hpp files with some regex.
     *  It only detects them when using this syntax:
     *  @code
     *   namespace x::y {
     *       enum NAME {
     *           ENUM1, ENUM2=4, ENUM3 = 5, ENUM4,
     *       };
     *   }
     *  @endcode
     *  The amount of tabs and spaces are irreleveant, but the { brackets must be on the same line as the declaration.
     *  Nested namespaces are not supported, you will have to manully edit the generated code if you use them.
     *
     *  After all enumerations were found, it generates toString and fromString declarations in the .hpp file,
     *  and the declarations in the according .cpp file. It uses two maps type2name and name2type for the conversion.
     *  The maps are contained in structs, which are declared and defined in the source file.
     *
     * @section ges_usage Usage
     *  The script was written for python 3(.10), so you will need to have that installed.
     *
     *  @subsection ges_usage_installed With script installed
     *   Depending on the installation method, it should either be in `/usr/bin` or `/usr/local/bin` which should both be in your `$PATH`.
     *   Note that it will not have the `.py` ending!
     *
     *   If you do want to run the script on `~/c++/src/myheader.hpp`, you can simply do:
     *   @code shell
     *    gen-enum-str ~/c++/src/myheader.hpp
     *   @endcode
     *
     *  @subsection ges_usage_not_installed With script not installed
     *   If you do want to run the script on `~/c++/src/myheader.hpp`, with the script itself being located at `~/scripts/gen_enum_str.py`, run:
     *   @code shell
     *    python3 ~/scripts/gen_enum_str.py ~/c++/src/myheader.hpp
     *   @endcode
     *
     *  @warning 
     *   This script was tested and should not mess anything up, HOWEVER: 
     *   Do not just run random scripts off the internet on your precious source code without skimming through them first!
     *   It is also advisable to have up-to-date backups!
     *
     *  To get help, use:
     *  @code
     *   gen-enum-str --help
     *  @endcode
     *  @code output 
     *   Synposis:           get_enum_str.py <Options>... <file>...
     *                       get_enum_str.py <Options>... -r <path>...
     *   -h --help           help
     *   -r                  recurse: Recurse through given paths process all files.
     *   -i                  interactive: prompt for every enumeration
     *   --no-docs           turn off docstring generation
     *   --docs-no-names     do not list names of enumeration values in docstring
     *   --docs-no-gen       do not put "generated by gen_enum_str" in docstring
     *   --no-throw          return empty string/last enum value if the argument for to/fromString is invalid.
     *                       This would normaly throw gz::InvalidArgument
     *                       This option does not make the functions noexcept!
     *   If the generated code produces errors:
     *   - check that necessary headers are included in the source file:
     *     - gz-util/string.hpp
     *     - gz-util/exceptions.hpp (unless you use --no-throw)
     *   - check the namespaces of the enumerations, the generated code should be in global namespace
     *     nested namespace are not supported, you will have to correct that if you use them
     *  @endcode
     */
}
