#include <unistd.h>
#include <sys/shm.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <sys/wait.h>
#include <mutex>

int fd[2]{};
int filhos[10]{};

std::mutex mtx;

void filho()
{
  pid_t meuPid = getpid();
  pid_t sorteado{};

  read(fd[0], &sorteado, sizeof(pid_t));

  if (sorteado == meuPid)
    std::cout << meuPid << ": fui sorteado" << std::endl;
  else
    std::cout << meuPid << ": não fui sorteado" << std::endl;
}

void sortear()
{
  pid_t sorteado = filhos[rand() % 10];

  for(int i{0} ; i < 10; i++)
    write(fd[1], &sorteado, sizeof(pid_t));

  int status{};

  for(int i{0}; i< 10; i++){
   // waitpid(filhos[i], &status, 0);
  }
}

int main()
{

  pipe(fd);

  for (int i = 0; i < 10; i++){
    pid_t child = fork();
    
    if (child == 0)
    {
      filho();
      break;
    }
    else{
      filhos[i] = child;
    }
  }

  sortear();
  
}