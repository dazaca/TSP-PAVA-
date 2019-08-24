#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include <graphics.h>

#define N 25



char nom[]="a:dista.dat"; // Cadena que nos especificará la ruta del
                          // direcctorio desde el cual se leerá el fichero de
                          // distancias.

int NN,num,control;  // Las variables "NN" y "num" van asociadas al número de
                     // ciudades que serán escogidas en cada nuevo tour.
                     // "control" ser  empleada para informar en todo momento
                     // de cuál debe ser el orden en que se vayan ejecutando
                     // las distintas funciones principales del programa a
                     // través del flujo del mismo.

FILE *fich;   // Variable con la cual podremos acceder al fichero de
              // distancias.

unsigned int suma1; // Es la variable global cuyo valor iremos 
                    // modificando a través de distintas funciones,
                    // informando siempre del kilometraje total del
                    // recorrido que se vaya a seguir.

int TABU[N],TABU2[N]; // Vectores que contendrán los índices de las ciudades
                      // que han sido seleccionadas para efectuar un tour,
                      // donde "TABU2[]" es empleado de forma auxiliar en casos
                      // concretos para efectuar modificaciones sobre un "TABU[]".


// "coord[N][2]" es un array con un número de filas igual al total
// de ciudades candidatas a ser escogidas para realizar un tour.
// Cada índice fila se corresponde con el asociado a cada ciudad,
// donde su su correspondiente columna (bien sea la de índice 0 o 1) posee las
// coordenadas de la posición en la que ubicaremos cada ciudad en pantalla.

int coord[N][2]={{220,134},{572,379},{472,422},{172,346},{372,365},
                 {420,288},{320,144},{208,173},{492,298},{392,235},
                 {136,293},{176,192},{314,70},{80,134},{384,326},
                 {128,82},{540,365},{376,14},{236,206},{274,180},
                 {240,262},{292,125},{480,7},{520,197},{28,326}};


struct tciudad      // Esta estructura permite asignar a cada índice ciudad
{                   // varios parámetros característicos de éstas, como son
 int posx;          // sus coordenadas tanto horizontal (posx) como vertical
 int posy;          // (posy) en pantalla, el nombre de la ciudad, además de
 char nombre[30];   // la distancia de cada una de éstas a ella misma (0 por
 int distancia[25]; // defecto) y a las demás. Todo esto se almacena en
};                  // el vector de estructuras de nombre "ciudad" con un
                    // número de elementos igual al total de ciudades.

struct tciudad ciudad[N];
struct tciudad *pciudad; // Este puntero a estructura se emplerá para pasar
                         // parte de los datos del fichero de distancias al
                         // vector de estructuras "ciudad"; concretamente
                         // aquellos que se dan en la misma.



///////////////////////// PROTOTIPOS DE FUNCIONES ///////////////////////////
/////////////////////////////////////////////////////////////////////////////

void sim_annel(int TABU[N],int TABU2[N],unsigned int *suma1);
unsigned int dist_revers(int TABU[N], int TABU2[N]);
int capt_matr(struct tciudad *pciudad,int *num);
void calc_dist(unsigned int *suma1);
void rell_TABU(int *NN);

/////////////////// PROTOTIPOS FUNCIONES GRAFICAS ///////////////////////////
void inicia_graf(void);
void marc_ciudades_selecc(void);
void traz_lineas(void);
void rell_rect(int x1,int y1, int x2, int y2,int color, int stilo);
int ventana1 (void);
int ventana1_2(int TABU[N],int *NN);
int ventana3 (void);
void intro (void);

