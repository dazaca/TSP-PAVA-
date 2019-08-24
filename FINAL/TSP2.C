#include <stdio.h>	// printf
#include <conio.h>	// clrscr, getch
#include <dos.h>	// int86, MK_FP
#include <mem.h>	// memset
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define T_FACTOR 0.9

#define TEXTO 0x03
#define GRAFICO 0x13
#define BYTE unsigned char
#define N 25

char tecla;
int n,k,i,j,tabuk,city,NN;
int *P;

long double suma1,suma2,mejor,num_comb,factN,fact,diff2_1,T,Tmin,PROBABILIDAD;
int /*C[N][N],*/TABU[N],TABU2[N];


int coord[N][2]={{110,56},{286,158},{236,176},{86,144},{186,152},
		   {210,120},{160,60},{104,72},{246,124},{196,98},
		   {68,122},{88,80},{157,29},{40,56},{192,136},
		   {64,34},{270,152},{188,6},{118,86},{137,75},
		   {120,109},{146,42},{240,1},{260,82},{14,136}};


int a[N][N]=
{{0,3210,3070,1588,2056,1831,685,198,2328,1442,1036,353,803,878,2054,989,2771,1427,674,454,1038,496,1860,2070,2031},
{3210,0,1644,3549,1941,1379,2696,3165,1168,1774,3469,3367,3157,4073,1831,4184,439,3766,2743,2756,2838,3320,3444,2270,4464},
{3070,1644,0,3409,942,1239,2556,3025,1299,1634,3329,3227,3017,3933,1301,4044,1205,3626,2603,2616,2698,2845,3416,2401,4419},
{1588,3549,3409,0,1941,2170,1829,1409,2883,2102,595,1406,2087,2112,2240,2223,3110,2711,1052,1274,808,1780,3071,3214,1118},
{2056,1941,942,1941,0,801,1819,1835,1514,1196,1907,2020,2309,2726,184,2837,1502,2933,1401,1602,1276,2002,3293,2132,2902},
{1831,1379,1239,2170,801,0,1317,1786,713,395,2090,1988,1778,2694,617,2805,940,2387,1364,1377,1459,2055,2177,1331,3085},
{685,2696,2556,1829,1819,1317,0,789,1771,922,1661,991,461,1530,1795,1641,2257,1070,775,555,1139,289,1430,1385,2656},
{198,3165,3025,1409,1835,1786,789,0,2283,1397,857,202,968,908,2009,1019,2726,1592,434,409,817,661,1952,2174,1852},
{2328,1168,1299,2883,1514,713,1771,2283,0,886,2803,2485,2134,3191,1330,3302,729,2774,2077,1874,2172,2060,2276,1102,3798},
{1442,1774,1634,2102,1196,395,922,1397,886,0,2010,1599,1383,2305,1012,2416,1335,1992,1087,988,1294,1211,1782,1137,3005},
{1036,3469,3329,595,1907,2090,1661,857,2803,2010,0,854,1840,1560,2160,1671,3030,2464,962,1134,716,1533,2824,3046,995 },
{353,3367,3227,1406,2020,1988,991,202,2485,1599,854,0,1170,706,2211,817,2928,1794,636, 611,864,863,2154,2376,1849},
{803,3157,3017,2087,2309,1778,461,968,2134,1383,1840,1170,0,1681,2256,1221,2718,624,1033,813,1397,307,984,1748,2835},
{878,4073,3933,2112,2726,2694,1530,908,3191,2305,1560,211,1681,0,2917,644,3634,2305,1342,1317,1570,1374,2665,2915,2555},
{2054,1831,1301,2240,184,617,1795,2009,1330,1012,2160,817,2256,2917,0,3028,1392,2865,1587,1600,1529,1998,2794,1948,3155},
{989,4184,4044,2223,2837,2805,1641,1019,3302,2416,1671,2928,1221,644,3028,0,3745,1449,1453,1428,1681,1485,1809,3026,2666},
{2771,439,1205,3110,1502,940,2257,2726,729,1335,3030,1794,2718,3634,1392,3745,0,3327,2304,2317,2399,2715,3005,1831,4025},
{1427,3766,3626,2711,2933,2387,1070,1592,2774,1992,2624,636,624,2305,2865,1449,3327,0,1657,1437,2021,931,360,2378,3459},
{674,2743,2603,1052,1401,1364, 775,434,2077,1087,962,611,1033,1342,1587,1453,2304,1657,0,220,383,726,2017,2160,1957},
{454,2756,2616,1274,1602,1377,555,409,1874,988,1534,864,813,1317,1600,1428,2317,1437,220,0,584,495,1797,1940,2129},
{1038,2838,2698,808,1276,1459,1139,817,2172,1294,716,864,1397,1570,1529,1681,2399,2021,383,584,0,1090,2381,2336,1711},
{496,3320,2845,1780,2002,2055,289,661,2060,1211,1533,863,307,1374 ,1998,1485,2715,931,726,495,1090,0,1291,1674,2528},
{1860,3444,3416,3071,3293,2177,1430,1952,2276,1782,2824,2154,984,2665,2794,1809,3005,360,2017,1797,2381,1291,0,1620,3819},
{2070,2270,2401,3214,2132,1331,1385,2174,1102,1137,3046,2376,1748,2915,1948,3026,1831,2378,2160,1940,2336,1674,1620,0,4041},
{2031,4464,4419,1118,2902,3085,2656,1852,3798,3005,995,1849,2835,2555,3155,2666,4025,3459,1957,2129,1711,2528,3819,4041,0}};


