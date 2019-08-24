#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include <graphics.h>
#define N 25


char tecla,nom[]="a:dista.dat", dist_TOUR[7];
int i,j,k,NN,city,num,control;

FILE *fich;


unsigned int suma1,suma2;

int TABU[N],TABU2[N];

int coord[N][2]={{220,134},{572,379},{472,422},{172,346},{372,365},
		   {420,288},{320,144},{208,173},{492,298},{392,235},
		   {136,293},{176,192},{314,70},{80,134},{384,326},
		   {128,82},{540,365},{376,14},{236,206},{274,180},
		   {240,262},{292,125},{480,7},{520,197},{28,326}};


struct tciudad
{
 int posx;
 int posy;
 char nombre[30];
 int distancia[25];
};

struct tciudad ciudad[N];
struct tciudad *pciudad;



///////////////////////// PROTOTIPOS DE FUNCIONES ///////////////////////////

void sim_annel(int TABU[N],int TABU2[N],unsigned int *suma1);
unsigned int dist_revers(int TABU[N], int TABU2[N]);
int capt_matr(struct tciudad *pciudad,int *num);
void calc_dist(unsigned int *suma1);
void rell_TABU(int *NN);

/////////////////// PROTOTIPOS FUNCIONES GRAFICAS ///////////////////////////
void inicia_graf(void);
void coloc_ciudades(void);
void marc_ciudades_selecc(void);
void traz_lineas(void);
void rell_rect(int x1,int y1, int x2, int y2,int color, int stilo);
int ventana1 (void);
int ventana1_2(int TABU[N],int *NN);
int ventana3 (void);

//////////////////////////// FUNCIONES //////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/// Capta los datos del archivo "dista.dat": N§ciudades, sus nombres
/// y las distancias de cada una de ‚stas a las otras.
/// Para rellenar el vector de estructura "ciudad" asignamos un puntero a
/// ‚ste llamado "pciudad" que es el que pasaremos como par metro a
/// esta funci¢n. "num" es una variable global que pasaremos por referencia
/// a la cu l ir  asociado el n§ de ciudades totales en nuestra matriz de
/// distancias.
/////////////////////////////////////////////////////////////////////////////
int capt_matr(struct tciudad *pciudad,int *num)
{
 int i,j;
 struct tciudad *posini; // "posini" nos indicar  el comienzo del vector de
 posini=pciudad;         // estructuras "ciudad[]" apuntado por "pciudad".

 if((fich=fopen(nom,"r"))==NULL)
 {
  printf("Error de apertura del archivo de distancias\n");
  getch();
  return -1;
 }

 fscanf(fich,"%d",num); // Capta el n§ de ciudades.

 for(i=0;i<*num;i++)
 {
  fscanf(fich,"%s",pciudad->nombre); // Capta los nombres.
  pciudad++;
 }

 pciudad=posini; // Volvemos a colocar pciudad al inicio de ciudad con posini.

 for(i=0;i<*num;i++)
 {                                            // Captamos cada una de las
  for(j=0;j<*num;j++)                         // distancias de cada ciudad
  fscanf(fich,"%d",&(pciudad->distancia[j])); // a ella misma (0) y a las
  pciudad++;                                  // dem s almacen ndolas en
 }                                            // el vector de la estructura
 fclose(fich);                                // "distancia[]".

 pciudad=posini;
 for(i=0;i<*num;i++)
 {
  for(j=0;j<2;j++)
  {
    if(j==0) pciudad->posx=coord[i][j];
    else pciudad->posy=coord[i][j];
  }
 pciudad++;
 }
 return 0;
}


