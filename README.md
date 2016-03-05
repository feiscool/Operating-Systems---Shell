# Operating-Systems---Shell
A simple Bash-like shell created for my Operating Systems class. Designed to be used with POSIX compliant systems. 

The main purpose of this homework was to learn about spawning processes. The program works by reading in a string from the command line, parsing the arguments from that string, and then performing the necessary actions. 

Once the user enters a command, like "ls", the program parses that argument from the input string, and then forks() the process. After forking the process, the program makes an exec() call, which replaces the child process with the "ls" process. 
