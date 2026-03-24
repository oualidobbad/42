# 42

Meta repository and solution archive for the 42 cursus, organized by difficulty level with exercises spanning C fundamentals, system programming, and algorithmic problem-solving.

## Project Overview
- What it does: collects exercises, personal solutions, and study notes from the 42 common core and piscine.
- Structure: subdivided into `Level_1/` (early exercises — string manipulation, memory basics), `Level_2/` (intermediate — deeper system-level work), and `mysolution/` (alternate implementations).
- Purpose: quick reference during peer evaluations, revision before exams, and a personal knowledge base.

## Architecture & Design
- `Level_1/`: piscine-style C drills — character tests, string operations, basic I/O, and simple Makefile builds.
- `Level_2/`: more advanced exercises touching file descriptors, process control, and data structure basics.
- `mysolution/`: standalone helper scripts and alternate implementations for comparison.
- Each subfolder is self-contained with its own source files and (where applicable) a Makefile.

## Core Concepts
- Progressive difficulty: exercises build on each other, reinforcing memory management, pointer arithmetic, and POSIX conventions.
- Norm compliance: all C code follows the 42 coding standard (no `for` loops, 25-line function limit, etc.).

## Usage Guide
- Browse by level; compile individual exercises with `make` or `cc -Wall -Wextra -Werror file.c`.
- Reference solutions during peer evaluations; do **not** submit directly (school policy).

## Technical Notes
- All code targets C99 with strict compiler flags (`-Wall -Wextra -Werror`).
- No external dependencies beyond POSIX libc.

## Improvements & Future Work
- Add a top-level index mapping exercises to 42 project names.
- Include unit tests per exercise for quick regression checks.

## Author
Oualid Obbad (@oualidobbad)