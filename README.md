# cli-task-tracker (ctt)
Command line task tracker

![Demonstration](images/record.gif)

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
    - [CMake](#cmake)
    - [Download binaries](#download-binaries)
- [Usage](#usage)
- [Examples](#examples)

## Overview
ctt strives to provide simple and intuitive interface to use, at the same time being not so overwhelming and scary 👻 to explore. It was implemeneted as a [Task Tracker](https://roadmap.sh/projects/task-tracker) pet-project.

## Features
JSON support is being brought by the nlochman's library[^1].

[^1]: https://json.nlohmann.me/

Here are the features given at your disposal:

- add new task
- update/delete existing tasks
- mark the existing tasks as `in-progress`/`done`
- list all existing tasks or filter them by their status (`todo`/`in-progress`/`done`)
- use `help` command for reference

## Installation
### CMake
You can build binaries from source using [CMake](https://cmake.org/):
```cmd
> git clone https://github.com/PavloShutz/cli-task-tracker.git
> cd cli-task-tracker
> cmake -B build
...
> cmake --build build
```
### Download binaries
You can also check the Releases tab to download executable.

## Usage
To make `task-cli` command available system-wide, add the folder where the executable is located to the `PATH` variable.    

## Examples
```cmd
D:\>task-cli
task-cli - A simple non-overwhelming command-line task tracker

Usage: task-cli <command> [arguments...]

Commands:
  add <description>             Add a new task.
  update <id> <description>     Update a task's description.
  delete <id>                   Delete a task.
  list [status]                 List tasks, optionally filtered by status.
  mark-in-progress <id>         Mark a task as in-progress.
  mark-done <id>                Mark a task as done.
  help [command]                Show help for a specific command.

D:\>task-cli help add
Usage: task-cli add <description>

Options:
  <description>                 = A description of the task.

D:\>task-cli add "hello, world"

D:\>task-cli add "another world"

D:\>task-cli list
Task #0:
        "hello, world"
        status: "todo"
Task #1:
        "another world"
        status: "todo"

D:\>task-cli update 1 "go for a walk"

D:\>task-cli mark-in-progress 1

D:\>task-cli list
Task #0:
        "hello, world"
        status: "todo"
Task #1:
        "go for a walk"
        status: "in-progress"

D:\>task-cli mark-done 1

D:\>task-cli list done
Task #1:
        "go for a walk"
        status: "done"

D:\>task-cli delete 1

D:\>task-cli list
Task #0:
        "hello, world"
        status: "todo"

D:\>
```