/// Funci¢n que
///
///
/////////////////////////////////////////////////////////////////////////////
void sim_annel(int TABU[N],int TABU2[N],unsigned int *suma1)
{
  int i,n,tecla,k;
  unsigned int suma2;
  int sig = 30; /* significant digits */
  int sig2=3;
  char buffer[300],buffer2[1000];
  long int diff2_1,cont;
  long double PROBABILIDAD,T,Tmin,T_FACTOR;

  T=209200.0;
  T_FACTOR=0.87;
  Tmin=(3.0*pow10(-5));
  cont=0;
  PROBABILIDAD=0.0;

  fflush(stdout);
  cleardevice();
  setbkcolor(BLUE);

 while(T>Tmin)
 {
  if (kbhit())
  {
   tecla=getch();
  }

  if(tecla==27)
  {
   break;
  }

  PROBABILIDAD=0.0;
  for(k=0;k<30000;k++)
  {
    suma2=dist_revers(TABU,TABU2);

    if(suma2<=*suma1)
    {
     *suma1=suma2;

     for(n=0;n<NN;n++)  // Igualamos todos los elementos de TABU a los de TABU2.
     {
      *(TABU+n)=*(TABU2+n);
     }
    }

    else
    {
     diff2_1=suma2-*suma1;

     PROBABILIDAD=exp(-(diff2_1)/T);
     if(PROBABILIDAD>3.0*pow10(-4000))
     {

     *suma1=suma2;

     for(n=0;n<NN;n++)  // Igualamos todos los elementos de TABU a los de TABU2.
     {
      *(TABU+n)=*(TABU2+n);
     }
    }
   }
  }
   T*=T_FACTOR;

   cont++;                 // Para evitar parpadeos se hace un borrado y
   if(cont==6)           // una puesta en fondo azul de la pantalla por cada
   {                       // 400 iteraciones del bucle while,tras las cuales
    cleardevice();         // el contador de ciclos "cont"  se pone a cero.
    setbkcolor(BLUE);
    cont=0;
   }
   setcolor(4);
   if(*suma1>30000)
   {
    settextstyle(1,0,4);
    outtextxy(10,10,"Enfriando...");
    settextstyle(0,0,1);
   }

	setcolor(4);
	setcolor(4);
	outtextxy(30,387,"Distancia Total");
	rell_rect(163,385,219,396,10,1);
	outtextxy(170,387,itoa(*suma1,dist_TOUR,10));
	outtextxy(230,387,"Km");
	line(30,400,260,400);
	outtextxy(30,410,"LISTA DE ENFRIAMIENTO");
	outtextxy(34,427,"T¦");
	rell_rect(54,425,267,435,10,1);
	outtextxy(57,427,gcvt(T, sig,buffer));
	outtextxy(34,442,"áúT¦");
	rell_rect(70,439,267,449,10,1);
	outtextxy(73,441,gcvt(T*T_FACTOR, sig,buffer2));
	outtextxy(34,457,"á");
	rell_rect(54,454,100,466,10,1);
	outtextxy(59,457,gcvt(T_FACTOR,sig2,buffer));

	if(PROBABILIDAD!=0)
	{
	 outtextxy(305,442,"Probabilidad:");
	 rell_rect(410,437,609,450,10,1);
	 outtextxy(413,441,gcvt(PROBABILIDAD, sig,buffer2));
	}

   setcolor(12);
   traz_lineas();

   if(kbhit())
   {
   tecla=getch();
   if(tecla==13)
   for(;;)
   {
    if(kbhit())
    {
     tecla=getch();
     if((tecla==13)||(tecla==27))break;
    }

   }
   if(tecla==27)break;
  }


 }//FIN WHILE

    cleardevice();         // Terminado el c¢mputo de la mejor distancia se
    setcolor(12);          // resalta la ciudad por la que se ha comenzado
    i=TABU[0];             // el tour.
    outtextxy(ciudad[i].posx+5,ciudad[i].posy-3,ciudad[i].nombre);

   setbkcolor(BLUE);
   traz_lineas();
   marc_ciudades_selecc();
   setcolor(14);

   rell_rect(20,377, 270,470,2,1);
   setcolor(4);
   outtextxy(30,387,"Distancia Total");
   rell_rect(163,385,219,396,10,1);
   outtextxy(170,387,itoa(*suma1,dist_TOUR,10));
   outtextxy(230,387,"Km");
   line(30,400,260,400);
   outtextxy(30,410,"LISTA DE ENFRIAMIENTO");
   outtextxy(34,427,"T¦");
   rell_rect(54,425,267,435,10,1);
   outtextxy(57,427,gcvt(T, sig,buffer));
   outtextxy(34,442,"áúT¦");
   rell_rect(70,439,267,449,10,1);
   outtextxy(73,441,gcvt(T*T_FACTOR, sig,buffer2));

   outtextxy(34,457,"á");
   rell_rect(54,454,100,466,10,1);
   outtextxy(59,457,gcvt(T_FACTOR,sig2,buffer));


   rell_rect(303,437,621,452,2,1);
   outtextxy(305,442,"Probabilidad:");
   rell_rect(410,439,609,450,10,1);
   outtextxy(413,441,gcvt(PROBABILIDAD, sig,buffer2));
   fflush(stdout);

}

