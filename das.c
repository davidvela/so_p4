 /* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
  */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "parser.h"

#define TAM 40

void Rutina(int sig);
int main(int argc, char *argv[])
{
	char **items;
	int background, i, num, sig, pidHijo;
 
	char expresion[TAM], buffer[TAM];

  signal(2, SIG_IGN);//ignoramos ctrl+c
  signal(15, Rutina);//saltamos a la rutina de atencion de señal  
 
  
 while(1)
 {
 	printf("\nms$:");
	fgets(expresion, TAM, stdin);
	num= separaItems(expresion, &items, &background);
	
	if (num == 0) continue;

	else //if (num > 1)
	//else
	{
		if(!strcmp(items[0], "msexit") )
			break;
		if (!strcmp(items[0], "mspwd") )
		{
			getcwd(&buffer, TAM);
			printf("%s\n", &buffer);
			continue;
		}
		if (!strcmp(items[0], "mskill") )
		{
			
			if ( !kill(atoi(items[2]),atoi(items[1])) )
			{
			 printf("Error: no se a podido mandar señal\n");
			 continue;
			}
		}
	//}
	//else if(num > 1)
	//{
	 	if (!strcmp(items[0], "mscd") )
		{
			getcwd(&buffer, TAM);
			//printf("1: %s", &buffer);
			strcat(buffer, "/");
			strcat(buffer, items[1]);
			//printf("\n2: %s\n", &buffer);
			if( chdir((const)&buffer))
				printf("Directorio no valido\n");
			continue;
		}
		else
		switch( pidHijo=fork())
		{
			case -1: 
				printf("Error\n");
				return -1;
			case 0:
				//getcwd(&buffer, TAM);
				//strcat(buffer, "/");
				//if( execv(&buffer, items) )
				if ( execvp(items[0], items))
				printf("eRROR 1\n");
				continue;
		
		}
		
	}
	
}
return 0;
}

void Rutina(int sig)
{
 printf("\nSIGTERM(15) no realizable.\n ms$:");
 return;
}


		

