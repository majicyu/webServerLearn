#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;
int number = 0;

void* another(void* arg){
        for(int i=0;i<10;i++){
            number++;
            printf("%d ",number);
        }

    printf("in child thread,lock the mutex\n");
    pthread_mutex_lock(&mutex);
    sleep(5);
    pthread_mutex_unlock(&mutex);
}

void prepare(){
    pthread_mutex_lock(&mutex);
}
void infork(){
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_mutex_init(&mutex,NULL);
    pthread_t id;
    //int number = 0;
    pthread_create(&id,NULL,another,NULL);
    printf("fast\n");
    // sleep(1);
    pthread_atfork(prepare,infork,infork);
    int pid = fork();
    
    if(pid < 0){
        pthread_join(id,NULL);
        pthread_mutex_destroy(&mutex);
        return 1;
    }
    else if(pid == 0){
        printf("I am in the child,want to get the lock\n");
        pthread_mutex_lock(&mutex);
        printf("I can not run to here,oop...\n");
        pthread_mutex_unlock(&mutex);
        exit(0);
    }
    else{
        for(int i=0;i<10;i++){
            number++;
            printf("%d ",number);
        }
        printf("in the parent\n");
        wait(NULL);
    }
    pthread_join(id,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
