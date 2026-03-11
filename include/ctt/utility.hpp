#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <chrono>
#include <format>
#include <string>
#include <string_view>

#define JSON_HAS_CPP_20 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

constexpr std::string_view file_path = "tasks.json";
constexpr std::string_view id_path = "id.txt";

inline std::string getCurrentUTCTimePoint()
{
    return std::format("{0:%F} {0:%H-%M-%OS}", std::chrono::utc_clock::now());
}

inline int64_t getIDFromUserInput(const char *input)
{
    return static_cast<int64_t>(std::stoi(input));
}

// JSON helper functions
json openJSON();
void updateJSON(const json &j);

int64_t loadGlobalId();
void updateGlobalId(int id);

#endif // UTILITY_HPP