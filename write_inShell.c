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
    //Esto estilo es como el antiguo codigo de C declarar antes 
    //Que el resto del codigo
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

//Lectura de linea
//Definimos el espacio en memoria que usaremos para almacenar los datos
//Buffer
#define LSH_RL_BUFFER 1024;
char *lsh_read_line(void){
    //Inicializamos las variables necesarias
    int bufsize=LSH_RL_BUFFER;
    int position=0;
    //Usa la liberia stdlib para usar malloc
    //malloc( size ) asigna la memoria dada, tamaño en bloque de memoria 
    //se usa para asignar memoria en tiempo de ejecucion
    //sizeof() nos devuelve el tamaño de un tipo de dato char,int,etc..
    char *buffer=malloc(sizeof(char)*bufsize);
    int c;
    //Verificamos si se ha asigna un valor al buffer 
    if(!buffer){
        //Sacamos por pantalla el error
        //stderr es el mensaje de error estandar para imprimir por pantalla
        fprint(stderr, "lsh: localizacion erronea. \n");
        //finalizamos las operaciones
        //EXIT_FAILURE finaliza el proceso por fallo.
        exit(EXIT_FAILURE);
    }

    //Bucle aparentemente infinito
    //Esta es la esencia de esta funcion
    while(1){
        //Lectura del carater
        //Entrada de datos del caracter
        c=getchar();
        //Verificamos si es la final de la entrada con EOF End of File
        //O si es igual a new line
        //EOF es un numero entero no un caracter
        if(c == EOF || c == '\n' ){
            buffer[position]='\0';
            return buffer;
        }else{
            buffer[position]=c;
        }
        position++;

        //Si excede el buffer o la memoria, se recolecta
        //Y y aumentamos el tamaño
        if(position>=bufsize){
            bufsize+=LSH_RL_BUFFER;
            //realloc(ptr-puntero bloque de memoria,tamaño) intenta cambiar el tamaño del bloque de memoria
            //al que apunta ptr, usa la libreria stdlib.h
            buffer=realloc(buffer,bufsize);
            //Verificamos si se ha asigna un valor al buffer 
            if(!buffer){
                //Sacamos por pantalla el error
                //stderr es el mensaje de error estandar para imprimir por pantalla
                fprint(stderr, "lsh: localizacion erronea. \n");
                //finalizamos las operaciones
                //EXIT_FAILURE finaliza el proceso por fallo.
                exit(EXIT_FAILURE);
            }
        }
    }

}