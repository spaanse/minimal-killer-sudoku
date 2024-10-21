# 6×6 Minimal killer sudoku searcher

The code in this repository searches for 6×6 killer sudoku where the cages cover a minimum number of cells.
Using this search, the following facts have been proven:

- there are no 8-cell killer sudoku puzzles with a unique solution
- there are no 3-cage 9-cell killer sudoku puzzles with a unique solution
- there are exactly six[^1] 9-cell killer sudoku puzzles, all with the same cage configuration.

[^1]: Up to permuting rows and columns
## The minimal killers:
The six minimal killers all have the same cages.
They only differ in the cage sums, and their solutions are the same up to permuting digits.
The cage sums are found by Vorados and Philip Newman.
They are:
- 3 / 7 / 11 / 8 (in the image)
- 4 / 6 / 11 / 9
- 4 / 6 / 10 / 9
- 11 / 14 / 6 / 3
- 10 / 15 / 3 / 5
- 10 / 15 / 4 / 5

![[6x6-minimal-killer.png]]
[SudokuPad](https://sudokupad.app/fpuzN4IgzglgXgpiBcA2ANCALhNAbO8QFkIA7CAWwEMsACRAdcSoGkIscAnKgZQFcATAewDW3EKnLc0AC35sEITgAdy5ImBhUAZFQBqM8gLCiQbbjjVo5AORkVqYPkO5UTZquQUKsATwB0AHSJmVhg2eCoAEQgAc0wwKmIqAGNyKJg45KIifjRnGAUYchyVXipSbjAc+1IqNH4ayXVatEoqGIA3GCIfIyi2CF4EAG1B4ABfZDGJ8cmZ0YBdZBHp5anVsYWltZXZjdmtrd3to6nD/b31hZBBFnZk1KHQRJhWQ3hBkAAlAEYAYQBmIwfABM/xAlzalG4uBAAOmICeLyGnxBABZAX9QagPhi0eDIdCAOwgOEIrCvd4fFE/L6AgCs1LBqAhWChci+NJJzzJSMpP1pdL5jJAzNZeAAHMTLmB+CyMPwiEi0ah+aggUZEEYaagAdr1ZqjGrUEqQCqQIaYUZjVqTXrUBrUNbTTqzZajKbzc7jfaQNbrV63UZnWq5qMgA)

## The code
There are four files in this repository:

| File                     | Purpose                                                                                                                                                                                |
| ------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `6x6-killer.cpp`         | Generating configurations of 4 domino cages                                                                                                                                            |
| `6x6-killer-general.cpp` | Same as `6x6-killer.cpp` but generalised to any cage sizes and number of cells covered                                                                                                 |
| `6x6-solutions.cpp`      | Recursive solver to generate all solutions for 6×6 sudoku<br>Up to relabeling digits by ensuring the first row is 0, 1, 2, ..., 5                                                      |
| `6x6-killer-solver.cpp`  | Filters cage configurations based on whether there are multiple solutions with the same digits in the cages. Does not take cage sums into account, instead digits are purely symbolic. |
To replicate the results, follow the following steps:
- generate all solutions up to relabelling by compiling and running `6x6-solutions.cpp` and writing the result to a file called `6x6-solutions.txt`
- generate all cage configurations by compiling and running `6x6-killer-genral.cpp` and writing the result to a file called `6x6-26-89-configurations.txt`
- filter these configurations by compiling and running `6x6-killer-solver.cpp`
## Configuration

At the top of `6x6-killer-general.cpp` there are some constants

| name          | function                                                       |
| ------------- | -------------------------------------------------------------- |
| p             | Height of boxes, used to determine sudoku size                 |
| q             | Width of boxes, used to determine sudoku size                  |
| N             | Size of sudoku                                                 |
| min_cell      | The minimum number of cells covered by the cage configurations |
| max_cell      | The maximum number of cells covered by the cage configurations |
| max_cages     | The maximum number of cages to use in a configuration          |
| min_cage_size | The minimum size of a cage                                     |
| max_cage_size | The maximum size of a cage                                     |
## Cage configuration format

The program prints cage configurations in a particular format.
Each configuration is printed on a single line, for example:
```
2 8 | 9 14 15 | 18 24 | 22 28
```
In this case there are four cages, separated by pipes (`|`).
Each cage lists the cells belonging to that cage.
These are numbered in reading order starting with `0` in the top-left to `35` in the bottom-right.
This example corresponds to the cages of the minimal killer above

## License
<p xmlns:cc="http://creativecommons.org/ns#" >This work is licensed under <a href="https://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-SA 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" alt=""></a></p>
