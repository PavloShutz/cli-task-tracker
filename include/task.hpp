#include <string>

#include "utility.hpp"

namespace ctt
{
    namespace task
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
    } // namespace task
} // namespace ctt
