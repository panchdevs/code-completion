#ifndef WINNOW_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define WINNOW_H

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>

void winnowing_rolling_hash(string text, map <int, vector<int> > &sig,int no_of_lines);
void createFileList(char *directory, vector<string> &file_list);
map <int, vector<int> > create_signature(string filex);

#endif