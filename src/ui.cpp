#include "ctt/ui.hpp"

#include <print>

#include "ctt/utility.hpp"

using namespace ctt;

namespace ctt
{
    namespace ui
    {
        void displayHelpInfo_Add()
        {
            std::print("Usage: task-cli add <description>\n\n");
            std::println("Options:");
            std::println("  {:<30}= A description of the task.", "<description>");
            // std::cout << std::format("  {:<30}= A description of the task.\n", "<description>");
        }

        void displayHelpInfo_List()
        {
            std::print("Usage: task-cli list [status]\n\n");
            std::println("Options:");
            std::println("  {:<30}= Filter tasks by status (todo, in-progress, done). If omitted, all tasks are listed.", "[status]");
        }

        void displayHelpInfo_Update()
        {
            std::print("Usage: task-cli update <id> <description>\n\n");
            std::println("Options:");
            std::println("  {:<30}= The ID of the task to update.", "<id>");
            std::println("  {:<30}= The new description of the task.", "<description>");
        }

        void displayHelpInfo_MarkInProgress()
        {
            std::print("Usage: task-cli mark-in-progress <id>\n\n");
            std::println("Options:");
            std::println("  {:<30}= The ID of the task to mark as in-progress.", "<id>");
        }

        void displayHelpInfo_MarkDone()
        {
            std::print("Usage: task-cli mark-done <id>\n\n");
            std::println("Options:");
            std::println("  {:<30}= The ID of the task to mark as done.", "<id>");
        }

        void displayHelpInfo_Delete()
        {
            std::print("Usage: task-cli delete <id>\n\n");
            std::println("Options:");
            std::println("  {:<30}= The ID of the task to delete.", "<id>");
        }

        void displayHelpInfo()
        {
            std::print("task-cli - A simple non-overwhelming command-line task tracker\n\n");
            std::print("Usage: task-cli <command> [arguments...]\n\n");
            std::println("Commands:");
            std::println("  {:<30}Add a new task.", "add <description>");
            std::println("  {:<30}Update a task's description.", "update <id> <description>");
            std::println("  {:<30}Delete a task.", "delete <id>");
            std::println("  {:<30}List tasks, optionally filtered by status.", "list [status]");
            std::println("  {:<30}Mark a task as in-progress.", "mark-in-progress <id>");
            std::println("  {:<30}Mark a task as done.", "mark-done <id>");
            std::println("  {:<30}Show help for a specific command.", "help [command]");
        }

        void displayHelpInfo(const std::string_view command)
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
    } // namespace ui
} // namespace ctt
