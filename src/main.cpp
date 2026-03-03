#include <iostream>

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
    }
    return 0;
}