// Puntero a la memoria de video
BYTE *DIR_VGA=(BYTE *) MK_FP(0xA000, 0);

///////////////////////// Prototipos de funciones/////////////////////////////
void SetMode(char mode);
void PutPixel(int x, int y, BYTE color);
BYTE GetPixel(int x, int y);
void Cls(BYTE color);
void Line(int x1, int y1, int x2, int y2, BYTE color);
int sgn(int num);
long double dist_revers(int NN);

/////////////////////////////////////////////////////////////////////////////


long double dist_revers(int NN)
{

 int k1,k2,tabukk,i,j,n,pos1,pos2;
 long double suma2;

 suma2=0.0;

 do
 {
   pos1=0;
   tabukk=0;
   k1=random(N);
   for(n=0; n<=(NN-1);n++)
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
  pos2=0;
  tabukk=0;
  k2=random(N);
  for(n=0; n<=(NN-1);n++)
  {
   if (k2==TABU[n])
   {
    tabukk++;
    break;
   }
   if(!tabukk) pos2++;

  }
 }while(!(tabukk)||(k2==k1)); //Busca una ciudad en TABU[] distinta de k1


 for(n=0;n<NN;n++)    //Igualamos todos los elementos de TABU2 a los de TABU
 {                     //...
  TABU2[n]=TABU[n];
 }

 TABU2[pos1]=k2;       //E insertamos en las posiciones pos1 y pos2 de TABU2
 TABU2[pos2]=k1;       //los valores k2 y k1 respectivamente que en TABU
		       //ocupaban las posiciones pos2 y pos1.
 n=0;

 do                       //Calcula la distancia de//
 {                        //un tour completo por   //
   i=TABU2[n];            //las ciudades almacena- //
   j=TABU2[n+1];          //das en TABU2[].        //
   suma2+=a[i][j];        ///////////////////////////
   n++;                                            //
  }while(n<NN-1);                                   //
						   //
 i=TABU2[NN-1];
 j=TABU2[0];
 suma2+=a[i][j];

 return suma2;
}

// Devuelve el signo de un numero
int sgn(int num)
{
  if(num>0) return(1);
  if(num<0) return(-1);
  return(0);
}


// Dibuja una linea con cualquier pendiente
void Line(int x1, int y1, int x2, int y2, BYTE color)
{
  int i, s, u, v, dx1, dx2, dy1, dy2, m, n;

  u=x2-x1;
  v=y2-y1;
  dx1=sgn(u);
  dy1=sgn(v);
  dx2=sgn(u);
  dy2=0;
  m=abs(u);
  n=abs(v);
  if(!(m>n))
  {
    dx2=0;
    dy2=sgn(v);
    m=abs(v);
    n=abs(u);
  }
  s=m>>2; // s=m/2;
  for(i=0; i<=m; i++)
  {
    PutPixel(x1, y1, color);
    s=s+n;
    if (!(s<m))
    {
      s=s-m;
      x1=x1+dx1;
      y1=y1+dy1;
    }
    else
    {
      x1=x1+dx2;
      y1=y1+dy2;
    }
  }
}



