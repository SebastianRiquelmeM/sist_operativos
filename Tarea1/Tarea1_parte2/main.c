#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char **argv )
{
  /*
  Este programa recibe un n y crea n procesos en un arreglo pos[n],
  tiene un r aleatorio, que es la posicion de Zelensky,
  luego busca por cada pos[i]

  */
  int n; 
  printf("Ingrese n: ");
  scanf("%d", &n);
  printf("\n");
  pid_t pos[n];

  for(int i=0; i<n; i++){
      pos[i]=fork();
      srand(time(NULL)^getpid());
      if(pos[i]==0) while(1);
  }
  
  int r = rand()%n; //donde esta inicialmente
  int i = 0;  
  printf("Zelensky esta realmente en: pos[%d]\n",r);
  while(1){
    for(int i=0; i<n; i++){
      printf("Posición: pos[%d]\n",i,pos[i]);
    }
    printf("\n");
    if (i==r) { //Si la posicion i coincide con donde esta Zelensky
      kill(pos[i], SIGKILL); //Encontró a Zelensky, termina el programa
      printf("Zelensky ha sido encontrado en la posicion pos[%d], termina el programa.\n",i);
      return 0;
    }
    else{ //Si la posicion i no es donde esta Zelensky
      printf("Zelensky no esta en pos[%d]\n",i);
      r = rand()%n;
      printf("Zelensky esta realmente en: pos[%d]\n",r);
      printf("(Buscando en pos[%d]...)\n", i+1);
      sleep(4);
      kill(pos[i],  SIGSTOP); //Se mata el proceso de la posicion
      pos[i] = fork(); //Si crea un nuevo proceso en la posicion i
      if (pos[i] == 0) while(1); //No nos interesa hacer cosas en ese hijo7
                                // Asi que lo dejamos en un bucle c:
    }
    if(i+1 < n) i++;//Si aun no llegamos al final
    else i = 0;//Si ya llegamos al final
  }
  return 0;
}