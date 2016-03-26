# Operating-Systems---Shell
A simple Bash-like shell. Designed to be used with POSIX compliant systems. 

The main purpose of this assignment was to learn about spawning processes. 

The program reads in a string as its input, parses the arguments from that string, and then performs the appropriate actions. 
Once the user enters a command, like "ls", the program parses that argument from the input string, and then forks() the process. After forking the process, the program makes an exec() call, which replaces the child process with the "ls" process. 
