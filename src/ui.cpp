#include "ctt/ui.hpp"

#include <format>
#include <iostream>

#include "ctt/utility.hpp"

using namespace ctt;

void ui::displayHelpInfo_Add()
{
    std::cout << "Usage: task-cli add <description>\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= A description of the task.\n", "<description>");
}

void ui::displayHelpInfo_List()
{
    std::cout << "Usage: task-cli list [status]\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= Filter tasks by status (todo, in-progress, done). If omitted, all tasks are listed.\n", "[status]");
}

void ui::displayHelpInfo_Update()
{
    std::cout << "Usage: task-cli update <id> <description>\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= The ID of the task to update.\n", "<id>");
    std::cout << std::format("  {:<30}= The new description of the task.\n", "<description>");
}

void ui::displayHelpInfo_MarkInProgress()
{
    std::cout << "Usage: task-cli mark-in-progress <id>\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= The ID of the task to mark as in-progress.\n", "<id>");
}

void ui::displayHelpInfo_MarkDone()
{
    std::cout << "Usage: task-cli mark-done <id>\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= The ID of the task to mark as done.\n", "<id>");
}

void ui::displayHelpInfo_Delete()
{
    std::cout << "Usage: task-cli delete <id>\n\n";
    std::cout << "Options: \n";
    std::cout << std::format("  {:<30}= The ID of the task to delete.\n", "<id>");
}

void ui::displayHelpInfo()
{
    std::cout << "task-cli - A simple non-overwhelming command-line task tracker\n\n";
    std::cout << "Usage: task-cli <command> [arguments...]\n\n";
    std::cout << "Commands:\n";
    std::cout << std::format("  {:<30}Add a new task.\n", "add <description>");
    std::cout << std::format("  {:<30}Update a task's description.\n", "update <id> <description>");
    std::cout << std::format("  {:<30}Delete a task.\n", "delete <id>");
    std::cout << std::format("  {:<30}List tasks, optionally filtered by status.\n", "list [status]");
    std::cout << std::format("  {:<30}Mark a task as in-progress.\n", "mark-in-progress <id>");
    std::cout << std::format("  {:<30}Mark a task as done.\n", "mark-done <id>");
    std::cout << std::format("  {:<30}Show help for a specific command.\n", "help [command]");
}

void ui::displayHelpInfo(const std::string_view command)
{
    if (command == "add")
        displayHelpInfo_Add();
    else if (command == "update")
        displayHelpInfo_Update();
    else if (command == "list")
        displayHelpInfo_List();
    else if (command == "delete")
        displayHelpInfo_Delete();
    else if (command == "mark-in-progress")
        displayHelpInfo_MarkInProgress();
    else if (command == "mark-done")
        displayHelpInfo_MarkDone();
    else
        displayHelpInfo();
}