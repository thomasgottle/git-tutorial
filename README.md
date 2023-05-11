# Merge Conflicts

When merging two branches there are sometimes changes that Git cannot automatically resolve. Git prefers then to flag the conflict as something it cannot resolve instead of intervening and potentially causing even larger errors. Errors that require human intervention usually result from changes to the same file, for example two people modify the same line of a file. Git would then require the person merging the files to decide which one it should keep.

It is important to note that during a merge process if you choose the wrong line or mess up the merge you can revert the merge. Meaning you must only commit the merge once you are happy that everything has been merged properly. At any time you can use the `git reset --hard HEAD` command to reset your HEAD to the last commit before the merge (if you didn't pick up on what this is then read [this](http://www.gitguys.com/topics/head-where-are-we-where-were-we/)).

## Resolving a conflict

When there is a merge conflict Git will tell you that there is unmerged paths and it will give you a list of the files involved. This can be found using `git status`.

``` bash
Unmerged paths:
(use "git add <file>..." to mark resolution)

    both modified:   src/main.c
```

Inside each conflict file Git places markers that indicate the area of conflict. Let's take the simple example where two changes affected the same line of code in a file. This means that Git needs you to decide which change to keep. You will manually need to edit the code to integrate both solutions into your project. Choosing how to fix your code will be up to your discretion.

Now in this example I have branched my original code, then on the new branch **and** on my current branch created commits that modify the same line of code. On the current branch I added "Result:" to a `printf` statement while on the branch I added "Output:".

``` bash
Original code (shared commit) ------ + "Result:"
                              |----- + "Output:"
```
To see some much more involved macros that are used in the auto generation of data structures in a state machine, look [here](https://github.com/alxhoff/Application_Interfacing_Governor/blob/master/AI_gov_phases.c).

<<<<<<< HEAD
## Compilation

Now the compilation of code is only one step in the process of building a program. After each C file is run through the preprocessor, so that all the preprocessor directives have been handled, the completed C files must then compiled into assembly code. This is done using a compiler, such as the GNU C Compiler (GCC). The assembly code must then be made into machine code that is actually usable by the target device. This is done by the assembler, which creates machine code from the assembly code. By modifying these pieces of software, collectively called a toolchain, you can change how the code is compiled. Various toolchains are available for different hardware architectures, such that the compiled code is compiled with regards to how the code executes on the target architecture. Compiling for a different architecture, such as compiling on an x86 laptop for a ARM based micro-controller, is known as cross compiling.

The file produced by the assembler is a binary file, the formats can vary (ELF, a.out, ...) but the idea is the same. The binary files are called objects, each object file contains the compiled code and exposes the symbols contained within the binary code. Symbols are the addresses of the variables and functions contained within a binary, they can be thought of as the "API" to the object file. The addresses of all the symbols within an object file are stored within a symbol table.

At this point all of your source files have been compiled into separate objects which are unaware of each other. Function calls to functions found in other object files are at this point pointing to an unknown memory locations, in an unknown binary file. These calls are stored as references to undefined addresses which are to be resolved in the last step of building a program, linking. If the completed program binary is to be able to execute, each function call needs to know where the pointed to code actually resides in memory. This is done by the third step in building a program, linking. Common errors pop up along the lines of "undefined reference" when a symbol cannot be resolved, meaning that the linking step was not able to be completed.

I should also mention that libraries, with which you are hopefully familiar with, are simply object files that can be reused by multiple programs such that the same code is not rewritten and/or recompiled unnecessarily.

## Linking

So we know now that our program is compiled into a number of object files (binary blobs) we need to resolve all of the references to the symbols that are pointed to and found in other object files. As the name implies, linking is the process of linking these references to the actual memory addresses in the appropriate object files. Linking to files within the same source code chunk is usually not that error prone. Most errors come from having to link against static libraries or source code found else where on a system or in another project. Common errors will be those that complain of either missing definitions (cannot find appropriate symbols to link against) or duplicate errors (multiple objects exposing the same symbol).

# CMake

So now that I have outlined a bit for you what happens when building a program, we will go through and build a demo program by using a program called CMake. CMake just helps in automating the build process a little, while not abstracting the process so much that one looses touch with what is happening. Using your newly discovered Git skills we will piece together a basic project and get it compiled and linked. You may have to apply some Git trickery along the way to get all the pieces ;).

So now that you have an idea of what goes into building a C project lets see how you can accomplish this using CMake. If we open the CMake file in this branch you should see the following

``` bash                                                         
project(git_tutorial)                                                            
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)                                  

set(CMAKE_BUILD_TYPE Debug)                                                      
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)                   

include_directories(include)                                                     

file(GLOB SOURCES "src/*.c")                                                     

add_executable(foo ${SOURCES})    
```

Now the first few lines should be quite self-explanatory. On the fourth line we set the output directory for our binary. Meaning we will need to create a `bin` directory in our repo's root. Do this now. The fifth line is where we tell CMake which directories we want to use as include directories. In the directories here is where make will then look for files that you include using `#include`. This CMake line equates then to the `-I` make build option. Another good common practice is to separate your `.c` source files from your `.h` source files. As can be seen in the CMake, we use a folder called `include` for the header files and a folder called `src` for the source files. Create the `include` folder so it sits alongside the bin and build directories. Following this we can see the `file` command. The file command is a file manipulation command used to achieve lots of different things. In this case it is used with `GLOB`. Glob is used to generate a list of files given one or more globbing expressions, storing the results in a variable, in this case `SOURCES`. From the provided globbing expression we can see that in this case the file command generates a list of all `.c` files that can be found in the `src` folder. Since we do not have this you will also need to create it.

The final line in the CMake lets CMake know that an executable should be built from the provided source files, in this case those stored in the `SOURCES` variable. This will also perform the required linking should there be more than one source file found, as there are going to be no object files external to our source files' directory.

Now we are almost there. We have the folder structure set up for our project but we are missing some code! We want to merge the new folder structures that we created back to our merging branch. The problem is that Git only tracks the contents of a folder and not folders themselves. As all of our folders are empty they would not be able to be tracked, commited and then merged to our `merging` branch. A convention of Git to keep Git directories that are empty are to add a `.gitkeep` file to them. This is a hack way of creating a reason for Git to track the folder. In this case we are in need of this folder structure for CMake and as such it is important that Git is able to track our folders. Let's touch a `.gitkeep` into each folder that is empty. `man touch` should help you understand what touching does.

Checking the status of your repo you should now see that you can track your empty `src`, `bin` and `include` directories as they all have `.gitkeep` files in them. Add and commit your folders with a meaningful commit message and then checkout your merging branch and merge the folders to your `merging` branch. Come back to this branch (`compiling`) when you have done that.

## Coding Challenge I

Now we are in need of the most the most fundamental of fundamentals to compile our project, a main function. As we will consider the main function a new "feature" that you are to add to your project you must perform the following steps:

 * Checkout a new branch to implement your features, branching from this branch.
 * Write a main function in an appropriate file in your project, that is to output "Hello ESPL" to the terminal.
 * Add, commit and PUSH the work you have done to the origin remote.
 * Merge the changes back to `merging`, pushing the result.
 * Come back to this branch to continue with the instructions below.

Now you should have at least one source file and be able to rerun your CMake command to generate the required make files for your project. If all went well in your build folder you should now see a Makefile that was generated from CMake. To then build your project you need to run the command `make` from within your build directory. If all went well you should now find a built binary in your bin directory with the same name as the executable specified in you `CMakeLists.txt`.

Navigate to your bin directory and execute the binary by using the `./` Linux convention. You should be greeted with "Hello ESPL".

Now we know roughly how to navigate around a Git repo, create, add and commit files as well as build a basic C project with an idea of what is happening behind the scenes. Before we look into the more advanced CMake features, such as linking libraries, you should merge your current project to master as it is now in a stable state. Binary files should not be included in your commits and should be left untracked. Modify your repository accordingly such the the binaries can never be accidentally added. Once that is done you will need to go to the `exercise` branch where you will need to use the Git logs, merging and the `git cherry-pick` command to get your exercise requirements and the library code. Useful articles can be found [here](https://www.git-tower.com/learn/git/faq/detached-head-when-checkout-commit) and [here](https://www.hacksparrow.com/how-to-merge-a-specific-commit-in-git.html) to explain the process.

One commit will contain the necessary `.h` and `.c` files for a static library that we will build called `espl_lib`. Another commit will contain a `.patch` for your CMake script to link the library. Checkout the commits, find the files, verify their contents and then use cherry pick to merge them to your merging branch. The instructions (in a separate `.md` file) to continue can also be found in a seperate commit.
=======
This has caused a merge conflict as the commit which they both share now has two different diffs when compared with the HEAD of both branches.

Looking into the file `src/main.c`, as shown by `git status`, we would see the following around the line of interest.

``` C
<<<<<<< HEAD
        printf("Result: %s", tmp);
=======
        printf("Output: %s", tmp);
>>>>>>> bar
```

This tells use that on our current branch (our current HEAD) the line containing "Result", where as on the branch we wish to merge into our current branch (bar) the line contains "Output". Git does not know which one we wish to use and as such we must decide. Let's say that we wish the have the line contain output and not result, then we must manually delete the markers from Git as well as the line. Using our new patch knowledge we can see the what needs to be done below.

``` bash
--- src/main.c  2019-03-20 11:47:22.947753390 +0100
+++ src/main.c  2019-03-20 11:47:34.777753931 +0100
@@ -8,11 +8,7 @@
    char *tmp = NULL;
    tmp = num_to_words(123);
    if (tmp)
-<<<<<<< HEAD
-        printf("Result: %s", tmp);
-=======
         printf("Output: %s", tmp);
->>>>>>> bar
    else
         return 1;
    return 0;
```

Once you have resolved the merge conflict you can then add the resolved file and finalize the merge with a normal commit. The commit message should summarize the changes during the merge.

# Coding Challenge III

Now that you has seen the basic ideas of how merging works, lets see if you can handle some more complex merge problem yourself. You will find a branch called `unknown_features` which has diverged from this current branch at the previous commit. Meaning that the HEAD of this branch and `unknown_features` have a shared previous commit....conflicts are looking likely!

Your job now is to merge `unknown_features` branch into this current branch and resolve the conflicts that appear (find files affected using `git status`). You will need to apply you C knowledge and CMake knowledge to merge the files correctly to get the project building properly. Please note that there are other tricks and errors hidden in the code. The code should not compile with warnings, as warnings should almost always be treated as errors. Warnings will be cause for deducted marks throughout this course.

The program you are building is a POSIX thread (`pthread`) based state machine that counts, using random intermediate values, to a number specified in the programs options. See the `--help` of the compiled binary to see how to use the program. An example usage of the program that counts up to the value 2 would be

``` bash
./state_machine 2
```

If the code has been compiled sucessfully the output should be something similar to

``` bash
Count until = 2
Verbose = no
Tick = 100ms
State 0 probed
State 1 probed
State 2 probed

### Starting State Machine ###

Count up once
Total count: 1
In state 1, state count: 1
---------
Count down once
Total count: 0
In state 3, state count: -1
---------
Entering 2
Count up twice
Total count: 2
In state 2, state count: 2
---------
Finshed
```

Once your binary performs this then you have the project merged and building correctly. Merge the project into `merging` and finally into `master`, if both projects are stable and working as expected. This code should replace the code that it in master from the 2nd coding challenge. Finally create another tag with the annotation "Coding Challenge 3".

If all of that is done then you have completed this tutorial. Please be wary that the use of Git is a requirement in this course and will be part of the project's assessment. Inform yourself on proper use of Git commit messages and make sure that you and your team partner establish a Git workflow that you will use throughout the course. A fun tool to use to make sure your workflow has been used properly is `git log --graph --all` which will give you a graphical representation of your repo's logs.

# Future Reading

There are a number of other features in Git that are useful to know. If you are motivated then I would recommend reading up on these features so that during semester you are able to overcome some problems you will no doubt encounter.

* `git stash`
* `git pull`
* `git show`
* `git revert`
* `git clean`
>>>>>>> conflicts
