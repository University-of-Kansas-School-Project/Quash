# Quash
EECS678 - Operating Systems - QUite A SHell (SQUASH) is a lite bash simulator.

# Overview of Project 1
Quash should be able to run executables (the basic function of a shell) with command line parameters. Explore the use of fork() and exec() to run executables. 
If the executable is not specified in the absolute path format (starting with ‘/’), quash should search the directories in the environment variable PATH (see below). If no executable file is found, quash should print an error message. 
Quash should allow both foreground and background executions. Character ‘&’ is used to indicate background execution. Commands without ‘&’ are assumed to run in foreground. Explore the use of wait(), waitpid(), and the SIGCHLD signal to handle foreground and background processes. 
Quash should support the following built-in functions: 
– set to set the value of a variable in the environment. 
Quash should inherit the initial environment from the command line that invokes it. In C, this is achieved by using the char **envp argument to main, as in: int main (int argc, char **argv, char **envp) Quash should support (at least) two built-in variables: PATH, which is used to record the paths to search for executables, and HOME, the user’s home directory. PATH may contain multiple directories (separated by :). For example, The command ‘set PATH=/usr/bin:/bin’ in quash should set the variable PATH to contain two directories, /usr/bin and /bin. – Child processes should inherit the environment variables (in C, various flavors of the exec system call allow you to pass the environment to child processes) – cd dir to change the current working directory to dir. cd with no arguments should change to the directory in the HOME environment variable. Explore the use of chdir() to change the working directory. – quit and exit to exit quash. – jobs should print all of the currently running background processes in the format: [JOBID] PID COMMAND where JOBID is a unique positive integer quash assigns to the job to identify it, PID is the PID of the child process used for the job, and COMMAND is the command used to invoke the job. 
When a command is run in the background, quash should print: [JOBID] PID running in background 
When a background command finishes, quash should print: [JOBID] PID finished COMMAND 
Quash should implement I/O redirection. The ‘<’ character is used to redirect the standard input from a file. The ‘>’ character is used to redirect the standard output to a file. For example, ‘ls > a’ sends to results of ls to file a. Explore the use of freopen() to achieve I/O redirection. 
Quash should implement the pipe (|) command. e.g. ‘cat myprog.c | more’. 
Quash should support reading commands interactively (with a prompt) or reading a set of commands stored in a file that is redirected from standard input, as in: bash> quash < commands.txt 

# GRADING POLICY
Partial credit will be given for incomplete efforts. However, a program that cannot compile will get 0 points. Point breakdown for features is below: 
Run executables without arguments (10) 
Run executables with arguments (10) 
set for HOME and PATH work properly (5) 
exit and quit work properly (5)
cd (with and without arguments) works properly (5)  
PATH works properly. Give error messages when the executable is not found (10) 
Child processes inherit the environment (5) 
Allow background/foreground execution (&) (5) 
Printing/reporting of background processes, (including the jobs command) (10) 
Allow file redirection (> and <) (5) 
Allow (1) pipe (|) (10) 
Supports reading commands from prompt and from file (10) 
Report (10) 
Bonus points (you can get bonus points only if you have everything else working (or very close to working)) 
Support multiple pipes in one command. (10) 
kill command delivers signals to background processes. The kill command has the format: kill SIGNUM JOBID, where SIGNUM is an integer specifying the signal number, and JOBID is an integer that specifies the job that should receive the signal. (5) 

# MATERIALS TO BE HANDED IN 
Each group should submit the project by email to the TA (ishrakhayet@ku.edu). Create a tar file with all of your source code and a Makefile and build instructions. The report should describe each of the features in your quash shell and (briefly) how you implemented each feature. Also, describe how you tested quash and document any required features that are not completely implemented in your quash shell.

# Project Tasks/Outline
Implement QUASH c++ class with:
Public member Functions predeclared:
bool set(std::string path);
True if path successfully set, otherwise false.
bool cd(std::string dir);
True if dir at path exists and can be entered, otherwise false.
void exit()/void quit();
Deallocate any memory on the heap and cleanly exit the program.
bool run(std::string programPath, std::string programCommands);
Run commands using tools fork() and exec() 
If programPath includes absolute path (/…) then run program at path, otherwise search for program in PATH and run there, else return false if no program is found.
Implement use of ‘&’ to run programs in background. Use wait(), waitpid(), and the SIGCHLD signal to handle foreground and background processes.
Void jobs()
For jobs in the background output:
[JOBID] PID running in background
For jobs finished running in the background output:
[JOBID] PID finished COMMAND
bool writeOut(std::string path);
Using the ‘>’ operator, write out to a file at path into the left hand side of the operator as redirected output from the file rather than command line.
bool readIn(std::string path);
Using the ‘<’ operator, read a file at path into the left hand side of the operator as redirected input from the file rather than command line.
Bool pipe(std::string leftProgram, std::string rightProgram);
Implements the pipe between a leftProgram argument and a rightProgram argument.
EXTRA CREDIT: Bool kill(int sigNum, int jobID);
The kill command has the format: kill SIGNUM JOBID, where SIGNUM is an integer specifying the signal number, and JOBID is an integer that specifies the job that should receive the signal. (5)
Private member variables:
std::string path;
std::string home;
std::string currentDir;
Implement Set function within squash class for PATH env variable.
Implement Set function within squash class for HOME env variable.
Implement cd function within squash class for currentDir env variable. (Use chdir())
Implement quit and exit within squash class to cleanly exit program.
Implement run within squash class for executables without arguments.
Implement run within squash class for executables with arguments.
Implement jobs within squash class for listing jobs running in the background.
Implement redirection via ‘>’ and ‘<’ operators to read in or output to a file.
Implement pipe within squash class for performing pipe operations within squash.
ECsst: Implement Kill within squash for performing kill operations within squash.


