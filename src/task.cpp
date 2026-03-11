#include "ctt/task.hpp"

#include <iostream>

using namespace ctt;

template <typename F>
void modifyTask(int id, const std::string &file, F func)
{
    json j = openJSON(file);
    auto it = j["tasks"].begin();
    for (; it != j["tasks"].end(); ++it)
    {
        if (it.value()["id"].get<std::int64_t>() == id)
        {
            func(j, it);
            updateJSONFile(file, j);
            return;
        }
    }
}

void task::addNewTask(const std::string &description, const std::string &file, const std::string &id_path)
{
    const int64_t id = loadGlobalId(id_path);
    const std::string createdAt = getCurrentUTCTimePoint();
    const Task task{id, Status::TODO, description, createdAt, createdAt};
    json j = openJSON(file);
    j["tasks"] += task;
    updateJSONFile(file, j);
    updateGlobalId(id + 1, id_path);
    std::cout << std::format("Added new task (ID: {})", id);
}

void task::updateTask(int id, const std::string &description, const std::string &file)
{
    auto func = [description](auto &j, auto it)
    {
        it.value()["description"] = description;
        it.value()["updatedAt"] = getCurrentUTCTimePoint();
    };
    modifyTask(id, file, func);
}

void task::markTaskStatus(int id, ctt::task::Status status, const std::string &file)
{
    auto func = [status](auto &j, auto it)
    {
        it.value()["status"] = status;
        it.value()["updatedAt"] = getCurrentUTCTimePoint();
    };
    modifyTask(id, file, func);
}

void task::deleteTask(int id, const std::string &file)
{
    auto func = [](auto &j, auto it)
    {
        j["tasks"].erase(it);
    };
    modifyTask(id, file, func);
}

void task::listTasks(const std::string &file, const std::string &status)
{
    const json j = openJSON(file);
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