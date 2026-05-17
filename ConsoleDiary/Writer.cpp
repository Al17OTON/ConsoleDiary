#include "Writer.h"
#include "Config.h"
#include <fstream>

void writer::save(const vector<vector<uint8_t>> chunks) 
{
    std::ofstream ofs(FILE_PATH, std::ios::binary);

    size_t count = chunks.size();
    ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& chunk : chunks) 
    {
        size_t size = chunk.size();
        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
        ofs.write(reinterpret_cast<const char*>(chunk.data()), size);
    }
}