///
///
///
/////////////////////////////////////////////////////////////////////////////
unsigned int dist_revers(int TABU[N],int TABU2[N])
{

 int k1,k2,tabukk,i,j,n,pos1,pos2;
 unsigned int suma2;

 suma2=0;

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
  *(TABU2+n)=*(TABU+n);
 }

 *(TABU2+pos1)=k2;       //E insertamos en las posiciones pos1 y pos2 de TABU2
 *(TABU2+pos2)=k1;       //los valores k2 y k1 respectivamente que en TABU
		       //ocupaban las posiciones pos2 y pos1.
 n=0;

 do                       //Calcula la distancia de
 {                        //un tour completo por
   i=*(TABU2+n);            //las ciudades almacena-
   j=*(TABU2+(n+1));          //das en TABU2[].
   suma2+=(unsigned int)ciudad[i].distancia[j];
   n++;
  }while(n<NN-1);

 i=*(TABU2+(NN-1));
 j=*TABU2;
 suma2+=(unsigned int)ciudad[i].distancia[j];

 return suma2;
}

/////////////////////////////////////////////////////////////////////////////
/// "calc_dist" calcula la distancia de un tour completo a trav‚s de las
/// ciudades almacenadas en TABU[].
/////////////////////////////////////////////////////////////////////////////
void calc_dist(unsigned int *suma1)
{
 int n,i,j;

 n=0;
 do
 {
   i=TABU[n];
   j=TABU[n+1];
   suma1+=(unsigned int)ciudad[i].distancia[j];
   n++;
 }while(n<NN-1);                                  						   //

 i=TABU[NN-1];
 j=TABU[0];
 suma1+=(unsigned int)ciudad[i].distancia[j];
}


/////////////////////////////////////////////////////////////////////////////
/// "rell_TABU" rellena de forma aleatoria y completa el vector de ciudades
/// del recorrido, TABU[]. Se usa para aquellos casos en los que el usuario
/// decide elegir un tour que abarque todas las ciudades posibles a elegir.
void rell_TABU(int *NN)
{
 int tabuk,i,k,n,*P;

 P=TABU;

 for (n=0; n< N; n++)
 {
 *(P+n)=24;           // Hemos de inicializar todos los elementos de TABU[]
 }                    // a un valor comprendido entre 0 y 24

 n=0;

 do
 {                           ////////////////////////
  do                         //Busca un k no conte-//
  {                          //nido en TABU[].     //
   tabuk=0;                  ////////////////////////
   k=random(N);                                    //
   for(i=0; i<N;i++)                              //
   {                                               //
    if (k==*(TABU+i))tabuk++;                      //
   }                                               //
  }while(tabuk>=1);                                //
			     ////////////////////////
  *(TABU+(n+1))=k;           //Y lo va introducien-//
  n++;                       //do en TABU[] hasta  //
 }while(n<N-1);              //que ‚ste est‚ lleno.//
			     ////////////////////////

  *NN=N;

}




/////////////////////////////////////////////////////////////////////////////
		       //////// FUNCIONES GRAFICAS ////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/// Funci¢n que inicia el modo gr fico. En caso de no poder avisa con un
/// mensaje de error que muestra la posible causa que lo provoc¢.
///
/////////////////////////////////////////////////////////////////////////////
void inicia_graf()
{

 int gdriver = DETECT, gmode, errorcode;

 initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
 /* read result of initialization */
 errorcode = graphresult();
 if (errorcode != grOk)
 /* an error occurred */
 {
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
  /* terminate with an error code */
   exit(1);
 }
}
/////////////////////////////////////////////////////////////////////////////
/// Situa las 25 ciudades en la pantalla seg£n sus coordenadas en ‚sta ya
/// preestablecidas y almacenadas en la estructura ciudad. Tambi‚n coloca sus
/// nombres al lado de cada una.
/////////////////////////////////////////////////////////////////////////////
void coloc_ciudades(void)
{
 int i,j;
 setcolor(15);
 settextstyle(0,0,1);

 for (i=0;i<NN;i++)
 {

  j=TABU[i];
  outtextxy(ciudad[j].posx+5,ciudad[j].posy-3,ciudad[j].nombre);
  setcolor(12);
  circle(ciudad[j].posx,ciudad[j].posy,2);
 }
}
/////////////////////////////////////////////////////////////////////////////
/// Destaca los nombres de las ciudades en un color diferente al que fueron
/// situadas en la pantalla para indicar que han sido seleccionadas en el
/// tour que se desea recorrer.
/////////////////////////////////////////////////////////////////////////////
void marc_ciudades_selecc(void)
{
 int i,j;
 settextstyle(0,0,1);
 j=TABU[0];


 setcolor(12);
 outtextxy(ciudad[j].posx+5,ciudad[j].posy-3,ciudad[j].nombre);
 for (i=1;i<NN;i++)
 {
  setcolor(10);
  j=TABU[i];
  outtextxy(ciudad[j].posx+5,ciudad[j].posy-3,ciudad[j].nombre);
  setcolor(15);
  circle(ciudad[j].posx,ciudad[j].posy,2);
 }
}

