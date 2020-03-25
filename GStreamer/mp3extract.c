/*AUTORES: 
Carlos Parra Marcelo - NIA: 100304942
Tirso Vargas Vega - NIA: 100345397

Se ha implementado al completo el REQUISITO #2
*/


/*IMPORTACIÓN DE LIBRERÍAS*/
#include <gst/gst.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*DECLARACIÓN DE VARIABLES*/
int option, num_pipeline;

/*MÉTODO PARA LA GESTIÓN DEL BUS DE MENSAJES*/
void bus_management(GstBus *bus, GstMessage *msg) {			  
	switch (GST_MESSAGE_TYPE (msg)) {
		case GST_MESSAGE_EOS: {	//Notifica la correcta ejecución de los pipelines
		g_print ("End Of Process Number %d\n", num_pipeline);
		break;
    }
    case GST_MESSAGE_ERROR: {	//Notifica mensajes de error o de depuración
		GError *err = NULL; 
		gchar *dbg = NULL;  

		gst_message_parse_error (msg, &err, &dbg);
		if (err) {
			g_printerr ("ERROR: %s\n", err->message);
			g_error_free (err);
		}
		if (dbg) {
			g_printerr ("[DEBUG DETAILS: %s]\n", dbg);
			g_free (dbg);
		}
    }
    default:	//Notifica mensajes inesperados
		g_printerr ("UNEXPECTED MESSAGE: %d", GST_MESSAGE_TYPE (msg));
		break;
	}
}

/*MÉTODO PRINCIPAL*/
int main (int argc, char *argv[]) {
	
	//Creación de los elementos necesarios para el pipeline
	GstElement *pipeline;
	GstElement *filesrc, *filesink;
	GstMessage *msg;
	GstBus *bus;
	GError *error = NULL;

	//Inicialización de los argumentos
	gst_init (&argc, &argv);

	//Comprobación de los argumentos
	if (argc < 2) {
		g_print ("ERROR: Not enough arguments\n");
		return -1;
	} else if (argc == 2) {
		option = 1;
	} else if (argc == 3) {
		option = 2;
	} else {
		g_print ("ERROR: Incorrect arguments\n");
		return -2;
	}

	//Creación del pipeline: descarga el vídeo y lo guarda
	pipeline = gst_parse_launch ("souphttpsrc name=source1 ! filesink name=destination1", &error);
  
	//Comprobación de error del pipeline
	if (!pipeline) {
		g_print ("ERROR: Pipeline failed -> %s\n", error->message);
		return -3;
	}
	
	//Guarda el nombre del vídeo
	gchar slash[]={'/'};
	gchar **url_video = g_strsplit ((gchar *) argv[option], slash, 0);
	char *noum = url_video[sizeof(url_video)+1];

	//Configuración de fuente y sumidero
	filesrc = gst_bin_get_by_name (GST_BIN (pipeline), "source1");
	if (option == 1) {
		g_object_set (filesrc, "location", argv[1], NULL);
	} else if (option == 2) {
		g_object_set (filesrc, "location", argv[2], NULL);
	}
	filesink = gst_bin_get_by_name (GST_BIN (pipeline), "destination1");
	g_object_set (filesink, "location", noum , NULL);

	//Borrado de elementos
	g_object_unref (filesrc);
	g_object_unref (filesink);

	//Ejecución del pipeline
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	bus = gst_element_get_bus (pipeline);

	//Escucha mensajes del bus y los muestra por consola
	msg = gst_bus_poll (bus, GST_MESSAGE_EOS | GST_MESSAGE_ERROR, -1);
	num_pipeline = 1;
	bus_management(bus, msg);

	//Creación del pipeline: extrae el audio del vídeo y lo guarda como MP3
	pipeline = gst_parse_launch ("filesrc name=source2 ! decodebin ! audioconvert ! lamemp3enc ! id3v2mux ! filesink name=destination2", &error);
  
	//Comprobación de error del pipeline
	if (!pipeline) {
		g_print ("ERROR: Pipeline failed -> %s\n", error->message);
		return -4;
	}

	//Crea el nombre del MP3 a partir de la URL del vídeo
	gchar point[] = ".";
	gchar ending[] = ".mp3";
	gchar **url_video_mp3 = g_strsplit((gchar *) noum, point, 0);
	g_print(point);
	gchar *noum_mp3 = g_strconcat(url_video_mp3[0], ending);

	//Configuración de fuente y sumidero
	filesrc = gst_bin_get_by_name (GST_BIN (pipeline), "source2");
	g_object_set (filesrc, "location", noum, NULL);
	filesink = gst_bin_get_by_name (GST_BIN (pipeline), "destination2");
	g_object_set (filesink, "location", noum_mp3, NULL);

	//Borrado de elementos
	g_object_unref (filesrc);
	g_object_unref (filesink);

	//Ejecución del pipeline
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	bus = gst_element_get_bus (pipeline);

	//Escucha mensajes del bus y los muestra por consola
	msg = gst_bus_poll (bus, GST_MESSAGE_EOS | GST_MESSAGE_ERROR, -1);
	num_pipeline = 2;
	bus_management(bus, msg);
  
	//Opción de reproducción del vídeo
	if (option==2) {
		
		//Creación del pipeline: reproduce el vídeo
		pipeline = gst_parse_launch ("filesrc name=source3 ! decodebin name = d d. ! queue ! videoconvert ! xvimagesink d. ! queue ! decodebin ! audioconvert ! audioresample ! autoaudiosink", &error);
		
		//Comprobación de error del pipeline
		if (!pipeline) {
			g_print ("ERROR: Pipeline failed -> %s\n", error->message);
			return -5;
		}
  
		//Configuración de fuente y sumidero
		filesrc = gst_bin_get_by_name (GST_BIN (pipeline), "source3");
		g_object_set (filesrc, "location", noum, NULL);
		g_object_unref (filesrc);

		//Borrado de elementos
		g_object_unref (filesrc);
		g_object_unref (filesink);

		//Ejecución del pipeline
		gst_element_set_state (pipeline, GST_STATE_PLAYING);
		bus = gst_element_get_bus (pipeline);

		//Escucha mensajes del bus y los muestra por consola
		msg = gst_bus_poll (bus, GST_MESSAGE_EOS | GST_MESSAGE_ERROR, -1);
		num_pipeline = 3;
		bus_management(bus, msg);
	}

	//Libera el pipeline
	gst_element_set_state (pipeline, GST_STATE_NULL);
	
	//Borrado de elementos
	gst_object_unref (pipeline);
	gst_object_unref (bus);
	gst_message_unref (msg);
	g_free(url_video);
	g_free(url_video_mp3);
	g_free(noum);
	g_free(noum_mp3);

	return 0;
}
