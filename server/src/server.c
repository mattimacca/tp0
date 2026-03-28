#include "server.h"

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);
	//handshake(server_fd);

	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;
}

/*void handshake(int socketServer){
	size_t bytes;

	int32_t handshakee;
	int32_t resultOk = 0;
	int32_t resultError = -1;

	bytes = recv(socketServer, &handshakee, sizeof(int32_t), MSG_WAITALL);
	
	if (handshakee == 1) {
    	bytes = send(socketServer, &resultOk, sizeof(int32_t), 0);
	} else {
   		bytes = send(socketServer, &resultError, sizeof(int32_t), 0);
	}
}*/

void iterator(char* value) {
	log_info(logger,"%s", value);
}
