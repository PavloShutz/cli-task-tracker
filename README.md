# cli-task-tracker (ctt)
A lightweight, non-overwhelming command-line task tracker written in C++23.

![Demonstration](images/record.gif)

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
    - [CMake](#cmake)
    - [Download binaries](#download-binaries)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing & Support](#contributing--support)

## Overview
`ctt` (cli-task-tracker) strives to provide a simple and intuitive interface, while being not so overwhelming and scary 👻 to explore. Tasks are stored locally in a JSON file, so there is no database setup, no accounts, and no internet connection required — just a single executable.

It was implemented as a [Task Tracker](https://roadmap.sh/projects/task-tracker) pet-project, following the roadmap.sh project guidelines.

## Features
Tasks are persisted in a local JSON file powered by the [nlohmann/json](https://json.nlohmann.me/) library[^1].

[^1]: https://json.nlohmann.me/

Here are the features given at your disposal:

- **Add** a new task with a short description
- **Update** the description of an existing task by its ID
- **Delete** a task that is no longer needed
- **Mark** tasks as `in-progress` or `done` to track your progress
- **List** all tasks at once, or filter them by their status (`todo` / `in-progress` / `done`)
- **Built-in help** — run `task-cli help` or `task-cli help <command>` for instant usage reference

## Installation
### CMake
You can build the binary from source using [CMake](https://cmake.org/) (version 3.31.3 or later) and a C++23-capable compiler:

```cmd
> git clone https://github.com/PavloShutz/cli-task-tracker.git
> cd cli-task-tracker
> cmake -B build
...
> cmake --build build
```

After a successful build, the `task-cli` executable will be placed inside the `build/` directory.

### Download binaries
If you prefer not to compile from source, head over to the [Releases](https://github.com/PavloShutz/cli-task-tracker/releases) tab and download the pre-built executable for your platform.

## Usage
After obtaining the executable (either by building or downloading), you can run it directly from its directory, or make it available system-wide:

- **Windows** — add the folder that contains `task-cli.exe` to your `PATH` environment variable.
- **Linux / macOS** — move (or symlink) the binary to a directory that is already on your `PATH`, such as `/usr/local/bin`:

```bash
sudo mv build/task-cli /usr/local/bin/task-cli
```

Once `task-cli` is on your `PATH`, every new terminal session can call it by name. Run `task-cli` (with no arguments) or `task-cli help` at any time to see the full list of available commands.

## Examples
The walkthrough below shows the most common workflow: adding tasks, updating them, tracking their progress, and finally cleaning them up.

```cmd
# Show the built-in help overview
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

# Get detailed help for a specific command
D:\>task-cli help add
Usage: task-cli add <description>

Options:
  <description>                 = A description of the task.

D:\>task-cli help update
Usage: task-cli update <id> <description>

Options:
  <id>                          = The ID of the task to update.
  <description>                 = A new description for the task.

# Add a couple of tasks
D:\>task-cli add "Buy groceries"

D:\>task-cli add "Read a book"

D:\>task-cli add "Go for a morning run"

# List all tasks — they all start with status "todo"
D:\>task-cli list
Task #0:
        "Buy groceries"
        status: "todo"
Task #1:
        "Read a book"
        status: "todo"
Task #2:
        "Go for a morning run"
        status: "todo"

# Update a task's description
D:\>task-cli update 1 "Read Clean Code by Robert C. Martin"

# Start working on a task
D:\>task-cli mark-in-progress 2

# List only the tasks that are currently in progress
D:\>task-cli list in-progress
Task #2:
        "Go for a morning run"
        status: "in-progress"

# Mark a task as done
D:\>task-cli mark-done 0

# List only completed tasks
D:\>task-cli list done
Task #0:
        "Buy groceries"
        status: "done"

# Delete a task that is no longer relevant
D:\>task-cli delete 0

# All remaining tasks after the deletion
D:\>task-cli list
Task #1:
        "Read Clean Code by Robert C. Martin"
        status: "todo"
Task #2:
        "Go for a morning run"
        status: "in-progress"

D:\>
```

## Contributing & Support

Contributions of all kinds are warmly welcome! Whether it's a bug report, a feature suggestion, a documentation improvement, or a pull request — every bit of help makes this project better.

**How to contribute:**
1. Fork the repository and create your branch from `main`.
2. Make your changes, then open a pull request with a clear description of what you changed and why.
3. For larger changes, consider opening an issue first to discuss your idea.

**Found a bug or have an idea?** Open an [issue](https://github.com/PavloShutz/cli-task-tracker/issues) — feedback is always appreciated.

If you find `ctt` useful, please consider giving the repository a ⭐ **star** on GitHub. It helps others discover the project and motivates further development. Thank you! 🙏
