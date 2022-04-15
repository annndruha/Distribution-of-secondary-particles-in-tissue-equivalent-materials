#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>


class CSVReader
{
    std::string fileName;
    std::string delimeter;
public:
    CSVReader(std::string filename, std::string delm = ",") : fileName(filename), delimeter(delm){ }
    std::vector<std::vector<std::string> > getData();
};


std::vector<std::vector<std::string> > CSVReader::getData()
{
    std::ifstream file(fileName);
    std::vector<std::vector<std::string> > dataList;
    std::string line = "";
    while (getline(file, line))
    {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(line);
        while (getline(ss, token, ',')){
            tokens.push_back(token);
        }
        dataList.push_back(tokens);
    }
    file.close();
    return dataList;
}
