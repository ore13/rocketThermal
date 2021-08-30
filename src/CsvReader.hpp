#ifndef CSV_READER
#define CSV_READER
#include <vector>
#include <string>

class CsvReader
{
public:
    
    // Constructor
    CsvReader() {};
    // Destructor
    ~CsvReader() {};
    // Read a specified file
    int readFile(std::string filename);
    // get a column by name
    int getColumn(std::vector<double> &column, int column_number);
    // get a column by 0-indexed column
    int getColumn(std::vector<double> &column, std::string column_name);
protected:
    // Data representation of a csv column with header
    struct dataElement {
        std::string header;
        std::vector<double> column;

        // Constructer
        dataElement(std::string head)
        {
            header = head;
        }
    };

    // Data representation of csv rows
    std::vector<dataElement> data;

    // Method to read line and split into comma seperated values
    void splitLine(std::vector<std::string> &separated_line, std::string &line);
};

#endif