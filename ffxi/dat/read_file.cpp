// A plain translation unit on purpose - see read_file.h.

#include "read_file.h"

#include <fstream>
#include <stdexcept>

namespace FFXI
{
std::vector<uint8_t> read_whole_file(const std::filesystem::path& path)
{
    std::ifstream file{path, std::ios::ate | std::ios::binary};

    if (!file.good())
        throw std::runtime_error("dat not found: " + path.string());

    std::vector<uint8_t> buffer(static_cast<size_t>(file.tellg()));

    file.seekg(0);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    return buffer;
}
} // namespace FFXI
