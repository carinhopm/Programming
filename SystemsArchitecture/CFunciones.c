#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CFunciones.h"
#include "CLista.h"

void liberar_lista()
{
   int inicio;
   int cont;
   cont=tamanio_lista();
   for(inicio=0; inicio<cont; inicio++)
   {
       suprimir_inicio();
   }
}

void salir_programa(int numero)
{
   int eleccion;
   if(numero==-1)
   {
       puts("¿Quiere guardar la lista?. Pulse 1 si quiere guardar la lista");
       eleccion=pedir_numero_iter();
       if(eleccion==1)
       {
	   char *nom;
	   puts("Introduzca el nombre del fichero");
	   nom=leer_cadena();
	   exportar(nom);
	   free(nom);
       }
       liberar_lista();
       puts("-Fin del programa-\n");
       exit(0); 
   }
}

int localizar_identificador(int posicion)
{
   int resultado;
   int inicio;
   struct lista *auxiliar;
   auxiliar=primero;
   for(inicio=1; inicio<posicion; inicio++)
   {
       auxiliar=auxiliar->siguiente;
   }
   resultado=auxiliar->identificador;
   return resultado;
}

void suprimir_campos(int identif)
{
   struct lista *auxiliar;
   auxiliar=primero;
   while(auxiliar!=NULL)
   {
       if(auxiliar->identificador==identif)
       {
	   free(auxiliar->titulo);
	   free(auxiliar->fuente);
	   free(auxiliar->autores);
	   if(auxiliar->tipo==CONFERENCIA)
	   {
	       free(auxiliar->confe.lugar);
	   }
	   else
	   {
	       free(auxiliar->arti.volumen);
	   }
       }
       auxiliar=auxiliar->siguiente;
   } 
}

void suprimir_campos_inicio()
{
   struct lista *auxiliar;
   auxiliar=primero;
   free(auxiliar->titulo);
   free(auxiliar->fuente);
   free(auxiliar->autores);
   if(auxiliar->tipo==CONFERENCIA)
   {
       free(auxiliar->confe.lugar);
   }
   else
   {
       free(auxiliar->arti.volumen);
   }
} 

void suprimir_inicio()
{
   struct lista *actual;
   struct lista *previo;
   previo=primero;
   if(previo==NULL)
   {
       return;
   }
   actual=previo->siguiente;
   if(actual==NULL)
   {
       suprimir_campos_inicio();
       free(previo); 
       primero = (struct lista *) NULL;
       puts("Lista vacía");
       return;
   }
   suprimir_campos_inicio();
   primero=actual;
   free(previo);
   return;
}

int tamanio_lista()
{
   int contador=0;
   struct lista *tamanio;
   tamanio=primero;
   while(tamanio!=NULL)
   {
       contador++;                                   
       tamanio=tamanio->siguiente;
   }
   return contador;
}
 
void suprimir_en_lista (int identif)
{  
   int encontrado=0;
   struct lista *actual;
   struct lista *previo;
   actual = primero;
   while(actual!=NULL)
   {
       if(actual->identificador==identif)
       {
	   suprimir_campos(identif);
	   puts("Elemento encontrado...");
	   puts("Elemento borrado");
	   if(actual==primero)
	   {
	       if(actual->siguiente==NULL)
	       {
		   previo=actual;
		   free(previo);
		   primero = (struct lista *) NULL;
		   encontrado=1;
		   break;
	       }
	       previo=actual;
	       actual=actual->siguiente;
	       primero=actual;
	       previo->siguiente=NULL;
	       free(previo);
	   }
	   else 
	   {
	       actual = previo;
	       previo = previo->siguiente;
	       actual->siguiente = actual->siguiente->siguiente;
	       previo->siguiente=NULL;
	       free (previo);
	   }
	   encontrado=1;
       }
       previo=actual;
       actual = actual->siguiente;
   }
   if (encontrado==0)
   {
       printf( "\nNo se ha encontrado la publicación por esa ID\n" );
   }
}
 
void mostrar_lista_completa() 
{
   struct lista *auxiliar;
   int i=1;
   auxiliar = primero;
   printf("\nMostrando la lista completa:\n");
   while (auxiliar!=NULL) 
   {
       printf("Elemento %d de la lista:\n\n",i);
       printf("Identificador(ID): %d\n-Titulo del artículo: %.30s\n-Año de la publicación: %d\n",
       auxiliar->identificador,auxiliar->titulo,auxiliar->anio);
       puts("----------------------------------------------\n");
       auxiliar=auxiliar->siguiente;
       i++;
   }
   if (i==1)
   {
       printf( "\nLa lista está vacía\n" );
   }
}

