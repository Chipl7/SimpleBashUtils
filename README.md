# SimpleBashUtils

The project is an implementation of the cat and grep commands in the C programming language. The build is done using Makefile. The project is written for MacOS, the end-of-line character sequences are LF.

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

3. Cat dir

```bash
  cd src/cat
```
4. Grep dir

```bash
  cd src/grep
```
5. Run make for build

```bash
  make gcc
```

6. Run test

```bash
  make test
```