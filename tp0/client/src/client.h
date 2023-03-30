#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

#define PORT_MAX_STR_SIZE 6
#define IP_MAX_STR_SIZE 10
#define KEY_VALUE_MAX_SIZE 100

typedef struct cliente{
	char* valor;
	char* ip;
	char* puerto;
}cliente_t;

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
cliente_t* cargar_cliente_config(t_config*);
void destruir_cliente(cliente_t*);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* CLIENT_H_ */
