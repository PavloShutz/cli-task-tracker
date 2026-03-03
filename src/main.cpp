#include <cstring>
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

enum class Action
{
    NONE,
    ADD
};

void displayHelpInfo()
{
    // TODO: Output descriptive help man-like page
    std::cout << "Help command";
}

inline bool equal(const char *str1, const char *str2)
{
    return std::strcmp(str1, str2) == 0;
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
        Action action = Action::NONE;
        for (int ndx{}; ndx != argc; ++ndx)
        {
            if (equal(argv[ndx], "add") && action == Action::NONE)
            {
                action = Action::ADD;
                continue;
            }
            if (action == Action::ADD)
            {
                // create new task
                // TODO: properly track time stamps
                // TODO: load from and save to file the value of global id
                tr::Task task{tr::g_id++, tr::Status::TODO, argv[ndx], "-", "-"};
                json t = task;
                std::cout << t << std::endl;
                action = Action::NONE;
            }
        }
    }
    return 0;
}