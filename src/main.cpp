#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace ctt
{
    enum class Status
    {
        TODO,
        IN_PROGRESS,
        DONE
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(Status, {{Status::TODO, "todo"},
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

void displayHelpInfo()
{
    // TODO: Output descriptive help man-like page
    std::cout << "Help command";
}

void displayHelpInfo_Add()
{
    std::cout << "Usage: task-cli add <description>\n\n";
    std::cout << "Options: \n";
    std::cout << "  " << std::left << std::setw(30) << "<description>"
              << "= A description of the task.\n";
}

void displayHelpInfo(const char *command)
{
    if (equal(command, "add"))
    {
        displayHelpInfo_Add();
    }
}

void addNewTask(int id, const std::string &description, const std::string &file)
{
    const ctt::Task task{id, ctt::Status::TODO, description, "-", "-"};
    json j = openJson(file);
    j["tasks"] += task;
    std::ofstream ofs(file, std::ios::in);
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
    std::ofstream ofs(path, std::ios::out);
    ofs << id;
}

int main(int argc, char *argv[])
{
    // Parse CLI commands
    if (argc < 2 || equal(argv[1], "help"))
    {
        displayHelpInfo();
        return 0;
    }

    const std::string op = argv[1];
    const std::string file = "test.json";
    const std::string id_path = "id.txt";

    if (equal(op, "add"))
    {
        // TODO: properly track time stamps
        if (argc < 3) // didn't provide any description
        {
            displayHelpInfo("add");
            return 0;
        }
        const int id = loadGlobalId(id_path);
        addNewTask(id, argv[2], file);
        updateGlobalId(id + 1, id_path);
    }
    else if (equal(op, "update"))
    {
        // TODO
    }
    else if (equal(op, "delete"))
    {
        // TODO
    }
    else if (equal(op, "list"))
    {
        // TODO
    }
    else if (equal(op, "mark-in-progress"))
    {
        // TODO
    }
    else if (equal(op, "mark-done"))
    {
        // TODO
    }

    return 0;
}