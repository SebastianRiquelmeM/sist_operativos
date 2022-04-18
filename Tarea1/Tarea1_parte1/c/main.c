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
    int salir=0, perdio1=0, perdio2=0;
    
    int fd1[2],fd2[2]; //Array en que la función pipe nos devolverá los file descriptors fd[0]: lectura ; fd[1]: escritura 
    pid_t pid1, pid2;
    int buffer1,buffer2;
    int num1, num2; //Para cuando read devuelva el numero de caracteres que se han leído

    pipe(fd1); //Devuelve 0 si no hay error
    pipe(fd2);
    pid1 = fork(); //Crea un hijo, devuelve valor de tipo pid_t que es como un int
    
    if(pid1 > 0) pid2 = fork(); //Crea fork si es el padre
    
    int i=0;
    while(salir == 0){

        if(pid1 == 0){
         //   printf("Soy el proceso hijo 1\n");
            //1 piedra
            //2 papel
            //3 tijera
            srand(time(NULL)^getpid());
            int opc1 =  rand() % 3;
            opc1 ++;
            write(fd1[1], &opc1, sizeof(opc1));

            
            
            sleep(10);
        }
        else if(pid2 == 0){
           // printf("Soy el proceso hijo 2\n");
            srand(time(NULL)^getpid());
            int opc2 =  rand() % 3;
            opc2 ++;
            write(fd2[1], &opc2, sizeof(opc2));
            sleep(10);
        }
        else{
            //printf("Soy el proceso padre\n");
            printf("Pid1: [%d]\n",pid1);
            printf("Pid2: [%d]\n",pid2);
            /*
            
            printf("Pid1: [%d]\n",pid1);
            printf("Pid2: [%d]\n",pid2);*/
            
            num1 = read(fd1[0], &buffer1, sizeof(buffer1));
          
            //printf("Mensaje recibido desde hijo1: %d\n", buffer1);

            num2 = read(fd2[0], &buffer2, sizeof(buffer2));

            //printf("Mensaje recibido desde hijo2: %d\n", buffer2);

            //1 piedra
            //2 papel
            //3 tijera
            if(buffer1 == 1 && buffer2 == 2){
              printf("El jugador 1 eligió pieda y el jugador 2 eligió papel\n");
              printf("Perdió el jugador1, pues papel gana a la pieda\n\n");
              perdio1=1;
            }
            if(buffer1 == 1 && buffer2 == 3){
              printf("El jugador 1 eligió pieda y el jugador 2 eligió tijera\n");
              printf("Perdió el jugador2, pues piedra gana a tijera\n\n");
              perdio2=1;
            }
            if(buffer1 == 2 && buffer2 == 1){
              printf("El jugador 1 eligió papel y el jugador 2 eligió piedra\n");
              printf("Perdió el jugador2, pues papel gana a la pieda\n\n");
              perdio2=1;
            }
            if(buffer1 == 2 && buffer2 == 3){
              printf("El jugador 1 eligió papel y el jugador 2 eligió tijera\n");
              printf("Perdió el jugador1, pues tijera gana al papel\n\n");
              perdio1=1;
            }
            if(buffer1 == 3 && buffer2 == 1){
              printf("El jugador 1 eligió tijera y el jugador 2 eligió piedra\n");
              printf("Perdió el jugador1, pues piedra gana a tijera\n\n");
              perdio1=1;
            }
            if(buffer1 == 3 && buffer2 == 2){
              printf("El jugador 1 eligió tijera y el jugador 2 eligió papel\n");
              printf("Perdió el jugador2, pues tijera gana al papel\n\n");
              perdio2=1;
            }
            if(buffer1 == buffer2){
              printf("Ambos eligieron lo mismo\n");
              printf("Es empate\n\n");
            }


            if(perdio1 == 1){
                kill(pid1, SIGKILL);

            }
            else if(perdio2 == 1){
                kill(pid2, SIGKILL);

            }
            //-------------ELEGIR SI SEGUIR JUGANDO O NO
            int eleccion=0 ;
            printf("¿Desea agregar un nuevo jugador?\n");
            printf("1- Si\n");
            printf("2- No\n\n");
            printf("Opcion: ");
            scanf("%d", &eleccion);
            //printf("Usted ha elejido: %d \n\n",eleccion);

            if(eleccion == 2){
              salir = 1;
              kill(pid1, SIGKILL);
              kill(pid2, SIGKILL);
              return 0;
            }
            else if(eleccion == 1){
                if(perdio1 == 1){
                    perdio1=0;
                    pid1 = fork();
                }
                else if(perdio2 == 1){
                    perdio2=0;
                    pid2 = fork();
                }
            }


            
        }
        sleep(7);
    }
}