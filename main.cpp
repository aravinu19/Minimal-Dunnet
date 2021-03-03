#include "json.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include "game.hpp"

using std::string;
using json = nlohmann::json;

#ifdef _WIN32
char clear_screen_cmd[] = "cls";
#else
char clear_screen_cmd[] = "clear";
#endif

bool checkIfFileExists(string);
void clearScreen();

int main(int argumentCount, char *argumentVector[])
{

    string map_file;

    clearScreen();

    if (argumentCount > 0)
    {
        map_file = argumentVector[1];

        if (checkIfFileExists(map_file))
        {
            std::cout << map_file << " Map File is Found" << std::endl;
            clearScreen();
            Game instance(map_file);
        }
        else
        {
            std::cout << map_file << " Map File is not Found" << std::endl;
            exit(0);
        }
    }
    else
    {
        std::cout << "Map File Not Provided" << std::endl;
        std::cout << "Usage: main <map_file_name>.json" << std::endl;
        map_file = "map1.json";

        if (checkIfFileExists(map_file))
        {
            std::cout << "Using Default Map Data File" << std::endl;
            // clearScreen();
            // Game instance(map_file);
        }
        else
        {
            std::cout << "Usage: main <map_file_name>.json" << std::endl;
            exit(0);
        }
    }

    return 0;
}

bool checkIfFileExists(string file_name)
{

    std::ifstream file;
    file.open(file_name);

    return file ? true : false;
}

void clearScreen()
{
    system(clear_screen_cmd);
}