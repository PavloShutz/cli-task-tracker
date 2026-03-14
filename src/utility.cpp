#include "ctt/utility.hpp"

#include <fstream>

json openJSON()
{
    std::fstream f{std::string(file_path)};
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

void updateJSON(const json &j)
{
    std::ofstream ofs{std::string(file_path), std::ios::out | std::ios::trunc};
    ofs << j.dump(2) << std::endl;
}

std::int64_t loadGlobalId()
{
    std::ifstream ifs{std::string(id_path), std::ios::in};
    if (!ifs.is_open())
        return 0;

    std::int64_t id = 0;
    ifs >> id;
    return id;
}

void updateGlobalId(std::int64_t id)
{
    std::ofstream ofs{std::string(id_path), std::ios::out | std::ios::trunc};
    ofs << id;
}