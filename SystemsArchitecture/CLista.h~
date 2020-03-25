enum tipo_articulo 
{
   ARTICULO, 
   CONFERENCIA
};
 
struct conferencia
{
   char *lugar;
};
 
struct articulo
{
   char *volumen;
   int revista;
};
 
struct lista 
{
   enum tipo_articulo tipo;
   int identificador;
   char *titulo;
   char *fuente;
   char *autores;
   int anio;
   int issn;
   struct lista *siguiente;
   struct conferencia confe;
   struct articulo arti;	
};

struct lista *primero;

char *leer_cadena();
int pedir_numero_iter();
char *mostrar_tipo(enum tipo_articulo tipo);
void anadir_campos(struct lista *nuevo);
void anadir_elemento();