//////////////////////////// FUNCIONES //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/// Capta los datos del archivo "dista.dat": Nºciudades, sus nombres
/// y las distancias de cada una de éstas a las otras.
/// Para rellenar el vector de estructura "ciudad" asignamos un puntero a
/// éste llamado "pciudad" que es el que pasaremos como parámetro en
/// esta función. "num" es una variable global que pasaremos por referencia
/// a la cuál irá asociado el número de ciudades totales en nuestra matriz de
/// distancias.
/////////////////////////////////////////////////////////////////////////////
int capt_matr(struct tciudad *pciudad,int *num)
{
 int i,j;
 struct tciudad *posini; // "*posini" apunta al comienzo del vector de
 posini=pciudad;         // estructuras "ciudad[]", a su vez apuntado por
                         // "*pciudad".

 if((fich=fopen(nom,"r"))==NULL)  // Si no es posible abrir el fichero de
 {                                // distancias se genera un mensaje de error.
  printf("Error de apertura del archivo de distancias\n");
  getch();
  return -1;  // El valor -1 devuelto en este punto provoca el aborto del pro-
 }            // grama en el bloque principal del mismo.

 fscanf(fich,"%d",num); // Capta el nº de ciudades (por defecto almacenado en
                        // la primera línea del fichero de distancias).

 for(i=0;i<*num;i++)                 // En este bucle se captan los nombres
 {                                   // de las ciudades (por defecto almacenados
  fscanf(fich,"%s",pciudad->nombre); // en la segunda línea del fichero de
  pciudad++;                         // distancias).
 }

 pciudad=posini; // Volvemos a colocar el apuntador "*pciudad" al inicio de
                 // ciudad con posini.
 for(i=0;i<*num;i++)
 {                                            // Captamos las distancias
  for(j=0;j<*num;j++)                         // de cada ciudad a ella misma (0)
  fscanf(fich,"%d",&(pciudad->distancia[j])); // y a las demás, almacenándolas en
  pciudad++;                                  // el vector "distancia[]" de la
 }                                            // estructura "ciudad".
 fclose(fich);   // Una vez almacenados todos los datos del fichero de
                 // distancias en la estructura "ciudad" cerramos el fichero.



 pciudad=posini;  // Una vez más, y haciendo uso del puntero "*posini" situamos
                  // el apuntador "*pciudad" al comienzo de la estructura.

 for(i=0;i<*num;i++)  // En este bucle se introducen las coordenadas en pantalla
 {                    // de cada ciudad en los campos "posx" y "posy" de la es-
  for(j=0;j<2;j++)    // tructura "ciudad" a partir de los valores de la matriz
  {                   // "coord[][]" ya declarada y definida.

    if(j==0) pciudad->posx=coord[i][j];
    else pciudad->posy=coord[i][j];
  }
 pciudad++;
 }
 return 0;  // El valor cero es devuelto por defecto si el fichero de
}           // distancias a podido ser leido correctamente, y consecuentemente
            // se ha volcado toda su información a la estructura "ciudad".