void mostrar_lista(int identif) 
{
   struct lista *auxiliar;
   auxiliar = primero;
   int encontrado=0;
   while (auxiliar!=NULL) 
   {
       if(auxiliar->identificador==identif)
       {
	   puts("\nMostrando la referencia:");
           printf("\nIdentificador(ID): %d\n-Tipo de artículo: %s\n-Titulo del artículo: %s\n-Nombre de la fuente: %s\n-Autores: %s\n-Año de la publicación: %d\n-ISSN: %d\n",
           auxiliar->identificador,mostrar_tipo(auxiliar->tipo),auxiliar->titulo,auxiliar->fuente,auxiliar->autores,auxiliar->anio,auxiliar->issn);
	   if(auxiliar->tipo==CONFERENCIA)
	   {
	       printf("-Lugar de la conferencia: %s\n",auxiliar->confe.lugar); 
	   }
	   else if(auxiliar->tipo==ARTICULO)
	   {
	       printf("-Volumen del artículo: %s\n-Número de revista: %d\n\n",auxiliar->arti.volumen,auxiliar->arti.revista); 
	   }
	   encontrado=1;
       }
       auxiliar = auxiliar->siguiente;
   }
   if (encontrado==0)
   {
       printf( "\nNo se ha encontrado la publicación por esa ID\n" );
   }
}
 
void modificar(int identif) 
{
   struct lista *auxiliar;
   auxiliar = primero;
   int encontrado=0;
   while (auxiliar!=NULL) 
   {
       if(auxiliar->identificador==identif)
       {
	   suprimir_campos(identif);
	   anadir_campos(auxiliar);
	   encontrado=1;
       }
       auxiliar = auxiliar->siguiente;
   }
   if (encontrado==0)
   {
       printf( "\nNo se ha encontrado la publicación por esa ID\n" );
   }
}
 
void ordenar_lista()
{
   struct lista *actual;
   struct lista *sgt;//para no confundirlo con siguiente
   struct lista *anterior;
   actual=primero;
   sgt=actual->siguiente;
   while(sgt!=NULL)
   {                              
       if(actual->anio < sgt->anio)
       {
           actual->siguiente=actual->siguiente->siguiente;
           sgt->siguiente=actual;
           if(actual==primero)
	   {
               primero=sgt;                 
           }
           else
	   {
               anterior->siguiente=sgt;   
           }
           anterior=sgt;
           actual=anterior->siguiente;
           if(actual==NULL)
	   {
               break;               
           }                     
           sgt = actual->siguiente;
       }
       else
       {
           anterior=actual; 
           actual=actual->siguiente;
           sgt=sgt->siguiente;
       }                                
   }
}

void exportar(char *nombre)
{
   int eleccion;
   FILE *fichero;
   struct lista *provisional;
   size_t resultado;
   int longitud = 0;
   int inicio;
   
   provisional = primero;
   
   fichero = fopen(nombre, "w");
   if (fichero == NULL)
   {
       printf("\nEl fichero no se ha podido abrir para escritura.\n");
   }
   else
   {
       puts("\nEscribiendo...\n");
       if (primero == NULL)
       {
           puts("\nLa lista esta vacia\n");
       }
       else
       {
	 while (provisional != NULL)
	 {
	     longitud = strlen(provisional->titulo);
	     resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	     resultado = fwrite(provisional->titulo, sizeof(char), strlen(provisional->titulo), fichero);
	     longitud = strlen(provisional->fuente);
	     resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	     resultado = fwrite(provisional->fuente, sizeof(char), strlen(provisional->fuente), fichero);
	     longitud = strlen(provisional->autores);
	     resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	     resultado = fwrite(provisional->autores, sizeof(char), strlen(provisional->autores), fichero);
	     resultado = fwrite(&provisional->anio, sizeof(int), 1, fichero);
	     resultado = fwrite(&provisional->issn, sizeof(int), 1, fichero);
	     if (provisional->tipo == CONFERENCIA) //Si no funciona bien probar añadiendo ENUM
	     {
	         longitud = 1;
	         resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	         longitud = strlen(provisional->confe.lugar);
	         resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	         resultado = fwrite(provisional->confe.lugar, strlen(provisional->confe.lugar), 1, fichero);
	     }
	     else if (provisional->tipo == ARTICULO)
	     {
	         longitud = 2;
	         resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	         longitud = strlen(provisional->arti.volumen);
	         resultado = fwrite(&longitud, sizeof(int), 1, fichero);
	         resultado = fwrite(provisional->arti.volumen, strlen(provisional->arti.volumen), 1, fichero);
	         resultado = fwrite(&provisional->arti.revista, sizeof(int), 1, fichero);
	     }
	     if(resultado!=0)
	     {
		 puts("Referencia escrita con éxito");
	     }
	     provisional = provisional->siguiente;
	 }
	 puts("Se ha exportado la lista");
	 puts("¿Desea liberar la lista?. Pulse 1 si así lo quiere");
	 eleccion=pedir_numero_iter();
	 if(eleccion==1)
	 {
	     longitud = tamanio_lista();
	     for(inicio=0; inicio<longitud; inicio++)
	     {
		 suprimir_inicio();
	     }
	 }
	 if (fclose(fichero)!=0)
	 {
	     puts("\nNo se ha podido cerrar el fichero\n");
	 }
	 else
	 {
	     puts("\nFichero escrito con exito. La lista se ha transferido correctamente");
	 }
       }
   }
}

