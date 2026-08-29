#pragma once

// Reading a file with <fstream> from inside a module implementation unit that
// imports enough other modules makes MSVC lose the definition of
// std::basic_istream<char>::sentry, so tellg/read fail to instantiate:
//
//   istream(698): error C2079: '_Ok' uses undefined class
//                 'std::basic_istream<char,std::char_traits<char>>::sentry'
//
// The identical code compiles in dat_loader.cppm, which imports far less, and
// removing any one import from dat.cpp is enough to make it go away - it is the
// size of the merged import set that tips it over, not any single module.
// Putting the body in a header does not help either, since it is still
// instantiated in the module's context.
//
// So the definition lives in read_file.cpp, an ordinary translation unit that
// belongs to no module and does the instantiation on its own.

#include <cstdint>
#include <filesystem>
#include <vector>

namespace FFXI
{
std::vector<uint8_t> read_whole_file(const std::filesystem::path& path);
}
