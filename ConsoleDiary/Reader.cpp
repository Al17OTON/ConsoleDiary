#include "Reader.h"
#include <fstream>
#include "Config.h"

vector<vector<uint8_t>> reader::load() 
{
    ifstream ifs(FILE_PATH, ios::binary);

    if (!ifs.is_open()) 
    {
        return {};
    }

    size_t count;
    ifs.read(reinterpret_cast<char*>(&count), sizeof(count));

    vector<vector<uint8_t>> chunks(count);
    for (auto& chunk : chunks) 
    {
        size_t size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
        chunk.resize(size);
        ifs.read(reinterpret_cast<char*>(chunk.data()), size);
    }
    return chunks;
}
