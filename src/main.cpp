#include <iostream>
#include <string_view>

#include "ctt/task.hpp"
#include "ctt/ui.hpp"

int main(int argc, char *argv[])
{
    using namespace ctt::ui;
    using namespace ctt::task;

    if (argc < 2)
    {
        displayHelpInfo();
        return 0;
    }

    const std::string_view op = argv[1];

    if (op == "add")
    {
        if (argc < 3) // no description
            displayHelpInfo("add");
        else
            addNewTask(argv[2]);
    }
    else if (op == "update")
    {
        if (argc < 3) // no id
            displayHelpInfo("update");
        else
            try
            {
                updateTask(getIDFromUserInput(argv[2]), (argc < 4 ? "" : argv[3]));
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "ID must be a valid integer\n";
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "ID value is out of range\n";
            }
    }
    else if (op == "delete")
    {
        if (argc < 3) // no id
            displayHelpInfo("delete");
        else
            try
            {
                deleteTask(getIDFromUserInput(argv[2]));
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "ID must be a valid integer\n";
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "ID value is out of range\n";
            }
    }
    else if (op == "list")
    {
        if (argc < 3) // no status
            listTasks();
        else
            listTasks(argv[2]);
    }
    else if (op == "mark-in-progress")
    {
        if (argc < 3) // no id
            displayHelpInfo("mark-in-progress");
        else
            try
            {
                markTaskStatus(getIDFromUserInput(argv[2]), Status::In_Progress);
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "ID must be a valid integer\n";
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "ID value is out of range\n";
            }
    }
    else if (op == "mark-done")
    {
        if (argc < 3) // no id
            displayHelpInfo("mark-done");
        else
            try
            {
                markTaskStatus(getIDFromUserInput(argv[2]), Status::Done);
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "ID must be a valid integer\n";
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "ID value is out of range\n";
            }
    }
    else if (op == "help")
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