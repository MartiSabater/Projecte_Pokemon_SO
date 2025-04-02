#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

/* typedef struct{
	char nombre[20];
    int socket;
}Conectado;

typedef struct{
	Conectado cnct [100];
	int num;
}Listaconectados;

//Anade nuevo conectado
int Anade (Listaconectados *lista, char nombre[20], int socket){
	if( lista->num == 100) return -1;
	else {
		strcpy(lista->cnct[lista->num].nombre,nombre);
		lista-> cnct[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}

int Elimina (Listaconectados *lista, char nombre[20]){
	//Retorna 0 si elimina y -1 si el usuario no esta en la lista
	int pos = Posicion(lista, nombre);
	if(pos == -1) 
		return -1;
	else {
		int i;
		for(i=pos; i<lista->num-1; i++){
			lista->cnct[i] = lista->cnct[i+1];
			strcpy(lista->cnct[i].nombre,lista->cnct[i+1].nombre);
			lista->cnct[i].socket = lista->cnct[i+1].socket;
		}
		lista->num--;
		return 0;
	}

}

int Posicion(Listaconectados *lista, char nombre[20]){
	//Devuelve socket o -1 si no esta en lista
	int i=0;
	int encontrado=0;
	while((i<lista->num)&& !encontrado){
		if(strcmp(lista->cnct[i].nombre,nombre)){
		encontrado = 1; 
		}
		if(!encontrado){
			i++;
		}
	}
	if(encontrado==1){
		return i;
	}
	else
	return -1;
}

void Conectados (Listaconectados *lista, char conectados[300]){
	//Pone en conectados los nombres de todos lo conecntados separados por /. 
	//Primero proporciona en numero de conectados.
	sprintf(conectados,"%d",lista->num);
	int i;
	for(i=0; i<lista->num; i++){
		sprintf(conectados,"%s/%s",conectados,lista->cnct[i].nombre);
	}
} */

char ubicacion[30];


