#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

struct Asignatura{
    int duracion_estudio_semanal; //en horas
    int dia_limite_termino; // (0-6)
    int hora_limite_termino; // (0-23)
};

int main()
{
    printf("\n\n-----Estas chalas culias no me roan la calma-----\n\n");
    
    //struct Asignatura Asignatura[i];
    

    int K=5;
    Asignatura asignaturas[K];
    for(int i=0; i<K ;i++){
        asignaturas[i].duracion_estudio_semanal = 15;
        asignaturas[i].dia_limite_termino = 5;
        asignaturas[i].hora_limite_termino = 22;
    }
    
    //printf("\n\nDuracion: %d\n\n",asignaturas[2].duracion_estudio_semanal);
    
}