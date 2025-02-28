#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipefd[2];  //creates pipe with read and write end
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    //creates child process and executes 1s comand
    
    pid = fork(); 

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {  //Execution of process, reading file numbers
        
        close(pipefd[0]); 

        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 

        execlp("ls", "ls", NULL);
        perror("execlp failed"); 
        return 1;
    } else {
        
        close(pipefd[1]); //Close write end of pipe

        char buffer[1024];
        int bytesRead;
        int fileCount = 0;

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) { //Counting files and \n entries
            buffer[bytesRead] = '\0';
            std::cout << "Received Data:\n" << buffer; 

            
            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') fileCount++;
            }
        }

        close(pipefd[0]); //Close read and wait for child to finish process execution
        wait(NULL); 

        std::cout << "\nTotal Files/Folders: " << fileCount << "\n"; //Display all files found
    }

    return 0;
}
