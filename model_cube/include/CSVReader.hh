#ifndef CSVReader_h
#define CSVReader_h 1

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>

////============= EXAMPLE OF USAGE =============
//
//  CSVReader reader("you_filename.csv", 12);
//  std::vector<std::vector<std::string>> data = reader.getData();
//  
//  for (int i=0; i < reader.len(); i++){
//      std::cout << data[i][7] << std::endl;
//  }
//
////============================================

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
private:
    std::vector<std::vector<std::string>> _data;
    int _length = 0;

public:
    CSVReader(std::string filename, int skiprows = 12, std::string delimeter = ",") : fileName(filename), delim(delimeter), skipr(skiprows)
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
        _data = dataList;
        _length = i - skipr;
    }
    std::vector<std::vector<std::string>> getData();
    int len();
};

#endif