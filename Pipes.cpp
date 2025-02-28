#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipefd[2];  
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid = fork(); 

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {  
        
        close(pipefd[0]); 

        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 

        execlp("ls", "ls", NULL);
        perror("execlp failed"); 
        return 1;
    } else {
        
        close(pipefd[1]); 

        char buffer[1024];
        int bytesRead;
        int fileCount = 0;

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "Received Data:\n" << buffer; 

            
            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') fileCount++;
            }
        }

        close(pipefd[0]); 
        wait(NULL); 

        std::cout << "\nTotal Files/Folders: " << fileCount << "\n";
    }

    return 0;
}
