// Operating Systems
// Homework 2
// Frank Edwards (fge0001)

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;

int main() {
    
    while (true) {
        
        int i = 0;
        int g = 0;
        pid_t pid;
        string input;
        string fileName;
        string program;
        bool boolean = false;
        
        cin.clear();
        
        cout << "$ ";
        getline (cin, input);
        
        // Only continue if the input is non-empty
        if (!input.empty()) {
            
            string stringArray[50];
            
            // strtok() seperates the input into individual tokens based on
            // the space character
            char *inputPtr = new char [input.length()+1];
            strcpy(inputPtr, input.c_str());
            char *tokenPtr = strtok(inputPtr, " ");
            
            // The line only contains spaces => jump back to the beginning
            if (tokenPtr == 0) {
                continue;
            }
            
            // Copy the tokens over to a string array
            while (tokenPtr != 0) {
                string tempString = tokenPtr;
                stringArray[i] = tempString;
                tokenPtr = strtok(NULL, " ");
                i++;
            }
            
            // Determine if the next to last character is '>' and set a boolean to true if it is
            for (int j = 0; j < i; j++) {
                if (((j + 1) == (i - 1)) && (j != 0) && (stringArray[j].compare(">") == 0)) {
                    fileName = stringArray[j + 1];
                    boolean = true;
                }
            }
            
            // Parameter variables for execvp
            const char *programName = stringArray[0].c_str();
            char* arguments[50];
            
            // If the output is NOT being redirected
            if (boolean == false) {
                
                // The first element is, by convention, the filenam
                arguments[0] = &(stringArray[0])[0];
                
                // If the input contains no arguments then the arguments array
                // should only contain the filename of the program to one
                if (i == 1) {
                    arguments[1] = NULL;
                }
                
                else {
                    // Insert the arguments into the arguments array
                    for (int k = 1; k < i; k++) {
                        arguments[k] = (&(stringArray[k])[0]);
                        if (k == (i - 1)) {
                            arguments[k + 1] = NULL;
                        }
                    }
                }
                
                // SPAWNING IS BELOW
                
                // Fork the process!
                pid = fork();
                
                // Check for error in fork()
                if (pid < 0) {
                    perror("fork");
                    return EXIT_FAILURE;
                }
                
                // Tell the parent process to wait for the child to finish
                else if (pid > 0) {
                    waitpid(pid, NULL, 0);
                    // Do not return from the parent process - that exits
                    // the program
                }
                
                // Child process
                else if (pid == 0) {
                    int returnValue = execvp(programName, arguments);
                    if (returnValue == -1) {
                        cout << "No such file or directory" << endl;
                    }
                    // Return from the child process
                    return EXIT_SUCCESS;
                }
            }
            
            // If the output IS being redirected
            else if (boolean == true) {
                
                // Note that we are accessing the array at "i - 1" - that's
                // because the filename is at the length of the array minus one
                const char *fileName = stringArray[i - 1].c_str();
                
                // The first element is, by convention, the filename
                arguments[0] = &(stringArray[0])[0];
                
                // If the input received contains no arguments
                if (i <= 3) {
                    arguments[1] = NULL;
                }
                
                else {
                    // Insert the arguments into the arguments array
                    for (int k = 1; k < i - 2; k++) {
                        arguments[k] = (&(stringArray[k])[0]);
                        if (k == (i - 3)) {
                            arguments[k + 1] = NULL;
                        }
                    }
                }
                
                // SPAWNING IS BELOW
                
                // Fork the process!
                pid = fork();
                
                // Check for error in fork()
                if (pid < 0) {
                    perror("fork");
                    return EXIT_FAILURE;
                }
                
                // Tell the parent process to wait
                else if (pid > 0) {
                    waitpid(pid, NULL, 0);
                    // Don't return from here - that exits out of the program!
                }
                
                // Child process
                else if (pid == 0) {
                    
                    // Closes standard output and then opens the specified file,
                    // which is now standard output due to the close
                    close(STDOUT_FILENO);
                    int openReturn = open(fileName, O_WRONLY | O_CREAT | O_TRUNC);
                    if (openReturn == -1) {
                        perror("open");
                    }
                    
                    int returnValue = execvp(programName, arguments);
                    if (returnValue == -1) {
                        cout << "No such file or directory" << endl;
                    }
                    
                    // Do return from the child process
                    return EXIT_SUCCESS;
                }
            }
        }
    }
}