///////////////////////////////////////////////////////////////////////////////
/// Función que recibe como parámetros la matriz "TABU[]" de ciudades escogidas
/// para un tour y su auxiliar "TABU2[]". También se le pasa la dirección de
/// la variable global "suma" a través de un puntero a la misma. Este paso por
/// valor nos permitirá modificar el valor de la variable mencionada en el
/// el ámbito de esta función. Además de implementarse el algoritmo conocido por
/// el término inglés "Simulated Annealing" para la resolución del problema a
/// a tratar, se efectuan de forma paralela las órdenes y funciones necesarias
/// para ir visualizando en pantalla la evolución del mismo.
///////////////////////////////////////////////////////////////////////////////
void sim_annel(int TABU[N],int TABU2[N],unsigned int *suma1)
{
  int i,n,tecla,k;    // Variables auxiliares empleadas en ciclos y contadores.
  unsigned int suma2; // Variable auxiliar empleada para comparar el valor
                      // obtenido en la distancia total de rutas alternativas
                      // a la de menor kilometraje dada por el valor de "suma1".
  int sig = 30; // Dígitos significativos empleados en las funciones de conver-
  int sig2=3;   // sión de valores valores numéricos a cadenas de caracteres.

  char buffer[300],buffer2[1000],dist_TOUR[7];  // Estas tres cadenas de carac-
  // teres también serán empleadas en las funciones de conversión de valores nu-
  // méricos a cadenas de caracteres.

  long int diff2_1,cont; // "diff2_1" es la variable donde se almacenará el
                         // valor de la diferencia de suma2 menos suma1
                         // empleado en la fórmula del cálculo de la probabili-
                         // dad.
  long double PROBABILIDAD,T,Tmin,T_FACTOR;
  // "PROBABILIDAD" es aquí la variable donde se almacenará la probabilidad
  // que es usada en el algoritmo para "retener" cambios efectuados en los arcos
  // de un recorrido con distancia asociada aparentemente elevada, y que según
  // el valor actual de la solución global (íntimamente ligado al de aquella)
  // será tenido en mayor o menor consideración. Las otras tres variables
  // corresponden a la lista de enfriamiento del algoritmo, donde "T" es la
  // temperatura, "Tmin" la temperatura mínima y "T_FACTOR" el factor multipli-
  // cativo responsable de la disminución de la temperatura, el cual se corres-
  // ponde con la constante de Boltzmann según la analogía aplicada al algoritmo
  // con el proceso físico del "enfriamiento simulado" empleado en las centrales
  // nucleares.
  T=209200.0;           // Definición de las variables que representan los
  T_FACTOR=0.87;        // los parámetros de la lista de enfriamiento.
  Tmin=(3.0*pow10(-5)); //
  cont=0;           // El contador "cont" se emplea para refrescar el contenido
                    // de la pantalla cada cierto número de iteraciones.



  PROBABILIDAD=0.0;
  fflush(stdout);   // Vaciado del buffer pantalla
  cleardevice();    // Borrado del contenido de pantalla
  setbkcolor(BLUE); // Puesta en azul del fondo de pantalla

 while(T>Tmin)     // Inicio del algoritmo "Simulated Annealing".
 {
  if (kbhit())tecla=getch(); // Si pulsamos la tecla ESCAPE se abortará
  if(tecla==27)break;        // el bucle while principal del algoritmo.

  PROBABILIDAD=0.0;
  for(k=0;k<30000;k++) // El valor máximo que puede alcanzar "k" corresponde
  {                    // con el número de comprobaciones de distancias alter-
                       // nativas que el algoritmo efectua a base de cambios
                       // por cada arco comprendidos entre dos ciudades
                       // de una ruta preestablecida (sólo en la primera pasada)
                       // o bien anteriormente modificada por cada variación
                       // que se efectua en "T".

    suma2=dist_revers(TABU,TABU2); // "suma_2" se iguala aquí al valor de una
                                   // distancia calculada a partir de una ruta
                                   // alternativa que se genera en la función
                                   // "dist_revers".

    if(suma2<=*suma1)  // Se compara la mejor solución obtenida hasta el momento
    {                  // (suma1) con la proporcionada por la función
     *suma1=suma2;     // "dist_revers" ("suma_2"). En caso de ser esta última
                       // mejor, se modifica el valor de "suma1" por la misma.

     for(n=0;n<NN;n++) // Igualamos todos los elementos de "TABU[]"
     {                 // a los de "TABU2[]".
      *(TABU+n)=*(TABU2+n);
     }
    }

    else    // En este bloque se efectúan posibles captaciones de
    {       // distancias con recorridos aparentemente "malos" (distancias
            // grandes), en función del estado actual de la probabilidad.

     diff2_1=suma2-*suma1;

     PROBABILIDAD=exp(-(diff2_1)/T); // Fórmula para el cálculo de la probabilidad.
     if(PROBABILIDAD>3.0*pow10(-4000))
     {
      *suma1=suma2;
      for(n=0;n<NN;n++)  // Igualamos todos los elementos de TABU a los de TABU2.
      {
       *(TABU+n)=*(TABU2+n);
      }
     }
    }
   }//FIN FOR

   T*=T_FACTOR;  // Reducimos la temperatura.

   cont++;             // Para evitar un exceso de información en pantalla, se
   if(cont==6)         // hace un borrado y puesta en fondo azul de la misma por
   {                   // cada 6 iteraciones del bucle while,tras las cuales
    cleardevice();     // el contador de ciclos "cont"  se pone a cero.
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

    setcolor(4);      // Puesta en pantalla de los parámetros de la lista de
                      // enfriamiento y de sus valores.

    outtextxy(30,387,"Distancia Total");
    rell_rect(163,385,219,396,10,1);
    outtextxy(170,387,itoa(*suma1,dist_TOUR,10));
    outtextxy(230,387,"Km");
    line(30,400,260,400);
    outtextxy(30,410,"LISTA DE ENFRIAMIENTO");
    outtextxy(34,427,"T:");
    rell_rect(54,425,267,435,10,1);
    outtextxy(57,427,gcvt(T, sig,buffer));
    outtextxy(34,442,"ß*T:");
    rell_rect(70,439,267,449,10,1);
    outtextxy(73,441,gcvt(T*T_FACTOR, sig,buffer2));
    outtextxy(34,457,"ß");
    rell_rect(54,454,100,466,10,1);
    outtextxy(59,457,gcvt(T_FACTOR,sig2,buffer));

    if(PROBABILIDAD!=0)  // El valor de la probabilidad se imprimirá en pantalla
    {                    // sólo cuando sea distinto de cero.

     outtextxy(305,442,"Probabilidad:");
     rell_rect(410,437,609,450,10,1);
     outtextxy(413,441,gcvt(PROBABILIDAD, sig,buffer2));
    }

   setcolor(12);
   traz_lineas(); // LLamamos a la función "traz_lineas" que nos permite visua-
                  // lizar en pantalla el recorrido de un tour por las ciudades
                  // seleccionadas.
   if(kbhit())     // Esta condición se empleaa en caso de pulsar la tecla
   {               // INTRO; de esta forma el flujo del programa se detendrá
    tecla=getch(); // hasta no no vuelva a pulsarse de nuevo la misma tecla
    if(tecla==13)  // o bien ESCAPE.
    for(;;)
    {
     if(kbhit())
     {
      tecla=getch();
      if((tecla==13)||(tecla==27))break;
     }
    }
    if(tecla==27)break; // En caso de pulsar ESC, bien desde el punto de parada
   }                    // o bien en cualquier instante en el que el algoritmo
                        // esté iterando, se producirá una ruptura en del
                        // bucle while y se producirá una interupción automática-
 }//FIN WHILE           // mente en éste.

    cleardevice();      // Terminado el cómputo de la mejor distancia se
    setcolor(12);       // resalta la ciudad por la que se ha comenzado
    i=TABU[0];          // el tour.
    outtextxy(ciudad[i].posx+5,ciudad[i].posy-3,ciudad[i].nombre);



   setbkcolor(BLUE);       // Se hace un último trazado de la mejor ruta encon-
   traz_lineas();          // trada una vez finalizada la búsqueda de distancias
   marc_ciudades_selecc(); // tras una puesta en azul de la pantalla. La función
   setcolor(14);           // "marc_ciudades_selecc()" nos permitirá ver los nom-
                           // bres de las ciudades que se han escogido para el
                           // recorrido, aparte de localizarlas en pantalla con
                           // un pequeño círculo de centro la coordena asociada
                           // a cada una de aquellas.

   rell_rect(20,377, 270,470,2,1);      // Al finalizar el algoritmo resaltamos
   setcolor(4);                         // con cuadradados de fondo verde los
   outtextxy(30,387,"Distancia Total"); // parámetros de la lista de enfriamien-
   rell_rect(163,385,219,396,10,1);     // to con sus correspondientes valores y
   outtextxy(170,387,itoa(*suma1,dist_TOUR,10));      // casillas de almacenaje.
   outtextxy(230,387,"Km");
   line(30,400,260,400);
   outtextxy(30,410,"LISTA DE ENFRIAMIENTO");
   outtextxy(34,427,"T:");
   rell_rect(54,425,267,435,10,1);
   outtextxy(57,427,gcvt(T, sig,buffer));
   outtextxy(34,442,"ß*T:");
   rell_rect(70,439,267,449,10,1);
   outtextxy(73,441,gcvt(T*T_FACTOR, sig,buffer2));

   outtextxy(34,457,"ß");
   rell_rect(54,454,100,466,10,1);
   outtextxy(59,457,gcvt(T_FACTOR,sig2,buffer));


   rell_rect(303,437,621,452,2,1);    // Por último se imprime el valor de la
   outtextxy(305,442,"Probabilidad:");// probabilidad (siempre cero al final de cada
   rell_rect(410,439,609,450,10,1);   // evaluación por defecto).
   outtextxy(413,441,gcvt(PROBABILIDAD, sig,buffer2));
   fflush(stdout);

}

/////////////////////////////////////////////////////////////////////////////
/// Esta es la función empleada dentro de "sim_annel()" que permite efectuar
/// transmormaciones locales del recorrido con mejor distancia encontrado hasta
/// el momento, a partir de cambios realizados con cada arco asociados a
/// cada dos ciudades.
/////////////////////////////////////////////////////////////////////////////
unsigned int dist_revers(int TABU[N],int TABU2[N])
{
 int k1,k2,tabukk,i,j,n,pos1,pos2;
 unsigned int suma2;
 suma2=0;
 do                       // En este bucle se procede a la búsqueda del primer índice
 {                        // válido de ciudades que estén en el recorrido (por
   pos1=0;                // tanto estén en "TABU[]") con el cual se efectuará
   tabukk=0;              // un cambio de arco. En caso de no encontarlo, la
   k1=random(N);          // variable "tabukk" se autoincrementa informándonos
                          // con ello posteriormente de que dicho índice no es
   for(n=0; n<=(NN-1);n++)// apto para efectuar el cambio local en el recorrido
   {                      // total dado por todos los índices de "TABU[]".
    if (k1==TABU[n])
    {
     tabukk++;
     break;
    }
    if(!tabukk) pos1++;   // "pos1" será la posición de la 1ª ciudad de las dos
   }                      // en "TABU[]" a partir de las cuales se calcula una
 }while(!tabukk);         // nueva distancia. Sólo se autoincrementa si se ha
                          // encontrado un índice válido ("tabukk"=0).
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
 {                    //...
  *(TABU2+n)=*(TABU+n);
 }
 *(TABU2+pos1)=k2;// ...e insertamos en las posiciones "pos1" y "pos2" de "TABU2[]"
 *(TABU2+pos2)=k1;// los valores "k2" y "k1" respectivamente que en TABU
                  //ocupaban las posiciones dadas por "pos2" y "pos1".
 n=0;
 do                   // Calcula la distancia de un tour completo por las
 {                    // ciuadades almacenadas en "TABU2[]" y lo almacena en
   i=*(TABU2+n);      // en "suma2".
   j=*(TABU2+(n+1));
   suma2+=(unsigned int)ciudad[i].distancia[j];
   n++;
 }while(n<NN-1);
 i=*(TABU2+(NN-1));   // Aquí termina el cálculo de un tour completo añadiéndose
 j=*TABU2;            // la distancia del arco de cierre del tour dado por la
 suma2+=(unsigned int)ciudad[i].distancia[j];  // ciudad de origen y la última
 return suma2;                                 //  visitada.
}

/////////////////////////////////////////////////////////////////////////////
/// "calc_dist" calcula la distancia de un tour completo a través de las
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
 }while(n<NN-1);
 i=TABU[NN-1];
 j=TABU[0];
 suma1+=(unsigned int)ciudad[i].distancia[j];
}


