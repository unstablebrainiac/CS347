#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// #include <semaphore.h>

#define NUMTHRDS 10
pthread_mutex_t mutex;

int votes[21];
int total_votes=0;
int temp = 0;
int tempi = 0;

void *computation(void *data){
	int j= *((int*)data);
	char jc[10];
	sprintf(jc,"%d",j);

	char ext[5];
	strcpy(ext,".txt");

	//string s = to_string(j);
	strcat(jc,ext);
	//printf("%s\n",jc);

	FILE *file;
	file = fopen(jc,"r");

	char *pos;
	char line[256];
	char *token;
	//char x = fgetc(file);
	int x;
	int inp[2];


	while(fgets(line,sizeof(line),file)){
						

		if ((pos=strchr(line, '\n')) != NULL)
  		  	*pos = '\0';

  		if(strlen(line)!=0){

			pthread_mutex_lock (&mutex);
				int k=0;
          		token = strtok(line," ");

          		while(token!=NULL){

          			inp[k] = atoi(token);
          		//	printf("%d\n",inp[k] );
          			k++;         			
          			token = strtok(NULL," ");

          		}

          		if(k==2){
          			votes[inp[0]] = votes[inp[0]] + inp[1]; 
          			
          			temp = temp + inp[1];
          			total_votes = total_votes + inp[1];


          		}

          		if (temp>49){

          			    for(int i=0;i<21;i++){
						  	printf("Votes of party ");
						  	printf("%d ",i);
						  	printf("%d\n",votes[i]);
					  	}

					  	printf("\n\n\n\n\n\n");	
					  	tempi = temp/50;
          				temp = temp - (tempi)*50;
          		}


            pthread_mutex_unlock (&mutex);

  		}

	}

    pthread_exit((void*) 0);

}











int main(){

	int tid[10];

	for(int i=0;i<21;i++){
		votes[i] = 0;
	}

	void *status;
	pthread_mutex_init(&mutex, NULL);
	pthread_t callThd[NUMTHRDS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	
	for(int i=0;i<NUMTHRDS;i++)
	  {

	   tid[i] = i+1;
	   pthread_create(&callThd[i], NULL, computation, (void *)&tid[i]);
	   

	   }


	 pthread_attr_destroy(&attr);

	for(int f=0;f<NUMTHRDS;f++) {
	  pthread_join(callThd[f], &status);
	  }

	  for(int i=0;i<21;i++){
	  	printf("Votes of party ");
	  	printf("%d ",i);
	  	printf("%d\n",votes[i]);
	  }

	   return 0;
}