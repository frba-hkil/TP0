#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;

	t_log* logger;
	t_config* config;
	cliente_t* cliente;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola!, Soy un log\n");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	cliente = cargar_cliente_config(config);

	// Loggeamos el valor de config
	log_info(logger, "key:%s ip:%s puerto:%s\n", cliente->valor, cliente->ip, cliente->puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(cliente->ip, cliente->puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(cliente->valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);
	destruir_cliente(cliente);
	terminar_programa(conexion, logger, config);
	close(conexion);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	return log_create("./Debug/tp0.log", "tp0logger", true, LOG_LEVEL_INFO);

}

t_config* iniciar_config(void)
{
	return config_create("./cliente.config");
}

cliente_t* cargar_cliente_config(t_config* cfg){
	cliente_t* cliente = malloc(sizeof(cliente_t));

	cliente->valor = config_get_string_value(cfg, "CLAVE");
	cliente->ip = config_get_string_value(cfg, "IP");
	cliente->puerto = config_get_string_value(cfg, "PUERTO");

	return cliente;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	if(leido){
		log_info(logger,"linea leida:%s\n", leido);
		free(leido);
	}
	while(1){
		leido = readline("> ");
		if(!leido)
			break;
		log_info(logger,"linea leida:%s\n", leido);
		free(leido);
	}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	while(1){
		leido = readline("> ");
		if(!leido)
			break;
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
	}
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
}

void destruir_cliente(cliente_t* cliente){

	//free(cliente->valor);
	//free(cliente->ip);
	//free(cliente->puerto);
	free(cliente);
}
