//
// Created by tywael on 1/5/23.
//

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../inc/HttpException.hpp"

const std::string WHITESPACE = " \n\r\t\f\v";

std::vector<std::string> readFile(std::string fileName) {
	std::string line;
	std::ifstream file;
	std::vector<std::string> _lines;

	file.open(fileName.c_str(), std::ios::in | std::ios::binary);

	if (file.is_open()) {
		// check if file is text or binary
		bool isTextFile = true;
		char c;
		while (file.get(c)) {
			if (!isprint((int)c) && !isspace((int)c)) {
				isTextFile = false;
				break;
			}
		}
		file.clear();
		file.seekg(0, std::ios::beg);
		if (isTextFile) {
			while (std::getline(file, line)) {
				_lines.push_back(line);
			}
		} else {
			std::istreambuf_iterator<char> it(file.rdbuf());
			std::istreambuf_iterator<char> eos;
			std::string str(it, eos);
			_lines.push_back(str);
		}
		file.close();
	} else if (errno) {
        catchErrno();
    }
//    for (std::vector<std::string>::iterator it = _lines.begin(); it < _lines.end(); it++)
//        std::cout << "DEBUG: "<< *it << std::endl;
	return _lines;
}

std::string concatPath(std::string str1, std::string str2)
{
    if (str1.back() == '/' && str2.front() == '/')
        str1.erase(str1.size() - 1);
    else if (str1.back() != '/' && str2.front() != '/')
        str1.push_back('/');
    return (str1 + str2);
}
size_t findKey(std::string line, std::string search)
{
    size_t ret;

    ret = line.find(search);
    if (ret == 0 || line[ret - 1] == ' ' || line[ret - 1] == '{' || line[ret - 1] == ';')
        return (ret);
    return (std::string::npos);
}

std::string getVal(std::string line, std::string attrib, size_t pos) {
    size_t lenWord;
    size_t lenTemp;
    std::string temp;

    pos += std::string(attrib).size();
    pos = line.find_first_not_of(" ", pos);
    lenWord = line.find(" ", pos) - (pos);
    lenTemp = line.find(";", pos) - (pos);
    if (lenTemp < lenWord)
        lenWord = lenTemp;
    temp = line.substr(pos, lenWord);
    if (temp.back() == ';')
        temp.erase(temp.back());
    return (temp);
}

bool    skip_space(std::string &line)
{
    if (line[0] == ' ') {
        line.erase(0, line.find_first_not_of(' '));
        return (true);
    }
    return (false);
}

std::string cut_word(std::string &line, size_t pos)
{
    std::string temp;

    temp = line.substr(0, pos);
    if (temp == "")
        temp = line;
    line.erase(0, temp.size());
    return (temp);
}

std::vector<std::string> split(std::string line, std::string sep)
{
    std::vector<std::string> ret;
    size_t pos = 0;
    size_t n;


    n = line.find(";");
    if (n != std::string::npos)
        line = line.substr(0, n);
    while ((pos = line.find(sep)) != std::string::npos)
    {
        if (skip_space(line))
            continue ;
        ret.push_back(cut_word(line, pos));
    }
    pos = line.find("\n");
    if (!line.empty())
        ret.push_back(cut_word(line, pos));
    ret.erase(ret.begin());
    return (ret);
}

std::vector<std::string> spliter(const std::string& s, const std::string& delimiter) {
	std::vector<std::string> parts;
	std::string::size_type start = 0;
	std::string::size_type end = s.find(delimiter);
	while (end != std::string::npos) {
		parts.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
		end = s.find(delimiter, start);
	}
	parts.push_back(s.substr(start));
	return parts;
}

bool hasSuffix(const std::string &str, const std::string &suffix) {
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}