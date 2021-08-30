#ifndef CSV_WRITER
#define CSV_WRITER
#include <vector>
#include <string>

class CsvWriter
{
    public:
        // Constructor
        CsvWriter() {};
        
        // Destructor
        ~CsvWriter() {};

        // Add columns. Return 0 if successful, 1 if failed.
        int addColumn(std::string header, std::vector<double> &column_data);

        // Write to file. Return 0 if successful, 1 if failed.
        int writeFile(std::string file, char separator);
    
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
};

#endif