// Setea un modo de video especifico
void SetMode(char mode)
{
	union REGS r;

	r.h.ah=0;
	r.h.al=mode;
	int86(0x10, &r, &r);
}

// Coloca un pixel en la pantalla en una posicion determinada
void PutPixel(int x, int y, BYTE color)
{
	DIR_VGA[(y<<8)+(y<<6)+x]=color;
}

// Obtiene el color de un pixel de una posicion determinada de la pantalla
BYTE GetPixel(int x, int y)
{
	return (DIR_VGA[(y<<8)+(y<<6)+x]);
}

// Borra la pantalla con un color determinado
void Cls(BYTE color)
{
	memset(DIR_VGA, color, 64000);
}




void main(void)
{

  suma1=suma2=0.0;
 T=10000.0;
 Tmin=(3*pow10(-200));
 clrscr();
 randomize();

 P=TABU;







 clrscr();

 for (n=0; n< N; n++)
 {
 *(P+n)=-1;
 }

 printf("\nIntro el n£mero de ciudad (-1) para terminar");

 i=0;

 for(;;)
 {
  scanf("%d",&city);
  fflush(stdin);
  if(city==-1) break;

  if((city>=0)&&(city)<=24)
  {
   TABU[i]=city;
   i++;

  }
  else clreol();
 }

 NN=i;




 SetMode(GRAFICO);


 Cls(1);


 /* printf("Introduzca ciudad inicio: ");
 scanf("%d",TABU[0]);
 fflush(stdin);*/

 n=0;
 i=0;

/* do
 {
  ///////////////////////////////////////////////////
  do                         //Busca un k no conte-//
  {                          //nido en TABU[].     //
   tabuk=0;                  ////////////////////////
   k=random(N);                                    //
   for(i=0; i<=(N-1);i++)                          //
   {                                               //
    if (k==TABU[i]) tabuk++;                       //
   }                                               //
  }while(tabuk>=1);                                //
			     ////////////////////////
  TABU[n+1]=k;               //Y lo va introducien-//
  n++;                       //do en TABU[] hasta  //
 }while(n<(N-1));            //que ‚ste est‚ lleno.//
 ////////////////////////////////////////////////////*/



 ////////////////////////////////////////////////////
 n=0;                     //                       //
 do                       //Calcula la distancia de//
  {                       //un tour completo por   //
   i=TABU[n];             //las ciudades almacena- //
   j=TABU[n+1];           //das en TABU[].         //
   suma1+=a[i][j];        ///////////////////////////
   n++;                                            //
  }while(n<NN-1);                                   //
						   //
  i=TABU[NN-1];                                     //
  j=TABU[0];                                       //
  suma1+=a[i][j];                                  //
						   //
						   //
 ////////////////////////////////////////////////////


 while(T>Tmin)
 {

   PROBABILIDAD=0.0;


   suma2=dist_revers(NN);

   if(suma2<=suma1)
   {
    suma1=suma2;

    for(n=0;n<NN;n++)  // Igualamos todos los elementos de TABU a los de TABU2.
    {
     TABU[n]=TABU2[n];
    }
   //  clrscr();
  /*gotoxy(1,3);
    {*/
  //   printf("TOTAL = %Lf",suma2);
  /*}*/
   //  printf("\n");
  /*gotoxy(1,1);
    {*/
     ////////////////////////////////////////////////////
  /* for (i=0;i<N;i++)       //Imprime por orden de re-//
     {                       //corrido las ciudades por//
     printf("%d-",TABU2[i]);  //las que se pasa a partir//
     }                       //del orden con que son   //
			     //almacenadas en TABU[].  //
     ////////////////////////////////////////////////////
     printf("%d",TABU2[0]);
  /*}*/


   }

   else
   {
    diff2_1=suma2-suma1;

    PROBABILIDAD=exp(-(diff2_1)/T);
    if(PROBABILIDAD>0.8)
    {

     suma1=suma2;

     for(n=0;n<NN;n++)  // Igualamos todos los elementos de TABU a los de TABU2.
     {
     TABU[n]=TABU2[n];
     }
    }

   /*  clrscr();
  /*gotoxy(1,3);
    {*/
   /*  printf("TOTAL = %Lf",suma1);*/
  /*}*/

  /*gotoxy(1,1);
    {*/
  /* printf("\n");
     ////////////////////////////////////////////////////
     for (i=0;i<N;i++)       //Imprime por orden de re-//
     {                       //corrido las ciudades por//
     printf("%d-",TABU[i]); //las que se pasa a partir//
     }                       //del orden con que son   //
			     //almacenadas en TABU[].  //
     ////////////////////////////////////////////////////
     printf("%d",TABU[0]);
  /*}*/

   }


   Cls(1);

	for(j=0;j<NN-1;j++)
	{
	 i=TABU[j];
	 k=TABU[j+1];
	 Line(coord[i][0],coord[i][1],coord[k][0],coord[k][1],14);

	}

	k=TABU[NN-1];
	i=TABU[0];

	Line(coord[i][0],coord[i][1],coord[k][0],coord[k][1],14);

	gotoxy(1,25);
	{
	 printf("TOTAL = %Lf",suma1);
	}


   T*=T_FACTOR;

 }











	Cls(1);

	for(j=0;j<NN-1;j++)
	{
	 i=TABU[j];
	 k=TABU[j+1];
	 Line(coord[i][0],coord[i][1],coord[k][0],coord[k][1],14);

	}

       k=TABU[NN-1];
       i=TABU[0];

       Line(coord[i][0],coord[i][1],coord[k][0],coord[k][1],14);

	gotoxy(10,7);
	printf("Amsterdam");
	gotoxy(35,21);
	printf("Ankara");
	gotoxy(29,23);
	printf("Atenas");
	gotoxy(7,19);
	printf("Barcelona");
	gotoxy(22,19);
	printf("Bari");
	gotoxy(27,15);
	printf("Belgrado");
	gotoxy(21,8);
	printf("Berl¡n");
	gotoxy(10,9);
	printf("Bruselas");
	gotoxy(32,16);
	printf("Bucarest");
	gotoxy(26,13);
	printf("Budapest");
	gotoxy(11,16);
	printf("Burdeos");
	gotoxy(6,11);
	printf("Calais");
	gotoxy(20,4);
	printf("Copenhague");
	gotoxy(1,7);
	printf("Dubl¡n");
	gotoxy(20,17);
	printf("Dubrovnic");
	gotoxy(5,4);
	printf("Edimburgo");
	gotoxy(33,19);
	printf("Estambul");
	gotoxy(15,1);
	printf("Estocolmo");
	gotoxy(13,12);
	printf("Estrasburgo");
	gotoxy(19,10);
	printf("Frankfurt");
	gotoxy(16,14);
	printf("Ginebra");
	gotoxy(20,6);
	printf("Hamburgo");
	gotoxy(32,1);
	printf("Helsinki");
	gotoxy(34,11);
	printf("Kiev");
	gotoxy(1,17);
	printf("Coru¤a");

	gotoxy(1,25);
	{
	 printf("TOTAL = %Lf",suma1);
	}



      /*	PutPixel(110,56,0);  //0
	PutPixel(111,56,0);  //0
	PutPixel(110,57,0);  //0
	PutPixel(110,57,0);  //0
	PutPixel(109,56,0);  //0
	PutPixel(110,55,0);  //0
	PutPixel(110,56,0);  //0
	PutPixel(110,56,0);  //0


	PutPixel(286,158,0); //1
	PutPixel(236,176,0); //2
	PutPixel(86,144,0);  //3
	PutPixel(186,152,0); //4
	PutPixel(210,120,0); //5
	PutPixel(160,60,0);  //6
	PutPixel(104,72,0);  //7
	PutPixel(246,124,0); //8
	PutPixel(196,98,0);  //9
	PutPixel(68,122,0);  //10
	PutPixel(88,80,0);   //11
	PutPixel(157,29,0);  //12
	PutPixel(40,56,0);   //13
	PutPixel(192,136,0); //14
	PutPixel(64,34,0);   //15
	PutPixel(270,152,0); //16
	PutPixel(188,6,0);   //17
	PutPixel(118,86,0);  //18
	PutPixel(137,75,0);  //19
	PutPixel(120,109,0); //20
	PutPixel(146,42,0);  //21
	PutPixel(240,1,0);   //22
	PutPixel(260,82,0);  //23
	PutPixel(14,136,0);  //24*/
       /*gotoxy(1,5);
       //printf("asdfasdf");

	gotoxy(1,3);
	printf("2");*/



       //Line(60,106,30,69,14);
       //Line(30,69,89,100,14);
       //Line(89,100,20,10,14);


	getch();



	SetMode(TEXTO);

}