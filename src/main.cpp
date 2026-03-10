#include <chrono>
#include <cstdio>
#include <cstring>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define JSON_HAS_CPP_20 1
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ctt
{
    enum class Status
    {
        TODO,
        IN_PROGRESS,
        DONE,
        INVALID = -1
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(Status, {{Status::INVALID, nullptr},
                                          {Status::TODO, "todo"},
                                          {Status::IN_PROGRESS, "in-progress"},
                                          {Status::DONE, "done"}});

    struct Task
    {
        int64_t id;
        Status status;
        std::string description;
        std::string createdAt; // yyyy-mm-dd hh:mm:ss
        std::string updatedAt; // yyyy-mm-dd hh:mm:ss
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task, id, status, description, createdAt, updatedAt);
} // namespace ctt

// TODO: remove redudant `file`, `path` parameters in function signatures
constexpr std::string_view json_path = "tasks.json";
constexpr std::string_view id_path = "id.txt";

json openJson(const std::string &path)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        std::ofstream ostrm(path);
        f.open(path);
    }
    json j;
    try
    {
        j = json::parse(f);
    }
    catch (const json::parse_error &e)
    {
        j = json::object();
        j["tasks"] = json::array();
    }
    return j;
}

inline bool equal(const std::string &str1, const std::string &str2)
{
    return str1.compare(str2) == 0;
}

void updateJSONFile(const std::string &file, const json &j)
{
    std::ofstream ofs(file, std::ios::out | std::ios::trunc);
    ofs << j.dump(2) << std::endl;
}

int64_t loadGlobalId(const std::string &path)
{
    std::ifstream ifs(path, std::ios::in);
    if (!ifs.is_open())
        return 0;

    int id = 0;
    ifs >> id;
    return id;
}

void updateGlobalId(int id, const std::string &path)
{
    std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    ofs << id;
}

int64_t getIDFromUserInput(const char *input)
{
    return static_cast<int64_t>(std::stoi(input));
}

template <typename F>
void modifyTask(int id, const std::string &file, F func)
{
    json j = openJson(file);
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

std::string getCurrentUTCTimePoint()
{
    return std::format("{0:%F} {0:%H-%M-%OS}", std::chrono::utc_clock::now());
}

void displayHelpInfo_Add()
{
    std::cout << "Usage: task-cli add <description>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<description>"
              << "= A description of the task.\n";
}

void displayHelpInfo_List()
{
    std::cout << "Usage: task-cli list [status]\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "[status]"
              << "= Filter tasks by status (todo, in-progress, done). If omitted, all tasks are listed.\n";
}

void displayHelpInfo_Update()
{
    std::cout << "Usage: task-cli update <id> <description>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to update.\n";
    std::cout << "  " << std::left << std::setw(30) << "<description>"
              << "= The new description of the task.\n";
}

void displayHelpInfo_MarkInProgress()
{
    std::cout << "Usage: task-cli mark-in-progress <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to mark as in-progress.\n";
}

void displayHelpInfo_MarkDone()
{
    std::cout << "Usage: task-cli mark-done <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to mark as done.\n";
}

void displayHelpInfo_Delete()
{
    std::cout << "Usage: task-cli delete <id>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<id>"
              << "= The ID of the task to delete.\n";
}

void displayHelpInfo()
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

void displayHelpInfo(const char *command)
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

void addNewTask(const std::string &description, const std::string &file, const std::string &id_path)
{
    const int64_t id = loadGlobalId(id_path);
    const std::string createdAt = getCurrentUTCTimePoint();
    const ctt::Task task{id, ctt::Status::TODO, description, createdAt, createdAt};
    json j = openJson(file);
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

void markTaskStatus(int id, ctt::Status status, const std::string &file)
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
    const json j = openJson(file);
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
                markTaskStatus(getIDFromUserInput(argv[2]), ctt::Status::IN_PROGRESS, file);
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
                markTaskStatus(getIDFromUserInput(argv[2]), ctt::Status::DONE, file);
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