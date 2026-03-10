#include <chrono>
#include <cstdio>
#include <cstring>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "task.hpp"
#include "ui.hpp"

// TODO: remove redudant `file`, `path` parameters in function signatures
constexpr std::string_view json_path = "tasks.json";
constexpr std::string_view id_path = "id.txt";

template <typename F>
void modifyTask(int id, const std::string &file, F func)
{
    json j = openJSON(file);
    auto it = j["tasks"].begin();
    for (; it != j["tasks"].end(); ++it)
    {
        if (it.value()["id"].get<std::int64_t>() == id)
        {
            func(j, it);
            updateJSONFile(file, j);
            return;
        }
    }
}

void addNewTask(const std::string &description, const std::string &file, const std::string &id_path)
{
    using namespace ctt::task;

    const int64_t id = loadGlobalId(id_path);
    const std::string createdAt = getCurrentUTCTimePoint();
    const Task task{id, Status::TODO, description, createdAt, createdAt};
    json j = openJSON(file);
    j["tasks"] += task;
    updateJSONFile(file, j);
    updateGlobalId(id + 1, id_path);
    std::cout << std::format("Added new task (ID: {})", id);
}

void updateTask(int id, const std::string &description, const std::string &file)
{
    auto func = [description](auto &j, auto it)
    {
        it.value()["description"] = description;
        it.value()["updatedAt"] = getCurrentUTCTimePoint();
    };
    modifyTask(id, file, func);
}

void markTaskStatus(int id, ctt::task::Status status, const std::string &file)
{
    auto func = [status](auto &j, auto it)
    {
        it.value()["status"] = status;
        it.value()["updatedAt"] = getCurrentUTCTimePoint();
    };
    modifyTask(id, file, func);
}

void deleteTask(int id, const std::string &file)
{
    auto func = [](auto &j, auto it)
    {
        j["tasks"].erase(it);
    };
    modifyTask(id, file, func);
}

void listTasks(const std::string &file, const std::string &status = "")
{
    const json j = openJSON(file);
    for (const auto &task : j["tasks"].items())
    {
        if (equal(status, "") || equal(status, task.value()["status"]))
        {
            std::cout << std::format("Task #{}:\n\t{}\n\tstatus:{}\n\tcreated:{}\n\tlast updated:{}\n",
                                     task.value()["id"].get<int64_t>(),
                                     task.value()["description"].get<std::string>(),
                                     task.value()["status"].get<std::string>(),
                                     task.value()["createdAt"].get<std::string>(),
                                     task.value()["updatedAt"].get<std::string>());
        }
    }
}

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