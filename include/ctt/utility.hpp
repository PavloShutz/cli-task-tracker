#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <chrono>
#include <format>
#include <string>

#define JSON_HAS_CPP_20 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

inline std::string getCurrentUTCTimePoint()
{
    return std::format("{0:%F} {0:%H-%M-%OS}", std::chrono::utc_clock::now());
}

inline int64_t getIDFromUserInput(const char *input)
{
    return static_cast<int64_t>(std::stoi(input));
}

// JSON helper functions
json openJSON(const std::string &path);
void updateJSONFile(const std::string &file, const json &j);

int64_t loadGlobalId(const std::string &path);
void updateGlobalId(int id, const std::string &path);

#endif // UTILITY_HPP