/////////////////////////////////////////////////////////////////////////////
/// Funci¢n que emplea los valores de las coordenadas correspondientes a
/// las ciudades del recorrido calcalado para unirlas a trav‚s de l¡neas
/// y as¡ poder mostrar un tour completo de forma instant nea o final.
/////////////////////////////////////////////////////////////////////////////
void traz_lineas(void)
{
 int i,k;
 i=TABU[0];
 k=TABU[1];

 setcolor(12);
 outtextxy(ciudad[i].posx+5,ciudad[i].posy-3,ciudad[i].nombre);

 setcolor(9);

 // Trazado del primer arco desde la ciudad de origen almacenadad en TABU[0]
 line(ciudad[i].posx,ciudad[i].posy,ciudad[k].posx,ciudad[k].posy);

 //Unimos con sucesivos arcos dados por el orden de colocaci¢n de las ciudades
 //en TABU[]
 for(j=0;j<NN;j++)
 {
  i=TABU[j];
  lineto(ciudad[i].posx,ciudad[i].posy);
 }
 k=TABU[0];
 // Cerramos el recorrido enlazando la £ltima ciudad con la primera (TABU[0]).
 lineto(ciudad[k].posx,ciudad[k].posy);
}

/////////////////////////////////////////////////////////////////////////////
/// Rellena un rect ngulo de un determinado color y estilo. Aparte de estos
/// dos par metros recibe las coordenadas de su esquina superior izquierda
/// y su esquina inferior derecha.
/////////////////////////////////////////////////////////////////////////////
void rell_rect(int x1,int y1, int x2, int y2,int color,int stilo)
{
   int poli[10];

   poli[0] = x1;
   poli[1] = y1;

   poli[2] = x2;
   poli[3] = y1;

   poli[4] = x2;
   poli[5] = y2;

   poli[6] = x1;
   poli[7] = y2;

   poli[8] = poli[0];
   poli[9] = poli[1];

   setfillstyle(stilo,color);

   fillpoly(5, poli);
}

/////////////////////////////////////////////////////////////////////////////
/// Esta es la funci¢n correspondiente a la primera ventana del programa.
/// Devuelve el valor 1 o el 2, seg£n sea la opci¢n escogida.
/////////////////////////////////////////////////////////////////////////////
int ventana1 (void)
{
 int maxx = getmaxx();
 int maxy = getmaxy();
 int tecla;

 tecla=0;

 fflush(stdout);
 fflush(stdin);

 setbkcolor(BLACK);
 rell_rect(120,120,maxx-120,maxy-120,1,9);
 setcolor(YELLOW);
 circle(80,80,20);
 setcolor(RED);

 line(80,80,300,80);
 line(80,80,80,250);

 setcolor(WHITE);
 settextstyle(0,0,2);
 outtextxy(140,140,"  SELECCI¢N MODO RUTA");
 settextstyle(0,0,1);
 outtextxy(140,180,"1- Todas las ciudades");
 outtextxy(140,200,"2- Ciudades a elegir");

 setcolor(BLUE);
 rectangle(100,100, maxx-100, maxy-100);
 rectangle(120,120, maxx-120, maxy-120);

/* for(;;)
 {
  if(kbhit()) tecla=getch();
  if((tecla==49)||(tecla==50)||(tecla==27))
  {
   if(tecla=='1') return 1;
   else if(tecla=='2') return 2;

	else return 3;

  }
 }*/

 do
 {
  if(kbhit())
  {
   tecla=getch();
   if((tecla==49)||(tecla==50)||(tecla==27))break;
  }
 }while((tecla!=49)||(tecla!=50)||(tecla!=27));

 if(tecla==49)return 1;
 if(tecla==50)return 2;
 if(tecla==27)return 3;
}

