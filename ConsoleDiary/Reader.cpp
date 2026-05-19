#include "Reader.h"
#include <fstream>
#include "Config.h"

vector<string> reader::parse_row(const string& line)
{
    vector<string> fields;
    string field;
    bool in_quotes = false;

    for (size_t i = 0; i < line.size(); ++i)
    {
        char c = line[i];

        if (in_quotes)
        {
            if (c == '"')
            {
                // 다음 문자도 " 이면 이스케이프된 " 하나
                if (i + 1 < line.size() && line[i + 1] == '"')
                {
                    field += '"';
                    ++i;
                }
                else
                {
                    in_quotes = false; // 닫는 따옴표
                }
            }
            else
            {
                field += c;
            }
        }
        else
        {
            if (c == '"')
            {
                in_quotes = true; // 여는 따옴표
            }
            else if (c == ',')
            {
                fields.push_back(field);
                field.clear();
            }
            else
            {
                field += c;
            }
        }
    }
    fields.push_back(field); // 마지막 필드

    return fields;
}

vector<vector<uint8_t>> reader::load_binary()
{
    ifstream file_stream(config::get_binary_file_path(), ios::binary);

    if (!file_stream.is_open()) 
    {
        return {};
    }

    size_t count;
    file_stream.read(reinterpret_cast<char*>(&count), sizeof(count));
    vector<vector<uint8_t>> chunks(count);

    for (auto& chunk : chunks) 
    {
        size_t size;
        file_stream.read(reinterpret_cast<char*>(&size), sizeof(size));
        chunk.resize(size);
        file_stream.read(reinterpret_cast<char*>(chunk.data()), size);
    }
    return chunks;
}

vector<vector<string>> reader::load_scv()
{
    vector<vector<string>> result;
    ifstream file_stream(config::get_csv_file_path());

	if (!file_stream.is_open())
	{
        return result;
	}

    string line;

    while (getline(file_stream, line))
    {
        // Windows CRLF 대응
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.empty())
        {
            continue;
        }

        result.push_back(parse_row(line));
    }

    return result;
}
