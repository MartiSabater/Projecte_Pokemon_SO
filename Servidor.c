#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql/mysql.h>


int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char buff[512];
	char buff2[512];
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 2) < 0)
		printf("Error en el Listen");
	
	int i;
	// Atenderemos solo 5 peticione
	
	
	// Inicializar MySQL
	MYSQL *conn;
	conn = mysql_init(NULL);
	
	// Configurar conexión a la base de datos
	const char *server = "localhost";
	const char *user = "root";
	const char *password = "mysql";
	const char *database = "JuegoPokemon";
	
	// Conectarse a MySQL
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "Error de conexion a MySQL: %s\n", mysql_error(conn));
		return 1;
	}
	
	printf("Conexion a MySQL exitosa.\n");
	
	
	for(i=0;i<70;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		//sock_conn es el socket que usaremos para este cliente
		
		// Ahora recibimos su nombre, que dejamos en buff
		ret=read(sock_conn,buff, sizeof(buff));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		buff[ret]='\0';
		
		//Escribimos el nombre en la consola
		
		printf ("Se ha conectado: %s\n",buff);
		
		
		char *p = strtok( buff, "/");
		int codigo =  atoi (p);
		p = strtok( NULL, "/");
		char consulta[20];
		strcpy (consulta, p);
		printf ("Codigo: %d, Consulta: %s\n", codigo, consulta);
		
		if (codigo ==1) //piden registrar un usuario teniendo nombre y constrase�a si no esta ya en la base de datos manda un Ok
		{
			char *p = strtok(consulta, ",");  // Separar por coma
			char nombre[50];
			char contrasena[50];
			
			if (p != NULL) {
				strcpy(nombre, p);  // Guardar el nombre
				p = strtok(NULL, ",");  // Obtener la contraseña
				if (p != NULL) {
					strcpy(contrasena, p);  // Guardar la contraseña
				}else {
					strcpy(buff2, "Error: Formato de contrase�a incorrecto");
					write(sock_conn, buff2, strlen(buff2));
					return;
				}
			} else {
				strcpy(buff2, "Error: Formato de nombre incorrecto");
				write(sock_conn, buff2, strlen(buff2));
				return;
			}
			// Construir la consulta SQL para registrar usuario
			char query[512];
			sprintf(query, "INSERT INTO Jugadores (nombre, pasword, numeroPokemons, nivel, victorias, derrotas, pos) "
					"SELECT * FROM (SELECT '%s' AS nombre, '%s' AS pasword, 0 AS numeroPokemons, 1 AS nivel, "
					"0 AS victorias, 0 AS derrotas, '' AS pos) AS tmp "
					"WHERE NOT EXISTS (SELECT 1 FROM Jugadores WHERE nombre = '%s') LIMIT 1;",
					nombre, contrasena, nombre);
			
			// Ejecutar la consulta en MySQL
			if (mysql_query(conn, query) == 0 && mysql_affected_rows(conn) > 0) {
				// Si se insertó un usuario, enviar "Ok"
				strcpy(buff2, "El registro ha sido exitoso");
			} else {
				// Si no se pudo registrar (porque ya existe), enviar error
				strcpy(buff2, "Error: Usuario ya existe");
			}
			
			write(sock_conn, buff2, strlen(buff2));
		}
			

		
		
		if (codigo ==2) //piden iniciar sesion en un usuario con nombre y contrase�a, si se encuientra en la base de datos manda un Ok
		{
			char nombre[50] = "";
			char contrasena[50] = "";
			
			// Separar la consulta en nombre y contraseña
			char *p = strtok(consulta, ",");
			if (p != NULL) {
				strcpy(nombre, p);
				p = strtok(NULL, ",");
				if (p != NULL) {
					strcpy(contrasena, p);
				} else {
					strcpy(buff2, "Error: Formato de contrasena incorrecto");
					write(sock_conn, buff2, strlen(buff2));
					return;
				}
			} else {
				strcpy(buff2, "Error: Formato de nombre incorrecto");
				write(sock_conn, buff2, strlen(buff2));
				return;
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
			write(sock_conn, buff2, strlen(buff2));
		}
			
		if (codigo ==3) //piden consulta 1
		
		if (codigo ==4) //piden consulta 2
		{
			char nombrePokemon[50] = "";
			
			// Extraer el nombre del Pokemon que en�a el cliente
			char *p = strtok(consulta, ",");
			if (p != NULL) {
				strcpy(nombrePokemon, p);
			} else {
				strcpy(buff2, "Error: Formato incorrecto");
				write(sock_conn, buff2, strlen(buff2));
				return;
			}
			
			printf("Buscando Pokemon -> Nombre: '%s'\n", nombrePokemon);
			// Consulta SQL para obtener toda la informacion del Pokemon
			char query[512];
			sprintf(query, "SELECT hp, ataquees, descripcion FROM Pokedex WHERE nombrePokemon = '%s';", nombrePokemon);
			
			// Ejecutar consulta
			if (mysql_query(conn, query) == 0) {
				MYSQL_RES *res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);
				if (row) {
					// Construimos la respuesta con los tres campos: vida, ataques y descripción
					sprintf(buff2, "Vida: %s, Ataques: %s, Descripcion: %s", row[0], row[1], row[2]);
				} else {
					strcpy(buff2, "Error: Pokemon no encontrado");
				}
				mysql_free_result(res);
			} else {
				strcpy(buff2, "Error: Problema con la base de datos");
			}
			
			// Enviar respuesta al cliente
			write(sock_conn, buff2, strlen(buff2));
		}
		
		if (codigo ==5) //piden consulta 3
			

		
	
		printf ("%s\n", buff2);
		// Y lo enviamos
		write (sock_conn,buff2, strlen(buff2));
		
		// Se acabo el servicio para este cliente
		//close(sock_conn); 
	}
}
