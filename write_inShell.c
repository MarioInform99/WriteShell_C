#include <stdio.h>//Estadar de input output
#include <stdlib.h> //Estandar de libreria
int main(int argc, char **argv)
{
    //Ejecutamos el bucle que tenemos como funcion
    lsh_loop();
    return 0;
}

//Bucle basico Local Shell
//Leer-Analizar-Ejecutarw
//Este bucle no devuelve nada
void lsh_loop(void){
    //Declaraciones de variables
    char *line;
    char **args;
    int status;
    //Bucle o loop el do{}while es para verificar la variable del estado
    //Para ejecutar una vez antes de verificar su valor.
    do{
        printf("> ");
        //Funcion de lectura de comandos
        line=lsh_read_line();
        //Funcion para dividir la linea de argumentos
        args=lsh_split_line(line);
        //Ejecutamos los argumentos
        status=lsh_execut(args);

        //Liberamos las variables c0n la funcion free()
        free(line);
        free(args);
    }while(status);
}
