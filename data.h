#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

struct pop_entry {
    int year;
    int population;
    char boro[15];
};

struct pop_entry * make_entry(int year, int population, char * boro);

void print_entry(struct pop_entry *p);

int count_lines(char * data, int size);

void read_csv(char * csv);

void read_data(char * file);

void add_data(char * file);

void update_data(char * file);