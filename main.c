#include "data.h"

int main(int argc, char *argv[]) {
    // read_csv("nyc_pop.txt");
    // read_data("pop.data");
    // //add_data("pop.data");
    // //read_data("pop.data");
    // update_data("pop.data");
    // read_data("pop.data");

    char command[50];
    if (argc <= 1) {
        fgets(command, sizeof(command), stdin);
        sscanf(command, "%s", command);
    }
    else {
        sscanf(argv[1], "%s", command);
    }
    if (!strcmp(command, "-read_csv")) {
        read_csv("nyc_pop.txt");
    }
    else if (!strcmp(command, "-read_data")) {
        read_data("pop.data");
    }
    else if (!strcmp(command, "-add_data")) {
        add_data("pop.data");
    }
    else if (!strcmp(command, "-update_data")) {
        update_data("pop.data");
    }
    return 0;
}