//Esttructura necessaria para acesso excluyente
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *AtenderCliente(void *socket)
{
	int socket_conn;
	int *s;
	int ret;
	s =(int *) socket;
	socket_conn = *s;
	char peticion[512];
	char buff2[1000];
	
	
	strcpy(ubicacion, "localhost");
	printf("Socket del cliente: %d\n", socket_conn);

	//Inicio el MYSQL
	MYSQL *conn;
	int err;
	
	// Estrucutra especial para almecenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
    // Conectar con el servidor MySQL
    if (mysql_real_connect(conn, ubicacion, "root", "mysql", "JuegoPokemon", 0, NULL, 0) == NULL) 
	{
        printf("Error al conectar con el servidor MySQL\n");
        mysql_close(conn);
        close(socket_conn);
        pthread_exit(NULL);
    }
	else 
	{
		printf("Se ha conectado a la base de datos con exito\n");
	}

	int terminar = 0;
	//Entramos en un bucle para atender todas las peticiones de este cliente
	//hasta que se desconecte
	while(terminar == 0)
	{
		//Ahora recibimos la peticion
		ret = read(socket_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		
		//Tenemos que a�adirle la marca de fin de string
		//Para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';
		
		printf ("Se ha conectado: %s\n", peticion);
		
		
		char *p = strtok(peticion, "/"); //Separamos los campos de las consultas por /
		if (p == NULL) {
			printf("Error: Codigo no especificado.\n");
			break;
		}
		int codigo =  atoi (p);

		if(codigo == 0)
		{
			terminar = 1;
		}
		else if (codigo ==1) //piden registrar un usuario teniendo nombre y constrase�a si no esta ya en la base de datos manda un Ok
		{
			strcpy(buff2,"");
			pthread_mutex_lock(&mutex);
			char nombre[50];
			char contrasena[50];
				
			
			//Comprobamos que el mensaje recibido tienen un formato correcto
			p = strtok(NULL, "/");  // Obtenemos el usuario
			if (p != NULL) {
				strcpy(nombre, p);  // Guardar el nombre
			} else {
				strcpy(buff2, "Error: Formato de nombre incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}

			p = strtok(NULL, "/");  // Obtener la contraseña
			if (p != NULL) {
				strcpy(contrasena, p);  // Guardar la contraseña
			}else {
				strcpy(buff2, "Error: Formato de contrase�a incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			
			printf("Se ha registrado el usuario: %s con contrae�a: %s", nombre, contrasena);


			/*Construir la consulta SQL para registrar usuario 
			y despues creamos comprobamos si el usuario existe*/
			char query[512];
			sprintf(query, "INSERT INTO Jugadores (nombre, pasword, numeroPokemons, victorias, derrotas, pos) "
					"SELECT * FROM (SELECT '%s' AS nombre, '%s' AS pasword, 0 AS numeroPokemons, "
					"0 AS victorias, 0 AS derrotas, '' AS pos) AS tmp "
					"WHERE NOT EXISTS (SELECT 1 FROM Jugadores WHERE nombre = '%s') LIMIT 1;",
					nombre, contrasena, nombre);
			
			// Ejecutar la consulta en MySQL
			if (mysql_query(conn, query) == 0 && mysql_affected_rows(conn) > 0) {
				// Si se insertó un usuario, enviar "Ok"
				strcpy(buff2, "El registro ha sido exitoso");
				printf("Registro exitoso\n");
			} else {
				// Si no se pudo registrar (porque ya existe), enviar error
				strcpy(buff2, "Error: Usuario ya existe");
				printf("Error: El usuario ya existe\n");
			}
			//Enviamos los resultados al cliente
			write(socket_conn, buff2, strlen(buff2));
			pthread_mutex_unlock(&mutex);
		}

		else if (codigo ==2) //piden iniciar sesion en un usuario con nombre y contrase�a, si se encuientra en la base de datos manda un Ok
		{
			strcpy(buff2,"");
			pthread_mutex_lock(&mutex);
			char nombre[50] = "";
			char contrasena[50] = "";
			
			// Separar la consulta en nombre y contraseña
			p = strtok(NULL, "/");
			if (p != NULL) {
				strcpy(nombre, p);//Copimaos el usuario
			} else {
				strcpy(buff2, "Error: Formato de nombre incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			p = strtok(NULL, "/");
			if (p != NULL) {
				strcpy(contrasena, p); //Copiamos la contasena
			} else {
				strcpy(buff2, "Error: Formato de contrasena incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			printf("Intentando iniciar sesion con -> Nombre: '%s', Contrasena: '%s'\n", nombre, contrasena);
			
			// Consulta SQL para verificar si existe el usuario con la contraseña correcta
			char query[512];
			sprintf(query, "SELECT COUNT(*) FROM Jugadores WHERE nombre = '%s' AND pasword = '%s';",
					nombre, contrasena);
			
			// Ejecutar consulta
			if (mysql_query(conn, query) == 0) {
				MYSQL_RES *res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);
				
				if (row && atoi(row[0]) > 0) {
					strcpy(buff2, "Sesion Iniciada exitosamente"); // Usuario encontrado
				} else {
					strcpy(buff2, "Error: Usuario o contrasena incorrectos");
				}
				
				mysql_free_result(res);
			} else {
				strcpy(buff2, "Error: Problema con la base de datos");
			}
			
			// Enviar respuesta al cliente
			write(socket_conn, buff2, strlen(buff2));

			pthread_mutex_unlock(&mutex);
		}
		//Formato Consulta: 3/NombreJugador
		else if (codigo ==3) //Que pokemons tiene el jugador/ cliente
		{
			//Extraer el nombre del cliente
			strcpy(buff2,"");
			char nombrecliente[50] = "";
			// Extraer el nombre del Pokemon que en�a el cliente
			p = strtok(NULL, "/");
			if (p != NULL) {
				strcpy(nombrecliente, p);
			} else {
				strcpy(buff2, "Error: Formato incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			
			printf("Buscando los pokemosn que tiene el jugador -> '%s'\n", nombrecliente);

			// Consulta SQL para obtener toda la informacion del Pokemon
			char query[512];
			sprintf(query, "SELECT Pokedex.*, Relacio.Nivell FROM Jugadores JOIN Relacio ON Jugadores.id = Relacio.IdJ JOIN Pokedex ON Relacio.IdP = Pokedex.id WHERE Jugadores.nombre = '%s';",nombrecliente);
			
			// Ejecutar consulta
			if (mysql_query(conn, query) == 0) {
				MYSQL_RES *res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);

				if(row == NULL){
					printf("El jugador %s no tiene pokomons", nombrecliente);
					sprintf(buff2, "El jugador %s no tiene pokomons", nombrecliente);
				}else{

					while(row != NULL){
						sprintf(buff2, "%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s#", buff2, row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9]);
						row = mysql_fetch_row(res);
					}
					printf("Pokemons: %s",buff2);
				}

				mysql_free_result(res);
			} else {
				strcpy(buff2, "Error: Problema con la base de datos");
			}

			//Enviamos el mensaje
			write(socket_conn, buff2, strlen(buff2));

		}
		//Formato de la Consulta : 4/nombreJugador
		else if (codigo ==4) //Lista de partidas donde el juagador esta
		{
			char nombreCliente[50] = "";
			strcpy(buff2,"");
			
			// Extraer el nombre del Pokemon que en�a el cliente
			p = strtok(NULL, "/");
			if (p != NULL) {
				strcpy (nombreCliente, p);
			} else {
				strcpy(buff2, "Error: Formato incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			
			printf("Buscando las partidas del usuario -> Nombre: '%s'\n", nombreCliente);
			// Consulta SQL para obtener toda la informacion del Pokemon
			char query[512];
			sprintf(query, "SELECT *FROM Partidas WHERE '%s' IN (jugador1, jugador2, jugador3, jugador4);", nombreCliente);
			
			// Ejecutar consulta
			if (mysql_query(conn, query) == 0) {
				MYSQL_RES *res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);

				if(row != NULL){
					while(row != NULL){
						sprintf(buff2,"%s/%s/%s/%s/%s/%s/%s/%s/",buff2, row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
						row = mysql_fetch_row(res);
					}
				}else{
					printf("El jugador  %s no a participado en ninguna partida", nombreCliente);
					sprintf(buff2, "El jugador %s no a participado en ninguna partida", nombreCliente);
				}
				mysql_free_result(res);
			} else {
				strcpy(buff2, "Error: Problema con la base de datos");
			}
			
			// Enviar respuesta al cliente
			write(socket_conn, buff2, strlen(buff2));
		}
		//Formato de la Consulta : 5/nombrePokemon
		else if (codigo ==5) //El servidor recibe el nombre de un pokemon y le manda al cliente todos los jugadores que tienen ese pokemon
		{
			char nombrePokemon[50] = "";
			char query[512];
			char buff2[1024] = ""; 
			
			// Extraer el nombre del Pokemon
			p = strtok(NULL, "/");
			if (p != NULL) {
				strncpy(nombrePokemon, p, sizeof(nombrePokemon) - 1);
				nombrePokemon[sizeof(nombrePokemon) - 1] = '\0'; // Evitar desbordamientos
			} else {
				strcpy(buff2, "Error: Formato incorrecto");
				write(socket_conn, buff2, strlen(buff2));
				break;
			}
			printf("Buscando los jugadores que tienen el Pokemon %s\n", nombrePokemon);
			
			// Construccion de la consulta SQL con formato seguro
			snprintf(query, sizeof(query),
					 "SELECT Jugadores.nombre FROM Jugadores, Pokedex, Relacio "
					 "WHERE Pokedex.nombrePokemon = '%s' AND Pokedex.id = Relacio.IdP AND Relacio.IdJ = Jugadores.id;",
					 nombrePokemon);
			// Ejecutar la consulta SQL
			if (mysql_query(conn, query) == 0) {
				MYSQL_RES *res = mysql_store_result(conn);
				if (res) {
					MYSQL_ROW row;
					while ((row = mysql_fetch_row(res)) != NULL) {
						strcat(buff2, row[0]);
						strcat(buff2, "/");
					}
					mysql_free_result(res);
				}
				// Si no se encontraron jugadores, enviar mensaje adecuado
				if (strlen(buff2) == 0) {
					snprintf(buff2, sizeof(buff2), "No hay jugadores con el Pokemon %s", nombrePokemon);
				}
			} else {
				strcpy(buff2, "Error: Problema con la base de datos");
				printf("Error en la consulta SQL: %s\n", mysql_error(conn));
			}
			
			// Enviar la respuesta al cliente
			write(socket_conn, buff2, strlen(buff2));
			
		}
	}
	//Cerramos la conexion con el servidor
	close(socket_conn); 
}


int main(int argc, char *argv[])
{
	strcpy(ubicacion, "localhost");
	//Inicio conexion con MYSQL
	MYSQL *conn;
	int err;
	

	//Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;

	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if(conn == NULL){
		printf("Error al crear la conexion: %u %S\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}

	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;

	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creando socket\n");
	// Fem el bind al port
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9030);

	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0){
		printf ("Error al bind\n");
	}
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 2) < 0){
		printf("Error en el Listen\n");
	}
		

	/*Aqui iniciariamos la listas de conectados
	Listaconectados lista;
	lista.num = 0;
	char connect [300];
	*/
	
	
	int i = 0;
	int sockets[100];
	pthread_t thread;
	for(;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		
		//sockets[i] es el socket que usaremos para este cliente
		sockets[i] = sock_conn;
		
		//Creatr thead y decirle lo que tiene que hacer
		pthread_create(&thread, NULL, AtenderCliente, &sockets[i]); //Le passas el socket por referencia. Para no passar le una copia 
		
		i++;
	}

	//Cerramos la conexion MYSQL
	mysql_close(conn);

	return 0;
}
