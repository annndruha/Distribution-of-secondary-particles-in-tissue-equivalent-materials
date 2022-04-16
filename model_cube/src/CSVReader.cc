#include "CSVReader.hh"
/**
 * First vectors - is lines of file. Second vectors - is string items.
 * @return vector<vector<string>>
 */
std::vector<std::vector<std::string>> CSVReader::getData()
{
    return _data;
}

/**
 * Return length of readed lines (excluded skiped)
 * @return int
 */
int CSVReader::len()
{
    return _length;
}