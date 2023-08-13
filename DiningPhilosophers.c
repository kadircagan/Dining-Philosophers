#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + (N-1)) % N
#define RIGHT (phnum + 1) % N


int surahi ;
int N;
int* state;
int* phil;
int* howmuch;
int* doAyran;
sem_t mutex;
sem_t mutexAyran;

sem_t* S;


void goGetAyran(int phnum)
{

	sem_wait(&mutexAyran);
    if(surahi>0){
    doAyran[phnum]=1;
    surahi=surahi-1;

    }


	sem_post(&mutexAyran);


	sleep(1);
}


void test(int phnum)
{  
	if (state[phnum] == HUNGRY
		&& state[LEFT] != EATING
		&& state[RIGHT] != EATING
        && doAyran[phnum]==1) {
	
		state[phnum] = EATING;
        doAyran[phnum]=0;
        howmuch[phnum] = howmuch[phnum]+1;
		sleep(2);

		sem_post(&S[phnum]);
	}
}

void take_fork(int phnum)
{

	sem_wait(&mutex);
	state[phnum] = HUNGRY;

	
	test(phnum);

	sem_post(&mutex);

	
	sem_wait(&S[phnum]);

	sleep(1);
}

void put_fork(int phnum)
{

	sem_wait(&mutex);

	state[phnum] = THINKING;



	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num)
{

	while (1) {

		int* i = num;

        if(doAyran[*i]==0){
            if(surahi ==0){
                state[*i]==THINKING;
                break;
            }
            else
            goGetAyran(*i);
        }else{

		sleep(1);

		take_fork(*i);

		sleep(0);

		put_fork(*i);

        }
	}
    return NULL;
}


int main(int argc, char* argv[])
{
	
int Numb;
	if (argc>=2)
		Numb = atoi(argv[1]);



N=Numb;   
state = (int*)malloc(sizeof(int)*Numb);
phil = (int*)malloc(sizeof(int)*Numb);
howmuch = (int*)malloc(sizeof(int)*Numb);
doAyran = (int*)malloc(sizeof(int)*Numb);
S = (sem_t*)malloc(sizeof(int)*Numb);
	int i;
	pthread_t thread_id[N];
    while(1){
    int randomnumber;
    srand ( time(NULL) );
    randomnumber = (rand() % (N*5) );
    printf("\nCurrent K: %d\n", randomnumber);

    surahi = randomnumber;
    for(i = 0; i < N; i++)
        phil[i] = i;
    for(i = 0; i < N; i++)
        doAyran[i] = 0;
    for(i = 0; i < N; i++)
        state[i] = THINKING;
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		pthread_create(&thread_id[i], NULL,
					philosopher, &phil[i]);

	}

 
	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);

    for (i = 0; i < N; i++){
        printf("%d ",howmuch[i]);
        howmuch[i] = 0 ;
    }
    fflush(stdout);
    sleep(5);

    }
	
}

