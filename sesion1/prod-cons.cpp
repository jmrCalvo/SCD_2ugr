// *****************************************************************************
//
// Prácticas de SCD. Práctica 1.
// Plantilla de código para el ejercicio del productor-consumidor con
// buffer intermedio.
//
// *****************************************************************************

#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // necesario para {\ttbf usleep()}
#include <stdlib.h> // necesario para {\ttbf random()}, {\ttbf srandom()}
#include <time.h>   // necesario para {\ttbf time()}

using namespace std ;

// ---------------------------------------------------------------------
// constantes configurables:

const unsigned
  num_items  = 40 ,    // numero total de items que se producen o consumen
  tam_vector = 10 ;    // tamaño del vector, debe ser menor que el número de items

  int V[tam_vector];
 sem_t productor;
 sem_t consumidos;
// ---------------------------------------------------------------------
// introduce un retraso aleatorio de duración comprendida entre
// 'smin' y 'smax' (dados en segundos)

void retraso_aleatorio( const float smin, const float smax )
{
  static bool primera = true ;
  if ( primera )        // si es la primera vez:
  {  srand(time(NULL)); //   inicializar la semilla del generador
     primera = false ;  //   no repetir la inicialización
  }
  // calcular un número de segundos aleatorio, entre {\ttbf smin} y {\ttbf smax}
  const float tsec = smin+(smax-smin)*((float)random()/(float)RAND_MAX);
  // dormir la hebra (los segundos se pasan a microsegundos, multiplicándos por 1 millón)
  usleep( (useconds_t) (tsec*1000000.0)  );
}

// ---------------------------------------------------------------------
// función que simula la producción de un dato

unsigned producir_dato()
{
  static int contador = 0 ;
  contador = contador + 1 ;
  retraso_aleatorio( 0.1, 0.5 );
  cout << "Productor : dato producido: " << contador << endl << flush ;
  return contador ;
}
// ---------------------------------------------------------------------
// función que simula la consumición de un dato

void consumir_dato( int dato )
{
   retraso_aleatorio( 0.1, 1.5 );
   cout << "Consumidor:  dato consumido: " << dato << endl << flush ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del productor

void * funcion_productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato = producir_dato() ;

    // falta aquí: insertar "dato" en el vector o buffer
    		sem_wait(&funcion_consumidor);
    		
    			V[i%tam_vector]=dato
    		
    		sem_post(&funcion_consumidor);
    // ................
    
    cout << "Productor : dato insertado: " << dato << endl << flush ;
  }
  return NULL ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del consumidor

void * funcion_consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato ;

    // falta aquí: leer "dato" desde el vector intermedio
  	sem_wait( &funcion_productor );
  		dato=V[i%tam_vector]
 	sem_post( &funcion_productor); 
    // .................
    cout << "Consumidor:  dato extraído : " << dato << endl << flush ;
    consumir_dato( dato ) ;
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{

  // falta: crear y poner en marcha las hebras, esperar que terminen
 	sem_init( &funcion_productor, 0, 10 );
 	sem_init( &funcion_consumido, 0, 0 );
 
  pthread_t hebra1, hebra2 ;
  pthread_create(&hebra1,NULL,funcion_productor,NULL);
  pthread_create(&hebra2,NULL,funcion_consumidor,NULL);
  
   pthread_join( hebra1, NULL );
   pthread_join( hebra2, NULL );
  
  sem_destroy( &productor );
  sem_destroy( &consumidor );
  
  // ....

   return 0 ;
}
