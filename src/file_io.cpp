#include "file_io.hpp"

#include "exceptions.hpp"

#include <algorithm>
#include <fstream>
#include <exception>
#include <functional>
#include <unordered_map>

namespace gz {

//
// KEY-VALUE FILE
//
    template<typename Hash, typename Pred>
    void writeKeyValueFile(const std::string& filepath, const std::unordered_map<std::string, std::string, Hash, Pred>& content) {
        std::ofstream file(filepath.c_str());
        if (file.is_open()) {
            file << "# Written by writeKeyValueFile" << std::endl;
            for (std::pair<std::string, std::string> line : content) {
                file << line.first << " = " << line.second << std::endl;
            }
            file.close();
        }
        else {
            throw FileIOError("Could not open file: '" + filepath + "'", "writeKeyValueFile");
        }
    }
    template void writeKeyValueFile<std::hash<std::string>, std::equal_to<std::string>>(const std::string&, const std::unordered_map<std::string, std::string, std::hash<std::string>, std::equal_to<std::string>>&);
    template void writeKeyValueFile<util::string_hash, std::equal_to<>>(const std::string&, const std::unordered_map<std::string, std::string, util::string_hash, std::equal_to<>>&);


    using pairSS = std::pair<std::string, std::string>;
    using umapSS = std::unordered_map<std::string, std::string>;
    using mapSS = std::map<std::string, std::string>;
    using vecSS = std::vector<pairSS>;

    inline void insert(vecSS& t, pairSS&& p) { t.emplace_back(p); }
    inline void insert(umapSS& t, pairSS&& p) { t.emplace(p); }
    inline void insert(mapSS& t, pairSS&& p) { t.emplace(p); }

    template<ReadKeyValueFileImplemented T>
    T readKeyValueFile(const std::string& filepath, bool removeSpaces) {
        T attr;
        std::string line;
        int eqPos;
        std::ifstream file(filepath);
        if (file.is_open()) {
            while (file.good()) {
                getline(file, line);

                // ignore commented lines
                if (line.starts_with('#')) { continue; }

                // if "=" in line: split into key - value pair and store in map
                if (line.find("=") != std::string::npos) {
                    if (removeSpaces) {  // remove all whitespaces
                        line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x) { return std::isspace(x); }), line.end()); 
                    }
                    else {  // remove whitespaces until after equal sign
                        eqPos = line.find("=");
                        line.erase(std::remove_if(line.begin(), line.begin() + eqPos + 2, [](unsigned char x) { return std::isspace(x); }), line.begin() + eqPos + 2);
                    }
                    eqPos = line.find("=");
                    insert(attr, std::pair{ line.substr(0, eqPos), line.substr(eqPos+1, line.length()) });
                }
            }
            file.close();
        }
        else {
            throw FileIOError("Could not open file: '" + filepath + "'", "readKeyValueFile");
        }
        return attr;
    }
    template umapSS readKeyValueFile<umapSS>(const std::string&, bool);
    template mapSS readKeyValueFile<mapSS>(const std::string&, bool);
    template vecSS readKeyValueFile<vecSS>(const std::string&, bool);



//
// BINARY-FILE
//
    std::vector<char> readBinaryFile(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::ate | std::ios::binary);

        std::vector<char> buffer;
        if (file.is_open()) {
             size_t fileSize = file.tellg();
             buffer.resize(fileSize);
             file.seekg(0);
             file.read(buffer.data(), fileSize);

        }
        else {
            throw FileIOError("Could not open file: '" + filepath + "'", "readBinaryFile");
        }
        file.close();

        return buffer;
    }


}