/////////////////////////////////////////////////////////////////////////////
/// "rell_TABU" rellena de forma aleatoria y completa el vector de ciudades
/// del recorrido, TABU[]. Se usa para aquellos casos en los que el usuario
/// decide elegir un tour que abarque todas las ciudades posibles a elegir.
/////////////////////////////////////////////////////////////////////////////
void rell_TABU(int *NN)
{
 int tabuk,i,k,n,*P;
 P=TABU;
 for (n=0; n< N; n++)
 {
 *(P+n)=24;           // Hemos de inicializar todos los elementos de TABU[]
 }                    // a un valor comprendido entre 0 y 24. El no hacerlo
                      // podría provocar fallos en el programa si el usuario
                      // decidiera ejecutar más de una vez la opción de un tour
                      // completo por todas las ciudades posibles.
 n=0;
 do
 {
  do                  //Busca un k no contenido en TABU[]...
   tabuk=0;
   k=random(N);
   for(i=0; i<N;i++)
   {
    if (k==*(TABU+i))tabuk++;
   }
  }while(tabuk>=1);

   *(TABU+(n+1))=k;   //Y lo va introduciendo en "TABU[]" hasta que éste se llene.
   n++;
 }while(n<N-1);
 *NN=N;
}


/////////////////////////////////////////////////////////////////////////////
		   //////// FUNCIONES GRÁFICAS ////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/// Función que inicia el modo gráfico. En caso de no poder avisa con un
