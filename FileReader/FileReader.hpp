//
// Created by bjarn on 16.06.2024.
//

#ifndef B_SHARP_FILEREADER_HPP
#define B_SHARP_FILEREADER_HPP

#include <fstream>

enum FileReaderState {
    EMPTY,
    OPEN,
    READING,
    DONE,
    ERROR
};

class FileReader {

    FileReaderState m_state;
    std::string m_file_name;
    std::fstream m_file;

public:

    FileReader();
    ~FileReader();

    std::string read_line();
    std::string read_line(unsigned int);

    bool can_read();

    void open_file(const std::string &);

    void close_file();

};


#endif //B_SHARP_FILEREADER_HPP
