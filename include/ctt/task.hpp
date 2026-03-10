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

        void addNewTask(const std::string &description, const std::string &file, const std::string &id_path);

        void updateTask(int id, const std::string &description, const std::string &file);

        void markTaskStatus(int id, ctt::task::Status status, const std::string &file);

        void deleteTask(int id, const std::string &file);

        void listTasks(const std::string &file, const std::string &status = "");

    } // namespace task
} // namespace ctt

#endif // TASK_HPP