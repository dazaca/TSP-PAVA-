#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define N 4

char tecla;
int TABU[N]={0,1,2,3};
int TABU2[N];

float a[N][N]={{0.0,1.3,1.0,1.2},
	       {1.3,0.0,2.0,2.5},
	       {1.0,2.0,0.0,1.6},
	       {1.2,2.5,1.6,0.0} };
int k1,k2,tabukk,i,j,n,pos1,pos2;
long double suma1,suma2,mejor;


void main (void)
{
 clrscr();
 pos1=0;
 pos2=0;

 do
 {
   tabukk=0;
   k1=random(N);
   for(n=0; n<=(N-1);n++)
   {
    if (k1==TABU[n])
    {
     tabukk++;
     break;
    }
    if(!tabukk) pos1++;   // pos1 ser  la posici¢n de la 1¦ ciudad de las dos
			  // en TABU[] a partir de las cuales se calcula una
			  // nueva distancia.

   }
 }while(!tabukk); //Busca una ciudad en TABU[]

 do
 {
  tabukk=0;
  k2=random(N);
  for(n=0; n<=(N-1);n++)
  {
   if (k2==TABU[n])
   {
    tabukk++;
    break;
   }
   if(!tabukk) pos2++;

  }
 }while(!(tabukk)||(k2==k1)); //Busca una ciudad en TABU[] distinta de k1

 n=0;

 do                       //Calcula la distancia de//
  {                       //un tour completo por   //
   i=TABU[n];             //las ciudades almacena- //
   j=TABU[n+1];           //das en TABU[].         //
   suma1+=a[i][j];        ///////////////////////////
   n++;                                            //
  }while(n<N-1);                                   //
						   //
 i=TABU[N-1];
 j=TABU[0];
 suma1+=a[i][j];

 for(n=0;n<N;n++)      //Igualamos todos los elementos de TABU2 a los de TABU
 {                     //...
  TABU2[n]=TABU[n];
 }

 TABU2[pos1]=k2;       //E insertamos en las posiciones pos1 y pos2 de TABU2
 TABU2[pos2]=k1;       //los valores k2 y k1 respectivamente que en TABU
		       //ocupaban las posiciones pos2 y pos1.
 n=0;

 do                       //Calcula la distancia de//
 {                        //un tour completo por   //
   i=TABU2[n];             //las ciudades almacena- //
   j=TABU2[n+1];           //das en TABU[].         //
   suma2+=a[i][j];        ///////////////////////////
   n++;                                            //
  }while(n<N-1);                                   //
						   //
 i=TABU2[N-1];
 j=TABU2[0];
 suma2+=a[i][j];

}


