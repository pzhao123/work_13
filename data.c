#include "data.h"

struct pop_entry * make_entry(int year, int population, char * boro) {
    struct pop_entry *p = malloc(sizeof(struct pop_entry));
    p->year = year;
    p->population = population;
    strcpy(p->boro, boro);
    return p;
}

void print_entry(struct pop_entry *p) {
    if (p) printf("year: %d\tboro: %s\tpop: %d\n", p->year, p->boro, p->population);
}

int count_lines(char * data, int size) {
    int num = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (data[i] == '\n') num++;
    }
    return num;
}

void read_csv(char * csv) {
    //read in nyc_pop.txt, store data in strucs, makes pop.data
    int file = open(csv, O_RDONLY, 400);
    if (file == -1) {
        printf("Opening File Error: %s\n", strerror(errno));
    }
    struct stat info;
    stat(csv, &info);
    char data[info.st_size];
    printf("reading %s\n", csv);
    int input = read(file, data, info.st_size);
    if (input == -1) {
        printf("Reading File Error: %s\n", strerror(errno));
    }
    int lines = count_lines(data, info.st_size);
    close(file);
    //printf("%d\n", lines);
    char *temp = data;
    char * boros[5] = {"Manhattan", "Brooklyn", "Queens", "Bronx", "Staten Island"};
    struct pop_entry dataset[(lines-1) * 5];
    int i;
    for (i = 0; i < lines; i++) {
        int line[6];
        temp = strchr(temp, '\n') + 1;
        sscanf(temp, "%d, %d, %d, %d, %d, %d", line, line + 1, line + 2, line + 3, line +4, line + 5);
        int j;
        for (j = 1; j < 6; j++) {
            (&dataset[j-1+(i*5)])->year = line[0];
            (&dataset[j-1+(i*5)])->population = line[j];
            strcpy((&dataset[j-1+(i*5)])->boro, boros[j-1]);
        }
    }
    int new = open("pop.data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (new == -1) {
        printf("Creating New File Error: %s\n", strerror(errno));
    }
    int add = write(new, dataset, sizeof(dataset));
    if (add == -1) {
        printf("Writing To New File Error: %s\n", strerror(errno));
    }
    printf("wrote %ld bytes to pop.data\n", sizeof(dataset));
}

void read_data(char * file) {
    //read in pop.data and display
    int input = open(file, O_RDONLY, 400);
    if (input == -1) {
        printf("Opening File Error: %s\n", strerror(errno));
    }
    struct pop_entry *dataset = malloc(input);
    struct stat info;
    stat(file, &info);
    int add = read(input, dataset, info.st_size);
    if (add == -1) {
        printf("Reading File Error: %s\n", strerror(errno));
    }
    int i;
    for (i = 0; i < info.st_size/sizeof(struct pop_entry); i++) {
        printf("%d: ", i);
        print_entry(&(dataset[i]));
    }
    free(dataset);
    close(input);
}

void add_data(char * file) {
    //append inputted data into pop.data
    char data[200];
    printf("Enter year boro pop: ");
    fgets(data, sizeof(data), stdin);
    int year;
    char *boro;
    int pop;
    struct pop_entry entry;
    sscanf(data,"%d %s %d", &entry.year, entry.boro, &entry.population);
    int input = open(file, O_WRONLY | O_APPEND, 600);
    if (input == -1) {
        printf("Opening File Error: %s\n", strerror(errno));
    }
    int add = write(input, &entry, sizeof(struct pop_entry));
    if (add == -1) {
        printf("Adding To New File Error: %s\n", strerror(errno));
    }
    printf("Appended data to file: year: %d\tboro: %s\tpop: %d\n", entry.year, entry.boro, entry.population);
    close(input);
}

void update_data(char * file) {
    read_data(file);
    char num[200];
    printf("entry to update: ");
    fgets(num, sizeof(num), stdin);
    int entry_num;
    sscanf(num, "%d", &entry_num);
    char input[200];
    printf("Enter year boro pop: ");
    fgets(input, sizeof(input), stdin);
    struct pop_entry entry;
    int year;
    int pop;
    char *boro;
    sscanf(input,"%d %s %d", &entry.year, entry.boro, &entry.population);
    int data = open(file, O_RDWR, 600);
    if (data == -1) {
        printf("Opening File Error: %s\n", strerror(errno));
    }
    lseek(data, sizeof(struct pop_entry) * entry_num, SEEK_SET);
    int add = write(data, &entry, sizeof(entry));
    if (add == -1) {
        printf("Adding To New File Error: %s\n", strerror(errno));
    }
    close(data);
    printf("File updated.\n");
}
