#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

void displayHelpInfo()
{
    // TODO: Output descriptive help man-like page
    std::cout << "Help command";
}

int main(int argc, char *argv[])
{
    // Parse CLI commands
    if (argc < 2)
    {
        displayHelpInfo();
    }
    else
    {
        std::ifstream f("test.json");
        json data = json::parse(f);
        std::cout << data["pi"] << '\n';
    }
    return 0;
}