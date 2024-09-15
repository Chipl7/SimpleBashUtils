# SimpleBashUtils

Проект предстявляет из себя реализацию команд cat и grep на языке программирования C.

## Cat

TEMPLATE: `cat [OPTION] [FILE]`

| № |                               Options                          |                 Description                  |
|---|----------------------------------------------------------------|----------------------------------------------|
| 1 | -b (GNU: --number-nonblank)                                    | numbers only non-empty lines                 |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $ |
| 3 | -n (GNU: --number)                                             | number all output lines                      |
| 4 | -s (GNU: --squeeze-blank)                                      | squeeze multiple adjacent blank lines        |
| 5 | -t implies -v (GNU: -T the same, but without implying -v)      | but also display tabs as ^I                  |

## Grep

TEMPLATE: `grep [OPTION] [TEMPLATE] [FILE]`

| № | Options |                           Description                          |
|---|---------|----------------------------------------------------------------|
| 1 | -e      | pattern                                                        |
| 2 | -i      | Ignore uppercase vs. lowercase.                                |
| 3 | -v      | Invert match.                                                  |
| 4 | -c      | Output count of matching lines only.                           |
| 5 | -l      | Output matching files only.                                    |
| 6 | -n      | Precede each matching line with a line number.                 |
| 7 | -h      | Output matching lines without preceding them by file names.    |
| 8 | -s      | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file.                                      |
| 10| -o      | Output the matched parts of a matching line.                   |

## Run Locally

1. Clone the project

```bash
  git clone https://github.com/Chipl7/SimpleBashUtils.git
```

2. Go to the project directory

```bash
  cd SimpleBashUtils
```

3. Go to the cat or grep folder

```bash
  cd src/cat
  cd src/grep
```

4. Run make for build

```bash
  make gcc
```

5. Run test

```bash
  make test
```

6. Clean project

```bash
  make clean
```

7. Google Style Check

```bash
  make clang_check
```

8. Google Style Format

```bash
  make clang_format
```