/////////////////////////////////////////////////////////////////////////////
/// Esta ventana se abre si en "ventana1" seleccionamos el modo de ruta
/// correspondiente a "ciudades a elegir". Con ella es posible seleccionar
/// aquellas ciudades que se desee est‚n en nuestra ruta.
/////////////////////////////////////////////////////////////////////////////
int ventana1_2 (int TABU[N],int *NN)
{
 char cadena[3],*num,separador[3]="-";
 int maxx = getmaxx();
 int maxy = getmaxy();
 int tecla,tabu,city,i,j;

 fflush(stdout);
 fflush(stdin);

 for(i=0;i<N;i++) // Se igualan todos los elementos de TABU al valor -1
 {                // porque por defecto todos son cero, n£mero que podr¡a
  TABU[i]=-1;     // coincidir con el ¡ndice asociado a la ciudad 1.
 }


 rell_rect(140,40,maxx-140,maxy-40,1,9);  //////////////
 setcolor(YELLOW);                                    //  Marcos y relleno
 circle(110,10,5);                                    //  de recuadro interior
 setcolor(RED);                                       //  azulado.
						      //
 setcolor(BLUE);                                      //
 rectangle(120,20, maxx-120, maxy-20);                //
 rectangle(140,40, maxx-140, maxy-40);                //
 setcolor(RED);                                       //
 line(110,10,300,10);                                 //
 line(110,10,110,250); /////////////////////////////////

 setcolor(WHITE); //////////////////////////////////////
 settextstyle(0,0,2);                                 //  T¡tulos ventana1_2
 outtextxy(140,60," SELECCION DE CIUDADES");          //
 settextstyle(0,0,1);                                 //
 outtextxy(200,90,"(Pulsar N§ ciudad + INTRO)"); ///////

 setcolor(GREEN);
 outtextxy(160,119,"0-Fin recorrido"); // La opci¢n Fin Recorrido se destaca
				       // con color verde para diferenciarla
				       // de las dem s que corresponden a las
				       // ciudades.

 setcolor(YELLOW);       // Posicionamos los n£meros que van asociados a los
 outtextxy(160,139,"1"); // d¡gitos que habr n de teclearse para seleccionar
 outtextxy(160,162,"2"); // una ciudad.
 outtextxy(160,185,"3");
 outtextxy(160,208,"4");
 outtextxy(160,231,"5");
 outtextxy(160,254,"6");
 outtextxy(160,276,"7");
 outtextxy(160,300,"8");
 outtextxy(160,323,"9");
 outtextxy(152,346,"10");
 outtextxy(152,369,"11");
 outtextxy(152,392,"12");
 outtextxy(350,117,"13");
 outtextxy(350,141,"14");
 outtextxy(350,163,"15");
 outtextxy(350,186,"16");
 outtextxy(350,209,"17");
 outtextxy(350,232,"18");
 outtextxy(350,255,"19");
 outtextxy(350,278,"20");
 outtextxy(350,301,"21");
 outtextxy(350,324,"22");
 outtextxy(350,347,"23");
 outtextxy(350,370,"24");
 outtextxy(350,393,"25");



 setcolor(LIGHTGRAY);                        // Todas las ciudades no marcadas
 for(i=0;i<((int)(N/2));i++)                 // aparecen con color gris claro.
 {                                           // Aqu¡ se insertan las ciudades
  outtextxy(168,139+(23*i),separador);       // situadas en una primera colum-
  outtextxy(173,139+(23*i),ciudad[i].nombre);// na. Se va descendiendo en Y
 }                                           // cada 23 p¡xeles.

 j=0;// El contador j permite seguir un orden unitario creciente para as¡
     // establecer el correcto c¢mputo de las coordenadas verticales asociadas
     // a los nombres que ser n colocados en una segundo columna.
 for(i=((int)(N/2));i<N;i++) // A diferencia del bucle anterior, el contador i
 {                           // aqu¡ empleado s¢lo sirve para buscar el nombre
			     // correspondiente a la ciudad cuyo ¡ndice
			     // asociado nos da aqu‚l.
  outtextxy(365,117+(23*j),separador);
  outtextxy(370,117+(23*j),ciudad[i].nombre);
  j++;
 }

 rell_rect(285,410,309,428,0,1); // En este punto se introduce una peque¤a
				 // ventana donde se iran visualizando los
				 // d¡gitos que el usuario vaya introduciendo.
 setcolor(LIGHTGRAY);

 *NN=0;
 city=1;
 j=0;

 do // Este bucle permite introducir d¡gitos de valor 1 a N que corresponder n
 {  // con los ¡ndices asociados a las ciudades que el usuario seleccione.
  fflush(stdin);
  i=0;
  for(;;) // Bucle indefinido en el cual se capta un n£mero que podr  ser o no
  {       // v lido.
   fflush(stdin);
   tecla=getch();    // Se capta la tecla pulsada.

   if(tecla==27)break;

   if((tecla==8)&&(i>0)) //////////// 
   {                               //
    i--;  			   // Si pulsamos "RETROCESO" teniendo m s de
    cadena[i]='\0';                // un d¡gito en pantalla (i>0), se borrar 
    rell_rect(285,410,309,428,0,1);// con un relleno de rect ngulo toda el
    outtextxy(290,415,cadena);     //  rea reservada para la impresi¢n de
				   // aquellos. Autom ticamente  se pondr 
				   // el caracter '\0'en la £ltima posici¢n
				   // v lida de "cadena" que corresponder  con
     // el n£mero que se haya querido borrar y se mostrar  en pantalla s¢lo
     // la parte de cadena v lida que hasta ese momento tenemos.
   }

   if((tecla==13)&&(i!=0))break;
   // Para cualquier valor que halla en el el rect ngulo de inserci¢n de
   // d¡gitos exceptuando el caso en el que ‚ste no contenga nada, si se pulsa
   // "INTRO" se sale del bucle for(;;) para evaluar el n£mero introducido.

   else if((tecla>=48)&&(tecla<=57)) // En caso de introducir d¡gitos
   {
    if(i<2)                     // Si el n£mero actual de d¡gidos almacenados
    {                           // es menor que dos se a¤ade a cadena el
     cadena[i]=tecla;           // d¡gito introducido (pulsado) y se escribe
     cadena[i+1]='\0';          // autom ticamente en pantalla. El contador
     i++;                       // que capta el n£mero de d¡gitos introducidos
     setcolor(LIGHTGRAY);       // "i" se autoincrementa.
     outtextxy(290,415,cadena);
    }
    else                  // Si el n£mero de d¡gitos es mayor que 2
    {                     // se sale del bucle para la evaluaci¢n de todos
     i=0;                 // los caracteres num‚ricos introducidos hasta el
     break;               // momento menos el £ltimo pulsado.
    }
   }
  }//FIN FOR(;;)

  if(tecla==27)break;

  city=atoi(cadena); // Los d¡gitos tecleados que han sido almacenados en
		     // cadena son convertidos en un valor entero que ser 
		     // almacenado en la variable city para su posterior
		     // evaluaci¢n como ¡ndice v lido asociado a una ciudad
		     // candidata al tour.
  if((city==0)       // En caso de que el valor sea cero (valor fin recorrido)
    &&(*NN>1))break; // salimos del bucle y conservamos los ¡ndices que
		     // han sido seleccionados como v lidos para el tour hasta
		     // el momento.

  if((city>=1)&&(city<=25)) // En este punto comenzamos a seleccionar e intro-
  {                         // ducir en TABU[] ¡ndices v lidos que nos marquen
   tabu=0;                  // la ruta a realizar.
   for(i=0;i<N;i++)
   {
    if(TABU[i]==city-1)   // Comprueba que la ciudad que el ¡ndice no est‚ ya
    {                     // contenido en TABU[]. En caso de que lo encuentre
     tabu++;              // la variable centinela "tabu" se pone a uno.
    }
   }

   if(tabu==0)  // Si el valor del ¡ndice v lido no se encontro se procede a
   {            // su introducci¢n en TABU[].

    TABU[*NN]=city-1; // N¢tese aqu¡ que si p.e. tecleamos el valor 1 como
		      // ¡ndice asociado a la primera ciudad, el valor almace-
		      // nado en TABU[] ser  0, ya que este ser  el verdadero
		      // ¡ndice que dada la notaci¢n matricial se asignar  al
		      // primer elemento del vector de ciudades visitadas.
    (*NN)+=1; // NN,como variable que informa del total de ciudades visitadas,
	      // se autoincrementa cada vez que se capta un ¡ndice v lido.


    if (city<=((int)N/2)) // Estos dos "if" se emplean para destacar en color
    {                     // amarillo los nombres de las ciudades que son
     city-=1;             // seleccionadas. Se usa el mismo criterio de impre-
     setcolor(YELLOW);    // si¢n por columnas que fue utilizado al colocar
			  // todas las ciudades en la ventana de seleeci¢n de
			  // ciudades.
			  ///////////////////////////////
     outtextxy(173,139+(23*city),ciudad[city].nombre); //
     city+=1;                                          //
    }                                                  //
						       //
    j=0;                                               //
    if (city>((int)N/2))                               //
    {                                                  //
     city-=1;                                          //
     setcolor(YELLOW);                                 //
     for(i=((int)(N/2));i<city;i++)                    //
     {                                                 //
      j++;                                             //
     }                                                 //
     outtextxy(370,117+(23*j),ciudad[city].nombre);    //
     city+=1;                                          //
    }////////////////////////////////////////////////////
   }
  }
  rell_rect(285,410,309,428,0,1); // Cada vez que se rellene el rect ngulo de
				  // de inserci¢n de d¡gitos, sean ‚stos v li-
				  // dos o no, y se hayan evaluado se procede
				  // al borrado del mismo.
 }while((*NN<25)||(*NN<=1));

 fflush(stdout);
 fflush(stdin);
 if(tecla==27)return 1;
 else return 0;

}

