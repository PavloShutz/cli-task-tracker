#include "ctt/task.hpp"

#include <iostream>

namespace ctt
{
    namespace task
    {
        using namespace ctt::utility;

        template <typename F>
        void modifyTask(std::int64_t id, F func)
        {
            json j = openJSON();
            auto it = j["tasks"].begin();
            for (; it != j["tasks"].end(); ++it)
            {
                if (it.value()["id"].get<std::int64_t>() == id)
                {
                    func(j, it);
                    updateJSON(j);
                    return;
                }
            }
        }

        void addNewTask(const std::string &description)
        {
            const std::int64_t id = loadGlobalId();
            const std::string createdAt = getCurrentUTCTimePoint();
            const Task task{id, Status::Todo, description, createdAt, createdAt};
            json j = openJSON();
            j["tasks"] += task;
            updateJSON(j);
            updateGlobalId(id + 1);
            std::cout << std::format("Added new task (ID: {})", id);
        }

        void updateTask(std::int64_t id, const std::string &description)
        {
            auto func = [description](auto &j, auto it)
            {
                it.value()["description"] = description;
                it.value()["updatedAt"] = getCurrentUTCTimePoint();
            };
            modifyTask(id, func);
        }

        void markTaskStatus(std::int64_t id, Status status)
        {
            auto func = [status](auto &j, auto it)
            {
                it.value()["status"] = status;
                it.value()["updatedAt"] = getCurrentUTCTimePoint();
            };
            modifyTask(id, func);
        }

        void deleteTask(std::int64_t id)
        {
            auto func = [](auto &j, auto it)
            {
                j["tasks"].erase(it);
            };
            modifyTask(id, func);
        }

        void listTasks(const std::string &status)
        {
            const json j = openJSON();
            for (const auto &task : j["tasks"].items())
            {
                const auto &value = task.value();
                if ((status == "") || (status == value["status"].get<std::string>()))
                {
                    std::cout << std::format("Task #{}:\n\t{}\n\tstatus:{}\n\tcreated:{}\n\tlast updated:{}\n",
                                             value["id"].get<int64_t>(),
                                             value["description"].get<std::string>(),
                                             value["status"].get<std::string>(),
                                             value["createdAt"].get<std::string>(),
                                             value["updatedAt"].get<std::string>());
                }
            }
        }
    } // namespace task
} // namespace ctt
