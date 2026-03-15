#include <iostream>
#include <string_view>

#include "ctt/task.hpp"
#include "ctt/ui.hpp"

int main(int argc, char *argv[])
{
    using namespace ctt::ui;
    using namespace ctt::task;
    using namespace ctt::utility;

    if (argc < 2)
    {
        displayHelpInfo();
        return 0;
    }

    const std::string_view op = argv[1];

    auto tryGetID = [](const char *input) -> std::optional<std::int64_t>
    {
        try
        {
            return getIDFromUserInput(input);
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << '\n';
            return std::nullopt;
        }
    };

    if (op == "add")
    {
        if (argc < 3) // no description
            displayHelpInfo("add");
        else
            addNewTask(argv[2]);
    }
    else if (op == "update")
    {
        if (argc < 3)
            displayHelpInfo("update");
        else if (auto id = tryGetID(argv[2]))
            updateTask(*id, (argc < 4 ? "" : argv[3]));
    }
    else if (op == "delete")
    {
        if (argc < 3)
            displayHelpInfo("delete");
        else if (auto id = tryGetID(argv[2]))
            deleteTask(*id);
    }
    else if (op == "list")
    {
        if (argc < 3) // no status
            listTasks();
        else
            listTasks(argv[2]);
    }
    else if (op == "mark-in-progress" || op == "mark-done")
    {
        if (argc < 3)
            displayHelpInfo(op);
        else if (auto id = tryGetID(argv[2]))
            markTaskStatus(*id, op == "mark-done" ? Status::Done : Status::In_Progress);
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