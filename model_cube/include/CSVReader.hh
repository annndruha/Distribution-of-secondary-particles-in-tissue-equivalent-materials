#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>


/**
 * CSVReader class
 * 
 * for read .csv files by call getData
 *
 * @param filename csv file to read
 * @param skiprows how many first rows are skiped
 * @param delimeter delimeter of items in row
 * 
 * @return See getData docs
 */
class CSVReader
{
    std::string fileName;
    std::string delim;
    int skipr;
public:
    CSVReader(std::string filename, int skiprows = 12, std::string delimeter = ",") : fileName(filename), delim(delimeter), skipr(skiprows){ }
    std::vector<std::vector<std::string> > getData();
};


/**
 * First vectors - is lines of file. Second vectors - is string items.
 * @return vector<vector<string>>
 */
std::vector<std::vector<std::string>> CSVReader::getData()
{
    std::ifstream file(fileName);
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
    int i = 0;
    while (getline(file, line))
    {
        if (i >= skipr){
            std::vector<std::string> tokens;
            std::string token;
            std::stringstream ss(line);
            while (getline(ss, token, ',')){
                tokens.push_back(token);
            }
            dataList.push_back(tokens);
        }
        i += 1;
    }
    file.close();
    return dataList;
}
