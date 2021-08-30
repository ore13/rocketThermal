#include "CsvWriter.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int CsvWriter::addColumn(std::string header, std::vector<double> &column_data)
{
    dataElement element(header);
    element.column = column_data;
    data.push_back(element);
    return 0;
}

int CsvWriter::writeFile(std::string filename, char separator)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return 1;
    }

    // # so that gnuplot ignores headers
    file << "#";
    for (int j = 0; j < data.size(); j++)
    {
        file << data[j].header;
        file << separator;
    }
    file << std::endl;

    for (int i = 0; i < data[0].column.size(); i++)
    {
        for (int j = 0; j < data.size(); j++)
        {
            file << std::to_string(data[j].column[i]);
            file << separator;
        }
        file << std::endl;
    }
    return 0;
}