/// mensaje de error que muestra la posible causa que lo provocó.
//////////////////////////////////////////////////////////////////////////////
void inicia_graf()
{

 int gdriver = DETECT, gmode, errorcode;

 initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

 errorcode = graphresult();   // Lee el resultado de la inicialización.
 if (errorcode != grOk)       // En caso de error termina el programa
 {                            // emitiendo antes un código de error.

   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
 }
}


/////////////////////////////////////////////////////////////////////////////
/// Destaca los nombres de las ciudades a color en la pantalla para indicar
/// que han sido seleccionadas en el tour que se desea recorrer.
/////////////////////////////////////////////////////////////////////////////
void marc_ciudades_selecc(void)
{
 int i,j;
 settextstyle(0,0,1);  // Aquí se hace uso de la información relativa a cada
 j=TABU[0];            // ciudad almacenada en la estructura "ciudad"; concré-
 setcolor(12);         // tamente del las coordenadas en pantalla y el nombre
		       // de cada una de ellas.
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
/// Función que emplea los valores de las coordenadas correspondientes a
/// las ciudades del recorrido calculado para unirlas a través de líneas
/// y así poder mostrar un tour completo de forma instantánea o final.
/////////////////////////////////////////////////////////////////////////////
void traz_lineas(void)
{
 int i,j,k;
 i=TABU[0];
 k=TABU[1];

 setcolor(12); // Impresión de la ciudad de partida en color rojo suavizado.
 outtextxy(ciudad[i].posx+5,ciudad[i].posy-3,ciudad[i].nombre);

 setcolor(9);

 // Trazado del primer arco desde la ciudad de origen almacenadad en TABU[0]
 line(ciudad[i].posx,ciudad[i].posy,ciudad[k].posx,ciudad[k].posy);

 //Unimos el recorrido con sucesivos arcos dados por el orden de colocación de
 // las ciudades cuyos índices asociados se almacenaron en "TABU[]".
 for(j=0;j<NN;j++)
 {
  i=TABU[j];
  lineto(ciudad[i].posx,ciudad[i].posy);
 }
 k=TABU[0];
 // Cerramos el recorrido enlazando la última ciudad con la primera (TABU[0]).
 lineto(ciudad[k].posx,ciudad[k].posy);

}

/////////////////////////////////////////////////////////////////////////////
/// Rellena un rectángulo de un determinado color y estilo. Aparte de estos
/// dos parámetros recibe las coordenadas de su esquina superior izquierda
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
/// Esta es la función correspondiente a la primera ventana del programa.
/// Devuelve el valor 1 o el 2, según sea la opción escogida.
/////////////////////////////////////////////////////////////////////////////
int ventana1 (void)
{
 int maxx = getmaxx();
 int maxy = getmaxy();
 char tecla;

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
 outtextxy(140,140,"  SELECCIóN MODO RUTA");
 settextstyle(0,0,1);
 outtextxy(140,180,"1- Todas las ciudades");
 outtextxy(140,200,"2- Ciudades a elegir");

 setcolor(BLUE);
 rectangle(100,100, maxx-100, maxy-100);
 rectangle(120,120, maxx-120, maxy-120);

 for(;;)                          // Si la tecla pulsada es 1 la función devolverá
 {                                // este mismo valor, que luego emplearemos para
  if(kbhit()) tecla=getch();      // que la variable global "control" haga uso
  if((tecla=='1')||(tecla=='2'))  // de la misma y vaya redirigiendo el flujo
  {                               // del programa según sea. Idem si la tecla
   if(tecla=='1') return 1;       // pulsada es 2, pero haciendo que se devuelva
   else return 2;                 // este mismo valor.
  }
 }
 fflush(stdout);
 fflush(stdin);
}

/////////////////////////////////////////////////////////////////////////////
/// Esta ventana se abre si en "ventana1" seleccionamos el modo de ruta
/// correspondiente a "ciudades a elegir" (pulsado tecla 1). Con ella es
/// posible seleccionar aquellas ciudades que deseamos estén en nuestra ruta.
/////////////////////////////////////////////////////////////////////////////
int ventana1_2 (int TABU[N],int *NN)
{
 char cadena[3],*num,separador[3]="-";
 int maxx = getmaxx();
 int maxy = getmaxy();
 int tecla,tabu,city,i,j;

 fflush(stdout);
 fflush(stdin);








 for(i=0;i<N;i++) // Se igualan todos los elementos de "TABU[]" al valor -1
 {                // porque por defecto todos son cero, número que sería
  TABU[i]=-1;     // reconocido como el índice asociado a la ciudad 1.
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
 settextstyle(0,0,2);                                 //  Títulos "ventana1_2"
 outtextxy(140,60," SELECCION DE CIUDADES");          //
 settextstyle(0,0,1);                                 //
 outtextxy(200,90,"(Pulsar N§ ciudad + INTRO)"); ///////

 setcolor(GREEN);
 outtextxy(160,119,"0-Fin recorrido"); // La opción Fin Recorrido se destaca
                                       // con color verde para diferenciarla
                                       // de las demás, que corresponden a las
                                       // ciudades.

 setcolor(YELLOW);       // Posicionamos los números que van asociados a los
 outtextxy(160,139,"1"); // dígitos que habrán de teclearse para seleccionar
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
 {                                           // Aquí se insertan las ciudades
  outtextxy(168,139+(23*i),separador);       // situadas en una primera colum-
  outtextxy(173,139+(23*i),ciudad[i].nombre);// na. Se va descendiendo en Y
 }                                           // cada 23 píxeles.

 j=0;// El contador j permite seguir un orden unitario creciente para así
     // establecer el correcto cómputo de las coordenadas verticales asociadas
     // a los nombres que serán colocados en pantalla en una segunda columna.

 for(i=((int)(N/2));i<N;i++) // A diferencia del bucle anterior, el contador i
 {                           // aquí empleado sólo sirve para buscar el nombre
			     // correspondiente a la ciudad cuyo índice
			     // asociado nos da aquí j.
  outtextxy(365,117+(23*j),separador);         // Colocamos el separador...
  outtextxy(370,117+(23*j),ciudad[i].nombre);  // ...seguido del nombre.
  j++;
 }

 rell_rect(285,410,309,428,0,1); // En este punto se introduce una pequeña
                                 // ventana donde se irán visualizando los
                                 // dígitos que el usuario vaya introduciendo.
 setcolor(LIGHTGRAY);

 *NN=0;
 city=1;
 j=0;
 do // Este bucle permite introducir dígitos de valor 1 a N que corresponder
 {  // con los índices asociados a las ciudades que el usuario seleccione.
  fflush(stdin);
  i=0;
  for(;;) // Bucle indefinido en el cual se capta un número que podrá ser o no
  {       // válido.
   fflush(stdin);
   tecla=getch();    // Se capta la tecla pulsada.
   if(tecla==27)break;
   if((tecla==8)&&(i>0))
   {
    i--;                           // Si pulsamos "RETROCESO" teniendo más de
    cadena[i]='\0';                // un dígito en pantalla (i>0), se borrará
    rell_rect(285,410,309,428,0,1);// con un relleno negro de rectángulo toda el
    outtextxy(290,415,cadena);     // área reservada para la impresión de
                                   // aquellos. Automáticamente  se pondrá
                                   // el caracter '\0'en la última posición
                                   // válida de "cadena" que corresponderá con
        // el número que se haya querido borrar y se mostrará en pantalla sólo
        // la parte de cadena válida que hasta ese momento tenemos.
   }
   if((tecla==13)&&(i!=0))break;
   // Para cualquier valor que halla en el el rectángulo de inserción de
   // dígitos exceptuando el caso en el que éste no contenga nada, si se pulsa
   // "INTRO" se sale del bucle for(;;) para evaluar el número introducido.

   else if((tecla>=48)&&(tecla<=57)) // En caso de introducir dígitos
   {
    if(i<2)                     // Si el número actual de dígidos almacenados
    {                           // es menor que dos, se añade a cadena el
     cadena[i]=tecla;           // dígito introducido (pulsado) y se escribe
     cadena[i+1]='\0';          // automáticamente en pantalla. El contador
     i++;                       // que capta el número de dígitos introducidos
     setcolor(LIGHTGRAY);       // "i" se autoincrementa.
     outtextxy(290,415,cadena);
    }
    else                  // Si el número de dígitos es mayor que 2
    {                     // se sale del bucle para la evaluación de todos
     i=0;                 // los caracteres numéricos introducidos hasta el
     break;               // momento menos el último pulsado.
    }
   }
  }//FIN FOR(;;)

  if(tecla==27)break;  // La opción de abandonar el menú que se genera en esta
                       // función es posible gracias a esta condición, que tras
                       // producir una ruptura en la ejecución de la misma tam-
                       // bién será responsable de modificar el valor que devuelva
                       // aquella para posteriormente redirigir el flujo del
                       // programa a la primera ventana.
  city=atoi(cadena); // Los dígitos tecleados que han sido almacenados en
                     // cadena son convertidos en un valor entero que será
                     // almacenado en la variable "city" para su posterior
                     // evaluación como posible índice válido asociado a una ciudad
                     // candidata al a ser esgogida para un tour.

  if((city==0)       // En caso de que el valor sea cero (valor fin recorrido)
    &&(*NN>1))break; // salimos del bucle y conservamos los índices que
                     // han sido seleccionados como válidos para el tour hasta
                     // el momento.

  if((city>=1)&&(city<=25)) // En este punto comenzamos a seleccionar e intro-
  {                         // ducir en "TABU[]" índices válidos que nos marquen
   tabu=0;                  // la ruta a realizar.
   for(i=0;i<N;i++)
   {
    if(TABU[i]==city-1)   // Comprueba que el índice de la ciudad no esté ya
    {                     // contenido en TABU[]. En caso de que lo encuentre
     tabu++;              // la variable centinela "tabu" se pone a uno.
    }
   }

   if(tabu==0)  // Si el valor del índice válido no se encontró se procede a
   {            // su introducción en TABU[].

    TABU[*NN]=city-1; // Nótese aquí que si p.e. tecleamos el valor 1 como
                      // índice asociado a la primera ciudad, el valor almace-
                      // nado en TABU[] será 0, ya que este es el verdadero
                      // índice que dada la notación matricial se asigna al
		      // primer elemento del vector de ciudades visitadas.

    (*NN)+=1; // "NN",como variable que informa del total de ciudades visitadas,
	          // se autoincrementa cada vez que se capta un índice válido.

    if (city<=((int)N/2)) // Estos dos "if" se emplean para destacar en color
    {                     // amarillo los nombres de las ciudades que son
     city-=1;             // seleccionadas. Se usa el mismo criterio de impre-
     setcolor(YELLOW);    // sión por columnas que fue utilizado al colocar
                          // todas las ciudades en la ventana de seleeción de
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
  rell_rect(285,410,309,428,0,1); // Cada vez que se rellene el rectángulo de
                                  // de inserción de dígitos, sean éstos váli-
                                  // dos o no, y una vez evaluados, se procede
                                  // al borrado del mismo.
 }while((*NN<25)||(*NN<=1)); // En caso de haberse seleccionado las 25 ciudades
                             // salimos del bucle.
 fflush(stdout);
 fflush(stdin);
 if(tecla==27)return 1;
 else return 0;

}

/////////////////////////////////////////////////////////////////////////////
///  Esta función corresponde con la última ventana en la cual se ofrece la
///  posibilidad de salir del programa, o bien ir de nuevo a la ventana de
///  "Modo Ruta".
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
/// Ventana que muestra recuadrado el título de la la introducción al programa.
/////////////////////////////////////////////////////////////////////////////
void intro(void)
{
 fflush(stdout);
 setbkcolor(BLACK);
 setcolor(YELLOW);
 rectangle(10, 10, getmaxx()-10, getmaxy()-10);
 rectangle(15, 15, getmaxx()-15, getmaxy()-15);
 settextstyle(1,0,10);
 outtextxy(150,50,"PAVA");
 settextstyle(1,0,3);
 outtextxy(100,180,"(Problema del Agente Viajero A‚reo)");
 settextstyle(1,0,1);
 outtextxy(100,420,"Implementado con \"SIMULATED ANNEALING\"");
 fflush(stdout);
 getch();
}

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void main(void)
{
 pciudad=ciudad;
 suma1=0;
 clrscr();
 if(capt_matr(ciudad,&num)==-1)
 {
  exit (0);
 }
 randomize();
 inicia_graf();
 intro();
 control=1;
 for(;;)
 {
  switch (control)    // "control" determina el flujo del programa nutriéndose
  {                   // en todo momento de los valores devueltos por las dis-
   case 1:{           // tintas funciones principales.
           fflush(stdin);
           cleardevice();
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
           else
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
