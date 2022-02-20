# ESCRIBIR EN SHELL CON LENGUAJE DE PROGRAMACION C

Esto esta sacado de <a href="https://brennan.io/2015/01/16/write-a-shell-in-c/">Write Shell C</a>
Es necesario un compilador para crear el archivo .exe de C.
El famoso compilador es gcc.
Una vez realizada la instalacion del compilador podemos realizar este comando para ejecutar el programa y crear el .exe.

```bash
    gcc <nombre_archivo.c> -o <nombre_que_se_quiere_dar>
```

## Basicos ciclos de vida de SHELL

<ul>
    <li>
        <b>Inicialización:</b> iniciamos la consola, en este paso un shell leería y ejecutaría sus archivos de configuracion
    </li>
    <li>
        <b>Interprete:</b> el shell lee los comando de stdin(liberias o archivos entrada de datos) y los ejecuta
    </li>
    <li>
        <b>Finalizar:</b> se ejecuta sus comandos y apaga, libera memoria y finaliza.
    </li>
</ul>
Nuestro shell será  muy simple.

## Bucle basico.

Principios del Local shell. El CLI tiene unas series de principios como leer, analizar y ejecutar los datos de entra introducido por el usuario.
La funcion la llamaremos <i>lsh_loop(void)</i> esta funcion no devuelve nada pero nos realiza el bucle que es lo principal para un command line.
Dentro de dicha funcion se realizan operaciones de lectura de comandos, division de linea de argumentos y ejecucion de los argumentos.

```bash
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
```