/////////////////////////////////////////////////////////////////////////////
///
///
///
/////////////////////////////////////////////////////////////////////////////

int ventana3 (void)
{
 int maxx = getmaxx();
 int maxy = getmaxy();
 char tecla;

 fflush(stdout);
 fflush(stdin);

 setbkcolor(BLACK);
 rell_rect(120,120,maxx-120,maxy-250,1,9);
 setcolor(YELLOW);
 setcolor(YELLOW);
 circle(80,80,10);
 setcolor(RED);

 line(80,80,230,80);
 line(80,80,80,170);


 setcolor(WHITE);
 settextstyle(0,0,2);
 outtextxy(140,140," ¨SALIR DEL PROGRAMA?");
 settextstyle(0,0,1);
 outtextxy(140,180,"1- S¡.");
 outtextxy(140,200,"2- No (efectuar nuevo tour).");

 setcolor(BLUE);
 rectangle(100,100, maxx-100, maxy-225);
 rectangle(120,120, maxx-120, maxy-250);

 fflush(stdout);

 do
 {
  if(kbhit())
  {
   tecla=getch();
   if((tecla=='1')||(tecla=='2'))break;
  }
 }while((tecla!='1')||(tecla!='2'));

 if(tecla=='1')return 1;
 else if(tecla=='2')return 2;


}




/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////



void main(void)
{


 pciudad=ciudad;

 suma1=suma2=0.0;

 clrscr();

 if(capt_matr(ciudad,&num)==-1)
 {
  exit (0);
 }

 randomize();

 inicia_graf();

 control=1;

for(;;)
{
 switch (control)
 {
  case 1:{
	  fflush(stdin);
	  cleardevice();

	  fflush(stdin);
	  if(ventana1()==3)
	  {
	   control=3;
	   break;
	  }
	  if(ventana1()==2)
	  {
	   fflush(stdin);
	   cleardevice();
	   if(ventana1_2(TABU,&NN)==1)
	   {
	    fflush(stdin);
	    break;
	   }
	   fflush(stdin);
	  }
	  else if(ventana1()==1)
	  {
	   rell_TABU(&NN);
	  }
	  calc_dist(&suma1);
	  sim_annel(TABU,TABU2,&suma1);
	  getch();
	}
	control=3;
	break;

 case 3:{
	 fflush(stdin);
	 cleardevice();
	 if(ventana3()==1)
	 {
	  closegraph();
	  exit(0);
	 }

	 else
	 {
	  control=1;
	  fflush(stdin);
	 }
	}
	break;
 }
}

}
//2gitLIZ HURL.EY