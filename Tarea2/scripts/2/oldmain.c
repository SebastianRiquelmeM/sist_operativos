#include <stdio.h>
#include <semaphore.h>

typedef struct _rwlock_t{
	sem_t lock;   // semaforo binario bloquear 
	sem_t writelock; // semaforo para permitir solo un escritor o muchos lectores
	int readers;     // cuantos lectores estan accediendo c:
} rwlock_t;

void rwlock_init(rwlock_t *rw){ //inicializacion
	rw->readers =0;     // cero lectoresa
	sem_init(&rw->lock,0,1);  
	sem_init(&rw->writelock,0,1);  // semaforos verde y rojo 
}

void rwlock_acquire_readlock(rwlock_t *rw){ // adquirir lectura 
	sem_wait(&rw->lock);   // espera el acceso exclusivo
	rw->readers++;         // auemnta el numero de lectores
    printf("readers: %d",rw->readers);
	if (rw->readers ==1)   
		sem_wait(&rw->writelock);  // con esto cuando alguien lee bloquea al que escribe
	sem_post(&rw->lock);  // cuando finaliza se finaliza el acceso al lector

}

void rwlock_release_readlock(rwlock_t *rw){   // sale region critica
	sem_wait(&rw->lock);  // adquire el bloqueo 
	rw->readers--;        // disminuye lectores
	if(rw->readers == 0)  
		sem_post(&rw->writelock);  // señaliza al escritor quie puede acceder
	sem_post(&rw->writelock);      
}

void rwlock_acquire_writelock(rwlock_t *rw){  // cuando entra el escritor pregunta la señal si esta libre
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw){  //cuando se libera del escritor...
	sem_post(&rw->writelock);
}

int main() {

    struct _rwlock_t rwlock1;

    rwlock1.readers=5;
    rwlock_init(&rwlock1);
    for(int i=0;i<5;i++){
        rwlock_acquire_readlock(&rwlock1);
        printf("\n");
    }
    


    printf("\nHello, World!\n");
    return 0;

}