/*
 * Hemos intentado hacer la función importar. La función importa la lista pero con valores
 * NULL ó 0 según sean nombre o número (Además que importe estos valores es un problema
 * pero es lo máximo que hemos conseguido sacar de la función). 
 * Hemos tratado de sacarla pero no ha sido posible.
 * Hemos tratado de contactar con usted para resolver esta duda porque no entendemos porque
 * no lo hace bien si en teoría debería hacerlo bien. Espero que tenga esto en cuenta ya que
 * además somos sólo 2 personas los que hemos hecho este trabajo. 
 * 
 */

void importar(char *nombre)
{
   FILE *fichero;
   struct lista *provisional;
   size_t resultado;
   int condicion=0;
   int lector;
   int longitud = 0;
   
   fichero = fopen(nombre, "r");
   if (fichero == NULL)
   {
       printf("\n¡El fichero no se ha podido abrir para escritura!\n");
   }
   else
   {
       if (primero == NULL)
       {
           provisional=(struct lista *)malloc(sizeof(struct lista));
	   primero=provisional;
	   condicion = 1;
       }
       else
       {
	   provisional=(struct lista *)malloc(sizeof(struct lista));
           struct lista *recorrido;
	   recorrido=primero;
	   while(recorrido->siguiente!=NULL)
	   {
	       recorrido=recorrido->siguiente;
	   }
	   recorrido->siguiente=provisional;
	   condicion = 1;
       }
       lector = feof(fichero);
       while (lector != 0)
       {
	   if(condicion==0)
	   {
	       provisional=(struct lista *)malloc(sizeof(struct lista));
	   }
	 provisional->identificador = (tamanio_lista() + 1);
	 resultado = fread(&longitud, sizeof(int), 1, fichero);
	 resultado = fread(provisional->titulo, sizeof(char), longitud, fichero);
	 resultado = fread(&longitud, sizeof(int), 1, fichero);
	 resultado = fread(provisional->fuente, sizeof(char), longitud, fichero);
	 resultado = fread(&longitud, sizeof(int), 1, fichero);
	 resultado = fread(provisional->autores, sizeof(char), longitud, fichero);
	 resultado = fread(&provisional->anio, sizeof(int), 1, fichero);
	 resultado = fread(&provisional->issn, sizeof(int), 1, fichero);
	 resultado = fread(&longitud, sizeof(int), 1, fichero);
	 if (longitud == 1)
	 {
	     provisional->tipo = CONFERENCIA;
	     resultado = fread(&longitud, sizeof(int), 1, fichero);
	     resultado = fread(provisional->confe.lugar, longitud, 1, fichero);
	 }
	 else if (longitud == 2)
	 {
	     provisional->tipo = ARTICULO;
	     resultado = fread(&longitud, sizeof(int), 1, fichero);
	     resultado = fread(provisional->arti.volumen, longitud, 1, fichero);
	     resultado = fread(&provisional->arti.revista, sizeof(int), 1, fichero);
	 }
	 if(resultado!=0)
	 {
	     puts("Referencia leida con éxito");
	 }
	 condicion=0;
	 provisional=provisional->siguiente;
       }
       if (fclose(fichero)!=0)
       {
	 puts("\nNo se ha podido cerrar el fichero.\n");
       }
       else
       {
	 puts("\nFichero leído con éxito");
       }
   }
}