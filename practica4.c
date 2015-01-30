 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define TAM 100
void manejador_sig_term(int sig);

int main ()
{
  char ** items;
  int i, num, background;
  char expresion[TAM];

  //char buf[TAM];

 char *buf;
	buf=(char*) malloc(256*sizeof (char));

char *path;
	path=(char*) malloc(256*sizeof (char));

char *arg[TAM];

  int pid;
  ///int pru;
int status,w;
int sem;

signal (SIGINT, SIG_IGN); //ignoramos ctrl-c
signal (SIGTERM, manejador_sig_term);//saltamos a la rutina de tratamiento de la señal


do
{
  printf ("msh $ ");
  fgets (expresion, TAM, stdin);
  num = separaItems (expresion, &items, &background);
  //printf ("Numero de parametros: %d\n", num);


  if (num>0)
  {
    for (i=0; i<num; i++)
      //printf ("%d \"%s\"\n", i+1, items[i]);
   
	
    //printf ("Background: %d\n", background);

  
	if( !strcmp(items[0],"msexit") )
	{ exit(0);}
	
	 if( !strcmp(items[0],"mspwd") )
	{
		getcwd(buf,TAM);
		printf("%s \n",buf);
	}
	
	


	if( !strcmp(items[0],"mscd") )
	{
		getcwd(buf, TAM);
		//printf("1: %s", &buf);
		//if(items[1]==0) 	
		if(num!=2)		
		{//printf("mscd necesita argumentos\n");
		printf("Argumentos Incorrectos para la funcion mscd\n");		
		}				
		else
		{
		strcat(buf, "/");
		strcat(buf, items[1]);
		//printf("\n2: %s\n", &buf);
		//if(pru= chdir((const)&buf)) 	//printf("numero %d\n",pru);
		//printf("Directorio no valido\n");

		chdir(buf);
		}
	}
		
		
	 if( !strcmp(items[0],"mskill") )
	{
	/*if(num==2)
	{if ( !kill(pid,atoi(items[1])) )
	printf("Error: no se a podido mandar señal\n");
	}*/		 
	
	if(num==3)
	{	
	if ( ( sem=kill( atoi( items[2] ), atoi( items[1] ) ) )==-1)
	printf("Error: no se a podido mandar señal\n");
	}
	if(sem==0) printf("Finalizado proceso con PID= %d \n",atoi( items[2]  ));			 
	}

	//si no es ninguna de estas es que es una orden externa:

	if((strcmp(items[0],"mskill")) && (strcmp(items[0],"mscd")) && (strcmp(items[0],"msexit")) && (strcmp(items[0],"mspwd")))
	{
		pid=fork();
			if(pid==-1) { printf("Error no se ha podido crear el proceso hijo\n"); break;}
			
			if(pid==0)
			{
				printf("Estamos en el proceso hijo\n");
				strcat(path,"/bin/");
	
				strcat(path,items[0]);
	
				for(i=0;i<num;i++)
					{
					arg[i]=(char*) malloc(256*sizeof (char));
					strcpy(arg[i],items[i]);
					}
				arg[i]=NULL;
			
				execv(path,arg);
			
				break;
			}
			
			else
			{
				printf("Estamos en el proceso padre\n");
				//waitpid(pid,0,0);
				if(!background)
				{				 
					do {
                  			 w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
                   			if (w == -1) {
                       			perror("waitpid");
                       			exit(EXIT_FAILURE);
                   			}  
					if (WIFEXITED(status)) {
		              		 printf("exited, status=%d\n", WEXITSTATUS(status));
		           		} else if (WIFSIGNALED(status)) {
		              		 printf("killed by signal %d\n", WTERMSIG(status));
		           		} else if (WIFSTOPPED(status)) {
		              		 printf("stopped by signal %d\n", WSTOPSIG(status));
		          		 } else if (WIFCONTINUED(status)) {
		               		printf("continued\n");
		           		}
		       			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		      			 //exit(EXIT_SUCCESS);
				}	//break(EXIT_SUCCESS);
			
			}
	
	

	}
 liberaItems (items);
  }


}while(1);

  return 0;
}

void manejador_sig_term(int sig)
{
 printf("\nSIGTERM(15) no realizable.\n");
 return;
}


