#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "ctt/task.hpp"
#include "ctt/ui.hpp"

int main(int argc, char *argv[])
{
    using namespace ctt::ui;
    using namespace ctt::task;

    // Parse CLI commands
    if (argc < 2 || (equal(argv[1], "help") && argc < 3))
    {
        displayHelpInfo();
        return 0;
    }

    const std::string op = argv[1];
    const std::string file = "tasks.json";
    const std::string id_path = "id.txt";

    if (equal(op, "add"))
    {
        // TODO: properly track time stamps
        if (argc < 3) // didn't provide any description
            displayHelpInfo("add");
        else
            addNewTask(argv[2], file, id_path);
    }
    else if (equal(op, "update"))
    {
        if (argc < 3) // didn't provide any id
            displayHelpInfo("update");
        else
            try
            {
                updateTask(getIDFromUserInput(argv[2]), (argc < 4 ? "" : argv[3]), file);
            }
            catch (std::invalid_argument)
            {
                std::cout << "ID must be a valid integer\n";
                return 0;
            }
            catch (std::out_of_range)
            {
                std::cout << "ID value is out of range\n";
                return 0;
            }
    }
    else if (equal(op, "delete"))
    {
        if (argc < 3) // didn't provide any id
            displayHelpInfo("delete");
        else
            try
            {
                deleteTask(getIDFromUserInput(argv[2]), file);
            }
            catch (std::invalid_argument)
            {
                std::cout << "ID must be a valid integer\n";
                return 0;
            }
            catch (std::out_of_range)
            {
                std::cout << "ID value is out of range\n";
                return 0;
            }
    }
    else if (equal(op, "list"))
    {
        if (argc < 3) // didn't provide any status
            listTasks(file);
        else
            listTasks(file, argv[2]);
    }
    else if (equal(op, "mark-in-progress"))
    {
        if (argc < 3) // didn't provide any id
            displayHelpInfo("mark-in-progress");
        else
            try
            {
                markTaskStatus(getIDFromUserInput(argv[2]), Status::IN_PROGRESS, file);
            }
            catch (std::invalid_argument)
            {
                std::cout << "ID must be a valid integer\n";
                return 0;
            }
            catch (std::out_of_range)
            {
                std::cout << "ID value is out of range\n";
                return 0;
            }
    }
    else if (equal(op, "mark-done"))
    {
        if (argc < 3) // didn't provide any id
            displayHelpInfo("mark-done");
        else
            try
            {
                markTaskStatus(getIDFromUserInput(argv[2]), Status::DONE, file);
            }
            catch (std::invalid_argument)
            {
                std::cout << "ID must be a valid integer\n";
                return 0;
            }
            catch (std::out_of_range)
            {
                std::cout << "ID value is out of range\n";
                return 0;
            }
    }
    else if (equal(op, "help"))
    {
        if (argc < 3) // didn't provide specific command
            displayHelpInfo();
        else
            displayHelpInfo(argv[2]);
    }
    else
    {
        displayHelpInfo();
    }

    return 0;
}