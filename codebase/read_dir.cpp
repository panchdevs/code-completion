#include <iostream>
#include <dirent.h>
#include <cstdio>

#define EXIT_FAILURE 0
using namespace std;

int main( int argc, char *argv[] )
{
 DIR *dir;
 struct dirent *ent;
 if ((dir = opendir (argv[1])) != NULL) {
  while ((ent = readdir (dir)) != NULL) {
    printf ("%s\n", ent->d_name);
  }
  closedir (dir);
} else {
  perror ("");
  return EXIT_FAILURE;
}
}