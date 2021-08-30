#include "CsvReader.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int CsvReader::getColumn(std::vector<double> &column, std::string column_name)
{
    int i = 0;
    bool found = false;
    while (i < data.size() && !found)
    {
        if (data[i].header.compare(column_name) == 0)
        {
            found = true;
            column = data[i].column;
        }
        i++;
    }
    if (!found)
    {
        return 1;
    }
    return 0;
}

int CsvReader::getColumn(std::vector<double> &column, int column_number)
{
    if (column_number > data.size())
    {
        return 1;
    }
    column = data[column_number].column;
    return 0;
}

/*
int CsvReader::readFile()
load the data specified by the file into memory.

RETURN:
    1 if the file cannot be opened
    0 if the file read succeeded.
*/
int CsvReader::readFile(std::string filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        return 1;
    }
    std::string line;

    // Read the header line at the top
    std::getline(file, line);
    std::vector<std::string> separated_line;
    CsvReader::splitLine(separated_line, line);
    for (std::string column_head : separated_line)
    {
        // Load the numeric header data
        data.push_back(dataElement(column_head));
    }

    // load the numeric data
    while ( std::getline(file, line) )
    {
        std::vector<std::string> separated_line;
        CsvReader::splitLine(separated_line, line);
        int i = 0;
        // load data. Note that data will not be loaded if the line is
        // longer than the header.
        while (i < separated_line.size() && i < data.size())
        {
            data[i].column.push_back(std::stod(separated_line[i]));
            i++;
        }
    }
    file.close();

    return 0;
}

void CsvReader::splitLine(std::vector<std::string> &separated_line, std::string &line)
{
    // Move to string helper class
    int start = 0;
    int substring_length = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] != ',') // compares strings, return 0 if equal
        {
            substring_length++;
        }
        else if (substring_length > 0)
        {
            separated_line.push_back(line.substr(start, substring_length));
            start += substring_length + 1;
            substring_length = 0;
        }
        else // The program tried to append a line of length zero
        {
            std::cout << "Line of length zero detected" << std::endl;
        }
    }
    // ensure the last column is added
    separated_line.push_back(line.substr(start, substring_length));
}


