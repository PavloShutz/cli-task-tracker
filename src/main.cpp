#include <fstream>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace tr
{
    static int g_id = 0;

    enum class Status
    {
        TODO,
        IN_PROGRESS,
        DONE
    };

    struct Task
    {
        int id;
        Status status;
        std::string description;
        std::string createdAt; // yyyy-mm-dd hh:mm:ss
        std::string updatedAt; // yyyy-mm-dd hh:mm:ss
    };

    void to_json(json &j, const Task &task)
    {
        j = json{
            {"id", task.id},
            {"status", task.status},
            {"description", task.description},
            {"createdAt", task.createdAt},
            {"updatedAt", task.updatedAt}};
    }

    void from_json(const json &j, Task &task)
    {
        j.at("id").get_to(task.id);
        j.at("status").get_to(task.status);
        j.at("description").get_to(task.description);
        j.at("createdAt").get_to(task.createdAt);
        j.at("updatedAt").get_to(task.updatedAt);
    }
} // namespace tr

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
    }
    return j;
}

void displayHelpInfo()
{
    // TODO: Output descriptive help man-like page
    std::cout << "Help command";
}

int main(int argc, char *argv[])
{
    // Parse CLI commands
    if (argc < 2)
    {
        displayHelpInfo();
    }
    else
    {
        json j = openJson("test.json");
    }
    return 0;
}