#ifndef WINNOW_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define WINNOW_H

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>

void winnowing_rolling_hash(std::string text, std::map <int, std::vector<int> > &sig,int no_of_lines);
void createFileList(char *directory, std::vector<std::string> &file_list);
std::map <int, std::vector<int> > create_signature(std::string filex);

#endif