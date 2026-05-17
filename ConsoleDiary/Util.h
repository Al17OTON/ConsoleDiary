#pragma once
#include <vector>
#include <string>
#include <cstring>

class util 
{
public:
    template<typename T>
    static inline void write_bytes(std::vector<uint8_t>& buf, const T& value) 
    {
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&value);
        buf.insert(buf.end(), ptr, ptr + sizeof(T));
    }

    static inline void write_bytes(std::vector<uint8_t>& buf, const std::string& str) 
    {
        size_t len = str.size();
        write_bytes(buf, len);
        buf.insert(buf.end(), str.begin(), str.end());
    }

    template<typename T>
    static inline void read_bytes(const std::vector<uint8_t>& buf, size_t& offset, T& value) 
    {
        std::memcpy(&value, buf.data() + offset, sizeof(T));
        offset += sizeof(T);
    }

    static inline void read_bytes(const std::vector<uint8_t>& buf, size_t& offset, std::string& str) 
    {
        size_t len;
        read_bytes(buf, offset, len);
        str.assign(reinterpret_cast<const char*>(buf.data() + offset), len);
        offset += len;
    }
};

