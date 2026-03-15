#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <charconv>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>

#define JSON_HAS_CPP_20 1
#include <nlohmann/json.hpp>

namespace ctt
{
    namespace utility
    {
        using json = nlohmann::json;

        constexpr std::string_view file_path = "tasks.json";
        constexpr std::string_view id_path = "id.txt";

        inline std::string getCurrentUTCTimePoint()
        {
            return std::format("{0:%F} {0:%H-%M-%OS}", std::chrono::utc_clock::now());
        }

        inline std::int64_t getIDFromUserInput(const char *input)
        {
            std::int64_t value = 0;
            if (std::from_chars(input, input + std::strlen(input), value).ec != std::errc())
            {
                throw std::runtime_error{"Couldn't interpret " + std::string(input) + " as a valid numeric id."};
            }
            return value;
        }

        // JSON helper functions
        json openJSON();
        void updateJSON(const json &j);

        std::int64_t loadGlobalId();
        void updateGlobalId(std::int64_t id);
    } // namespace utility
} // namespace ctt

#endif // UTILITY_HPP