# Escribir en SHELL con C

Esto esta sacado de <a href="https://brennan.io/2015/01/16/write-a-shell-in-c/">Write Shell C</a>.<br/>
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

## Lectura de Linea.

Existe problemas a la hora de de introducir datos usando las librerías stdin o stdio (estándares de output e input de datos), lo malo es que no sabemos de cuanto texto ingresara el usuario en la linea de comandos. Por eso debemos de crear un bloque y expandir su espacio. Por eso implementamos <i>lsh_read_line()</i><br/>

Para empezar la función establecemos la maxima capacidad de almacenamiento de datos en memoria o buffer. Comprobamos que se nos ha creado el buffer.

```bash
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
```

La esencia de de la funcion esta dentro del bucle aparentemente infinito <i>while(1)</i>. En el se leemos el o los caracteres que introduce el usuario con <i>getchar()</i> que se usa en la librería <i>stdio.h</i>, este carater leido posteriomente lo almacenamos como un <i>int</i> como como <b>char</b>. <br/>
EOF es un numero entero, no un caracter, este significa End of File, final de la entrada. Si se desea verificar EOF se debe de usar un <i>int </i> no un <i>char</i>, este es el principal común error en C.<br/>
Si es una nueva linea, lo anulamos y la devolvemos. De lo contrario añadimos el carácter a nuestra cadena existente.

```bash
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
```

Posteriormente en caso de que el tamaño que le hemos asignado anteriormente falle, aumentamos el tamaño del buffer auto-incrementandolo. Reasignamos la variable <i>buffer</i> con la funcion realloc() que intenta cambiar el tamño del bloque de memoria. Realizamos la verificación del buffer para ver si ha ido todo bien.
