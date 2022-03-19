//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	MYSQL *conn;
	int err;
	//Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char duracion[60];
	char consulta[200];
	char fecha[30];
	
	//Creamos una conexión al servidor MYSQL 
	conn = mysql_init(NULL);
	if(conn==NULL){
		printf("Error al crear la conexión:%u %s\n",
			   mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	//Inicializar la conexión
	conn = mysql_real_connect (conn, "localhost","root","mysql","BaseDatos", 0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Consulta SQL 
	//DAME EL USERNAME DEL GANADOR Y LA DURACIÓN DE LA PARTIDA 
	//QUE SE JUGO EN UNA FECHA CONCRETA
	printf("Dame la fecha\n");
	scanf("%s", fecha);
	
	strcpy(consulta,"SELECT jugador.Username, partida.Duracion FROM jugador, partida, relacion  WHERE  partida.Fecha = ' AND partida.ID = relacion.ID_P AND relacion.ID_J = jugador.ID");
	strcat(consulta,fecha);
	strcat(consulta,"'");
	
	//Construimos la consulta SQL
	err=mysql_query(conn,consulta);
	if(err!=0){
		printf("Error al consultar datos de la base\n",
			   mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		    //La columna 2 contiene la duración de la partida que son caracteres
			printf("Username:%s, Duracion:%s\n", row[0],row[0]);
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}

