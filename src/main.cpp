#include <cstdio>
#include <cstring>
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
                                          {Status::IN_PROGRESS, "in progress"},
                                          {Status::DONE, "done"}});

    struct Task
    {
        int id;
        Status status;
        std::string description;
        std::string createdAt; // yyyy-mm-dd hh:mm:ss
        std::string updatedAt; // yyyy-mm-dd hh:mm:ss
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task, id, status, description, createdAt, updatedAt);
} // namespace ctt

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

int loadGlobalId(const std::string &path)
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
              << "= Filter tasks by status (todo, in progress, done). If omitted, all tasks are listed.\n";
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
    // TODO: Output descriptive help man-like page
    std::cout << "Help command";
}

void displayHelpInfo(const char *command)
{
    if (equal(command, "add"))
    {
        displayHelpInfo_Add();
    }
    else if (equal(command, "list"))
    {
        displayHelpInfo_List();
    }
    else if (equal(command, "delete"))
    {
        displayHelpInfo_Delete();
    }
    else
    {
        displayHelpInfo();
    }
}

void addNewTask(const std::string &description, const std::string &file, const std::string &id_path)
{
    const int id = loadGlobalId(id_path);
    const ctt::Task task{id, ctt::Status::TODO, description, "-", "-"};
    json j = openJson(file);
    j["tasks"] += task;
    updateJSONFile(file, j);
    updateGlobalId(id + 1, id_path);
}

void updateTask(int id, const std::string &description, const std::string &file)
{
    json j = openJson(file);
    auto it = j["tasks"].begin();
    for (; it != j["tasks"].end(); ++it)
    {
        if (it.value()["id"].get<std::int64_t>() == id)
        {
            it.value()["description"] = description;
            updateJSONFile(file, j);
            return;
        }
    }
}

void deleteTask(int id, const std::string &file)
{
    json j = openJson(file);
    auto it = j["tasks"].begin();
    for (; it != j["tasks"].end(); ++it)
    {
        if (it.value()["id"].get<std::int64_t>() == id)
        {
            j["tasks"].erase(it);
            updateJSONFile(file, j);
            return;
        }
    }
}

void listTasks(const std::string &file, const std::string &status = "")
{
    const json j = openJson(file);
    for (const auto &task : j["tasks"].items())
    {
        if (equal(status, "") || equal(status, task.value()["status"]))
        {
            std::cout << "Task #" << task.value()["id"] << ":\n\t"
                      << task.value()["description"] << "\n\t"
                      << "status: " << task.value()["status"] << '\n';
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
            updateTask(std::stoi(argv[2]), (argc < 4 ? "" : argv[3]), file);
    }
    else if (equal(op, "delete"))
    {
        if (argc < 3) // didn't provide any id
            displayHelpInfo("delete");
        else
            deleteTask(std::stoi(argv[2]), file);
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
        // TODO
    }
    else if (equal(op, "mark-done"))
    {
        // TODO
    }
    else if (equal(op, "help"))
    {
        if (argc < 3) // didn't provide specific command
            displayHelpInfo();
        else
            displayHelpInfo(argv[2]);
    }

    return 0;
}