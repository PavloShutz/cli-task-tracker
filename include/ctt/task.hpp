#ifndef TASK_HPP
#define TASK_HPP

#include <string>

#include "ctt/utility.hpp"

namespace ctt
{
    namespace task
    {
        enum class Status
        {
            Todo,
            In_Progress,
            Done,
            Invalid = -1
        };

        NLOHMANN_JSON_SERIALIZE_ENUM(Status, {{Status::Invalid, nullptr},
                                              {Status::Todo, "todo"},
                                              {Status::In_Progress, "in-progress"},
                                              {Status::Done, "done"}});

        struct Task
        {
            int64_t id;
            Status status;
            std::string description;
            std::string createdAt; // yyyy-mm-dd hh:mm:ss
            std::string updatedAt; // yyyy-mm-dd hh:mm:ss
        };

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Task, id, status, description, createdAt, updatedAt);

        void addNewTask(const std::string &description);

        void updateTask(int64_t id, const std::string &description);

        void markTaskStatus(int64_t id, ctt::task::Status status);

        void deleteTask(int64_t id);

        void listTasks(const std::string &status = "");

    } // namespace task
} // namespace ctt

#endif // TASK_HPP