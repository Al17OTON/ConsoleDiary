#include "Writer.h"
#include "Config.h"
#include <fstream>
#include <iostream>

string writer::escape_csv(const string& field)
{
    // 특수문자가 없으면 그대로 반환
    bool needs_quote = field.find_first_of(",\"\n\r") != string::npos;
    if (!needs_quote)
        return field;

    std::string result;
    result.reserve(field.size() + 2);
    result += '"';
    for (char c : field)
    {
        if (c == '"')
            result += '"'; // " -> "" 이스케이프
        result += c;
    }
    result += '"';
    return result;
}

void writer::save_binary(const vector<vector<uint8_t>> chunks)
{
    ofstream file_stream(config::get_binary_file_path(), ios::binary);

    if (!file_stream.is_open())
    {
        cout << "Failed to open file for writing: " << config::get_binary_file_path() << endl;
        return;
    }

    size_t count = chunks.size();
    file_stream.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& chunk : chunks) 
    {
        size_t size = chunk.size();
        file_stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file_stream.write(reinterpret_cast<const char*>(chunk.data()), size);
    }
}

void writer::save_csv(const vector<vector<string>>& chunks)
{
    ofstream file_stream(config::get_csv_file_path(), ios::out | ios::trunc);

    if (!file_stream.is_open()) 
    {
		cout << "Failed to open file for writing: " << config::get_csv_file_path() << endl;
        return;
    }

    for (int i = 0; i < chunks.size(); ++i) 
    {
		for (int j = 0; j < chunks[i].size(); ++j)
		{
            if (j > 0) 
            {
                file_stream << ',';
            }
            file_stream << escape_csv(chunks[i][j]);
		}
		file_stream << '\n';
    }
}
