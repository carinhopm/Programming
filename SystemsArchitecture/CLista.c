#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLista.h"

char *leer_cadena()
{
   ssize_t bytes_leidos;
   size_t num_bytes = 0;
   char *letras=NULL;
   bytes_leidos = getline(&letras, &num_bytes, stdin);
   if(bytes_leidos == -1)
   {
       //puts("\nError al introducir la cadena");
       free(letras);
       return NULL;
    }
    else
    {
       letras[strlen(letras)-1]='\0';
       return letras;
    }
}

int pedir_numero_iter()
{
   int resultado;
   char *cadena=NULL;
   char *basura=NULL;
   do 
   {
       cadena=leer_cadena();
       if(cadena==NULL)
       {
	   free(cadena);
	   resultado=-1;
       }
       else
       {
	   resultado=strtol(cadena,&basura,0);
	   if(strlen(basura)!=0)
	   {
	       //free(basura);
	       puts("Has introducido letras, vuelve a introducir un número");
	       resultado=-2;
	       free(cadena);
	   }
       }
   }while(resultado<-1);
   free(cadena);
   return resultado;
}

char *mostrar_tipo(enum tipo_articulo tipo)
{
   if (tipo==CONFERENCIA)
   {
       return "Conferencia";
   }
   else
   {
       return "Articulo";
   }
}

void anadir_campos(struct lista *nuevo)
{
   int opcion=0;
   
   printf("\nIntroduzca los datos de la referencia:\n");
   printf("Título del artículo: ");
   nuevo->titulo=leer_cadena();
   printf("Nombre de la fuente: ");
   nuevo->fuente=leer_cadena();
   printf("Autores: ");
   nuevo->autores=leer_cadena();
   printf("Año de publicación: ");
   nuevo->anio=pedir_numero_iter();
   printf("ISSN: ");
   nuevo->issn = pedir_numero_iter(); 
      
   while(opcion!=1)
   {
       puts("Introduce si la contribución es una conferencia(1) o un artículo(2): ");
       opcion = pedir_numero_iter();
       if(opcion==2)
       {
	   break;
       }
   }
   
   if(opcion==1)
   {
       puts("Introduce el lugar de la conferencia: ");
       nuevo->confe.lugar=leer_cadena();	
       nuevo->tipo = CONFERENCIA;
   }
      
   else if(opcion==2)
   {
       puts("Introduce el volumen del artículo: ");
       nuevo->arti.volumen=leer_cadena();
       puts("Introduce el número de revista: ");
       nuevo->arti.revista = pedir_numero_iter();
       nuevo->tipo = ARTICULO;
   } 
}

void anadir_elemento() 
{
   static int contador=0; 
   struct lista *nuevo;
   nuevo = (struct lista *) malloc (sizeof(struct lista));	
   if (nuevo==NULL)
   { 
       printf( "No hay memoria disponible!\n");//avise si ha habido un error en el malloc
       return;
   }
   anadir_campos(nuevo);   
   contador++;
   nuevo->identificador=contador;
   if (primero==NULL) 
   {
       puts("\nPrimer elemento\n");
       primero = nuevo;
   }
   else 
   {
       struct lista *recorrido;
       recorrido=primero;
       while(recorrido->siguiente!=NULL)
       {
	   recorrido=recorrido->siguiente;
       }
       recorrido->siguiente=nuevo;
   }
   nuevo->siguiente = NULL;
}