#include "ui.hpp"

#include <iomanip>

#include "utility.hpp"

using namespace ctt;

void ui::displayHelpInfo_Add()
{
    std::cout << "Usage: task-cli add <description>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<description>"
              << "= A description of the task.\n";
}

void ui::displayHelpInfo_List()
{
    std::cout << "Usage: task-cli list [status]\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "[status]"
              << "= Filter tasks by status (todo, in-progress, done). If omitted, all tasks are listed.\n";
}

void ui::displayHelpInfo_Update()
{
    std::cout << "Usage: task-cli update <id> <description>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to update.\n";
    std::cout << "  " << std::left << std::setw(30) << "<description>"
              << "= The new description of the task.\n";
}

void ui::displayHelpInfo_MarkInProgress()
{
    std::cout << "Usage: task-cli mark-in-progress <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to mark as in-progress.\n";
}

void ui::displayHelpInfo_MarkDone()
{
    std::cout << "Usage: task-cli mark-done <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to mark as done.\n";
}

void ui::displayHelpInfo_Delete()
{
    std::cout << "Usage: task-cli delete <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to delete.\n";
}

void ui::displayHelpInfo()
{
    std::cout << "task-cli - A simple non-overwhelming command-line task tracker\n\n";
    std::cout << "Usage: task-cli <command> [arguments...]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  " << std::left << std::setw(30) << "add <description>"
              << "Add a new task.\n";
    std::cout << "  " << std::left << std::setw(30) << "update <id> <description>"
              << "Update a task's description.\n";
    std::cout << "  " << std::left << std::setw(30) << "delete <id>"
              << "Delete a task.\n";
    std::cout << "  " << std::left << std::setw(30) << "list [status]"
              << "List tasks, optionally filtered by status.\n";
    std::cout << "  " << std::left << std::setw(30) << "mark-in-progress <id>"
              << "Mark a task as in-progress.\n";
    std::cout << "  " << std::left << std::setw(30) << "mark-done <id>"
              << "Mark a task as done.\n";
    std::cout << "  " << std::left << std::setw(30) << "help [command]"
              << "Show help for a specific command.\n";
}

void ui::displayHelpInfo(const char *command)
{
    if (equal(command, "add"))
        displayHelpInfo_Add();
    else if (equal(command, "update"))
        displayHelpInfo_Update();
    else if (equal(command, "list"))
        displayHelpInfo_List();
    else if (equal(command, "delete"))
        displayHelpInfo_Delete();
    else if (equal(command, "mark-in-progress"))
        displayHelpInfo_MarkInProgress();
    else if (equal(command, "mark-done"))
        displayHelpInfo_MarkDone();
    else
        displayHelpInfo();
}