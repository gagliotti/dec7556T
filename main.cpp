#include <unistd.h>
#include <sys/shm.h>
#include <iostream>
#include <chrono>
#include <thread>

const int CHAVE = 10;

void produtor()
{
  int mem_id = shmget(CHAVE, sizeof(int) * 256, 0777 | IPC_CREAT);

  if (mem_id < 0)
  {
    std::cerr << "Erro ao criar area de memoria compartilhada..." << std::endl;
    exit(0);
  }

  int *ptr_mem = (int *)shmat(mem_id, nullptr, 0);

  if (ptr_mem == nullptr)
  {
    std::cerr << "Erro de mapeamento de memoria..." << std::endl;
    exit(0);
  }

  for (auto i{0}; i < 256; i++)
  {
    *(ptr_mem++) = i;
  }
  shmdt((void *)ptr_mem);
}

void consumidor()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  int mem_id, *ptr_mem, i;
  mem_id = shmget(CHAVE, sizeof(int) * 256, 0777 | IPC_CREAT);
  if (mem_id < 0)
  {
    std::cerr << "Erro ao criar area de memoria compartilhada...\n" << std::endl;
    exit(0);
  }
  ptr_mem = (int *)shmat(mem_id, 0, 0);
  if (ptr_mem == nullptr)
  {
    std::cerr << "Erro de mapeamento de memoria...\n" << std::endl;
    exit(0);
  }

  for (i = 0; i < 256; i++)
  {
    std::cerr << "Dados da memoria compartilhado: " << *(ptr_mem++) << std::endl;
  }

  shmdt((void *)ptr_mem);
  shmctl(mem_id, 0, IPC_RMID); //#define IPC_RMID 0 
}


int main()
{
  if (fork() > 0)
    produtor();
  else
    consumidor();
}