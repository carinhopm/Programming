#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CLista.h"
#include "CFunciones.h"
 
void mostrar_menu() 
{
   puts("\nMenú:\n");
   puts("1.- Añadir referencia bibliográfica");
   puts("2.- Ordenar lista por fechas descendentes");
   puts("3.- Mostrar referencia por ID");
   puts("4.- Mostrar resumen lista completa");
   puts("5.- Modificar una referencia por ID");
   puts("6.- Borrar referencia a partir del ID");
   puts("7.- Exportar referencias a un fichero");
   puts("8.- Importar referencias desde un fichero");
   puts("9.- Liberar lista y salir");
   puts("Para salir de la aplicación pulse CTRL-D. ");
   puts("Escoge una opción: ");
}

int main() 
{
   int opcion=0;
   int inicio;
   int id;
   int cont;
   char *nom;
   primero = (struct lista *) NULL;//inicializar lista
   while(1)
   {
       mostrar_menu();
       opcion=pedir_numero_iter();
       if(opcion==-1)
       {
	   salir_programa(opcion);
       }
       switch (opcion)
       {
	   case 1:
               anadir_elemento();
	       break;
	       
	   case 2:
	       cont=tamanio_lista();
	       for(inicio=0; inicio<cont; inicio++)
	       {
	           ordenar_lista();
               }
               puts("Lista ordenada de mayor a menor año de publicación");
	       break;
	       
	   case 3:
	       puts("Introduzca el identificador: ");
	       id=pedir_numero_iter();
	       mostrar_lista(id);
	       break;
	       
	   case 4:
	       mostrar_lista_completa();
	       break;
	       
	   case 5:
	       puts("Introduzca el identificador: ");
	       id=pedir_numero_iter();
	       modificar(id);
	       break;
	       
	   case 6:
	       puts("Introduzca el identificador a borrar");
	       id=pedir_numero_iter();
	       suprimir_en_lista(id);
	       break;
	       
	   case 7:
	       puts("Introduzca el nombre del fichero");
	       nom=leer_cadena();
	       exportar(nom);
	       free(nom);
	       break;
	       
	   case 8:
	       puts("Introduzca el nombre del fichero");
	       nom=leer_cadena();
	       importar(nom);
	       free(nom);
	       break;
	       
	   case 9:
	       opcion=-1;
	       salir_programa(opcion);
	       break;
	       
	   default:
	       puts("\nIntroduce una opción correcta\n");
       }
   }
   return 0;
}