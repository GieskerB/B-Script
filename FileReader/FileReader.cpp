#include "FileReader.hpp"

void FileReader::close_file() {
    if(can_read()) {
        m_file.close();
    }
}

FileReader::FileReader(): m_state(FileReaderState::EMPTY) {

}

FileReader::~FileReader() {
    close_file();
}


std::string FileReader::read_line() {
    if(!can_read()) {
        throw std::runtime_error("Can not Read the file!");
    }
    m_state = FileReaderState::READING;
    std::string line;
    if(!static_cast<bool>(std::getline(m_file, line))) {
        m_state = FileReaderState::DONE;
        m_file.close();
    }
    return line;
}

std::string FileReader::read_line(unsigned int line_number) {
    for (unsigned int line{0}; line < line_number;++line) {
        read_line();
    }
    return read_line();
}

FileReaderState FileReader::get_state() {
    return m_state;
}

bool FileReader::can_read() {
    return m_state == FileReaderState::OPEN or m_state == FileReaderState::READING;
}

void FileReader::open_file(const std::string & file_name) {
    close_file();
    m_file.open("../" + file_name);
    if( m_file.is_open()) {
        m_state = FileReaderState::OPEN;
    } else {
        m_state = FileReaderState::ERROR;
    }
}
