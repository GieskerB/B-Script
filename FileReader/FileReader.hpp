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
    std::fstream m_file;

    void close_file();

public:

    FileReader();
    ~FileReader();

    std::string read_line();

    FileReaderState get_state();

    bool can_read();

    void open_file(const std::string &);

};


#endif //B_SHARP_FILEREADER_HPP
