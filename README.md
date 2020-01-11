# Linear system solver
This project focuses on solving systems of linear equations. Program offers interactive interface. 
User can either choose from which file the linear system should be read or he can enter the linear system 
himself through command line. The linear system should be given as augmented matrix. 
Program output looks like one of following options:
 1. vector of the solution,
 2. particular solution and basis of the null linear space or
 3. information that given linear system has no solution

## Usage
### Compilation
The application was created with usage of the JetBrains CLion IDE. It is preferred that you use this IDE 
for the build of the application.

If you decide to run the program from the command line or other IDE, please make sure that the input folder 
is two levels above the main executable of the application. For `matrix.txt`, the route 
from `linear-system-solver.exe` would be `../inputs/matrix.txt`.

The input files should be in format `.txt` and their content should be also properly formatted. 
For matrix:

```
 1  2  1  1  1 | -4
-1 -2 -2  2  1 |  9
 2  4  3 -1  0 | -13
 1  2  2 -2 -1 | -9
```

the file should look like:

```
 6  4
 1  2  1  1  1 -4
-1 -2 -2  2  1  9
 2  4  3 -1  0 -13
 1  2  2 -2 -1 -9
```

The first line holds two space separated numbers, first for width of the matrix, second for height of the matrix. 
Each other line represents row of the matrix. **The values are space separated.** 
Values don't have to be integers, doubles can be written with decimal point as `2.5` for example.

>The format rules for text files apply also for the command prompt input feature. When using that feature, 
>program gives user a little help. However, you should remember that values should be space separated.

The main function can be found in the `main.cpp` file, compilation configuration is set in `CMakeLists.txt` file.

### Run
When you run the compiled program, it should print all of the available commands. 
The commands are shown also in the table below.

| Command | Description |
| :-----: | ----------- |
| **h** | shows help |
| **q** | shuts down the program |
| **thd1** | sets app to use one thread for computation |
| **thd2** | sets app to use multiple threads for computation |
| **cmd** | selects input from command line |
| **txt** | selects input from text file |

Note that the program won't end until you tell it by entering the command `q` for quit.

## Multithreading
The program includes two implementations of finding the solution of the given system of linear equations. 
The first one is using only one thread, whereas the other is using multiple threads.

The computation part of the program also measures time needed for finding the solution. Hence you can compare the 
one- and multi-threaded implementation.

The multithreaded implementation is more effective when the solution 
requires counting of linear space with large dimension. Each vector of the space's basis is computed in 
different thread, so the computation is faster. However, with not that complex solution 
one can't see that much of a difference between the two implementations.

The test data were meant to be real and thus not that much complex. 
On Acer Aspire V15 Nitro, with Intel Core i7 two-core 2.6 GHz processor both implementations 
needed less than 1 ms to finish.

## Code structure
Documentation of the main program features can be found directly in the `.hpp` files. 
Functions and methods are commented with Doxygen comments. 
You can also find brief description of the parts of the program in the list below.

 - `main.cpp` - contains the main function of the program
 - `command.hpp` - contains all logic associated with commands and their processing, implemented in `command.cpp`
 - `matrix.hpp` - contains the struct representing matrices in the program, also contains logic for parsing 
 the matrices from text files or command prompt, implemented in `matrix.cpp`
 - `system_solver.hpp` - contains all the logic associated with solving the system of linear equations, 
 implemented in `system_solver.cpp`
 - `utils.hpp` - contains other useful functionality such as reading files etc., implemented in `utils.cpp`
 
 ---
 
 *Written for commit 219c37171768d1d415b1d85da434a7b91eb8590e.*