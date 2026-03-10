#include "utility.hpp"

#include <fstream>

json openJSON(const std::string &path)
{
    std::fstream f(path);
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