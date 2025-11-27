SAPID: 590023457
# Bank System (C Project)

Simple command-line bank account management system written in C.

## Project structure

- `src/` – C source files (`main.c`, `account_operations.c`, `file_operations.c`, `utils.c`).
- `include/` – Header files (`account_operations.h`, `file_operations.h`, `utils.h`).
- `data/` – Data files used by the program (accounts, records).
- `assets/`, `docs/` – Optional assets and documentation.
- `sample_input.txt` – Example input file to try with the program.

## Build

From the repository root run (macOS / zsh):

```bash
gcc src/*.c -I include -o bank_system
```

This compiles all source files and produces the `bank_system` executable.

## Run

Run the program directly:

```bash
./bank_system
```

Or provide the sample input file as stdin:

```bash
./bank_system < sample_input.txt
```

## Notes

- The code uses plain C and standard library functions. Adjust compiler flags as needed (e.g., `-Wall -Wextra -std=c11`).
- If compilation fails, ensure the `include/` headers are present and `src/` files are not missing.

## Contributing / Next steps

- Add a `Makefile` for easier building.
- Add testing instructions or unit tests.
- Expand documentation in `docs/`.

---

Created on 25 Nov 2025.
# c-project
