# SIGNALS (SEÑALES)

Las señales en Unix son una forma de comunicación entre procesos que permiten notificar a un proceso sobre ciertos eventos. En el proyecto Minishell, las señales son clave para manejar interrupciones, suspender procesos y responder a combinaciones de teclas como Ctrl+C, Ctrl+\ y Ctrl+Z.

⸻

## Conceptos Básicos sobre Señales

Las señales son identificadas por números enteros y nombres simbólicos en <signal.h>. Algunas señales comunes que servirán en Minishell son:

| Señal | Número | Descripción |
|-------|--------|-------------|
| SIGINT | 2 | Interrumpe un proceso (enviado con Ctrl+C). |
| SIGQUIT | 3 | Termina un proceso y genera un core dump (enviado con Ctrl+\). |
| SIGTSTP | 20 | Suspende un proceso (enviado con Ctrl+Z). |
| SIGTERM | 15 | Solicita la terminación de un proceso. |
| SIGHUP | 1 | Se envía cuando la terminal se cierra. |
| SIGKILL | 9 | Mata un proceso (no se puede capturar o ignorar). |
| SIGSTOP | 19 | Suspende un proceso (no se puede capturar o ignorar). |

## Manejo de Señales en C con signal()

### Ejemplo

Para capturar y manejar señales en Minishell, usaremos signal():

```c
    #include <signal.h>
    #include <stdio.h>
    #include <unistd.h>

    void sigint_handler(int sig)
    {
        (void)sig;
        printf("\nMinishell> ");
        fflush(stdout);
    }

    int main(void)
    {
        signal(SIGINT, sigint_handler);  // Captura Ctrl+C
        while (1)
            pause(); // Espera señales
        return (0);
    }
```

### Explicación

-	signal(SIGINT, sigint_handler): Configuraremos sigint_handler() para manejar SIGINT.
-	pause(): Suspende el proceso hasta recibir una señal.

Si presionamos Ctrl+C, en vez de cerrar el programa, imprimirá un nuevo prompt.

### signal()

La nomeclatura es:

```c
#include <signal.h>

void signal(int signum, void (*handler)(int));
```

Signal escuchará la señal especificada y cuando la reciba, ejecuta la función que se le indique, omitiendo su comportamiento predeterminado.

En el ejemplo:

```c
signal(SIGINT, sigint_handler);
```

signal escuchará SIGINT (Ctrl + C) y hará la función sigint_handler.
"sigint_handler" será un función que deberá evitar cerrar el programa, que es lo que pasaría si usamos Ctrl + C durante la ejecución de Minishell.

#### Ejemplo de sigint_handler:

```c
void sigint_handler(int sig)
{
    (void)sig;  // Evita el warning de variable no usada
    printf("\n¡Se recibió SIGINT! Pero no cerramos el shell.\n");
    printf("Minishell> ");
    fflush(stdout);
}

int main(void)
{
    signal(SIGINT, sigint_handler);  // Capturar Ctrl+C

    while (1)
    {
        printf("Minishell> ");
        fflush(stdout);
        sleep(2);  // Simula esperar comandos
    }

    return (0);
}
```

#### flush()

La función fflush() en C se usa para vaciar (flush) un buffer de salida, es decir, fuerza la escritura de datos que están almacenados en un buffer en su destino final (como la pantalla o un archivo).

🔹 Uso común: Vaciar stdout

Cuando se usa printf(), el texto no se imprime inmediatamente, sino que se almacena en un buffer temporal y se envía a la terminal solo cuando:

1.	El buffer se llena.
2.	Se encuentra un salto de línea \n.
3.	Se usa fflush(stdout) para forzar la impresión.

Ejemplo:

```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Hola, esto se imprimirá luego...");
    sleep(2);
    printf(" ¡ahora!\n");
    return 0;
}
```

No imprime nada al instante, todo aparece después de 2 segundos.

Si agregamos fflush(stdout); después del primer printf(), imprime la primera parte inmediatamente:

```c
    printf("Hola, esto se imprimirá luego...");
    fflush(stdout);  // Fuerza la impresión inmediata
    sleep(2);
    printf(" ¡ahora!\n");
```

## Cuándo usar SIGNAL

### Inicio

Cuando estemos en el prompt principal ("**Minishell>**") deberíamos evitar que el programa se cierre, haciendo que muestre otro prompt.

```c
void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\nMinishell> ", 12);
}

int main(void)
{
    signal(SIGINT, sigint_handler);  // Captura Ctrl+C en el prompt

    while (1)
    {
        write(1, "Minishell> ", 11);
        pause();  // Espera señales
    }
}
```

### Durante la ejecución de un comando externo

Por ejemplo, si hacemos "*ls -l*", *Ctrl+C* debería terminar el proceso hijo sin afectar el shell, es decir que Minishell no debe cerrarse.

```c
pid_t pid = fork();
if (pid == 0)  // Proceso hijo (ejecuta comando)
{
    signal(SIGINT, SIG_DFL);  // Restaurar SIGINT a su comportamiento normal
    execve(cmd, args, env);
}
else  // Proceso padre (Minishell)
{
    signal(SIGINT, SIG_IGN);  // Ignorar SIGINT en el shell
    wait(NULL);  // Esperar al hijo
}
```

### Here_doc

Debería detener la entrada del here_doc, o mejor dicho, detener el modo here_doc. También **debe limpiar los buffer temporales** y, obviamente, no cerrar Minishell.

```c
void sigint_here_doc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);  // Código de error estándar para Ctrl+C
}

void start_here_doc()
{
    signal(SIGINT, sigint_here_doc);  // Capturar SIGINT en here_doc
    while (1)
    {
        char *line = readline("> ");  // Leer línea de here_doc
        if (!line)
            break;
        free(line);
    }
    exit(0);
}
```

###  En un comando en segundo plano (&)

Si hacemos *sleep 10 & ./minishell*, en principio, debería esperar 10 segundos y ejecutar el programa. No obstante, si hacemos *Ctrl + C* en la espera debería finalizar el proceso de la espera y ejecutar el programa, **sólo si Minishell es interactivo**.

Comportamiento esperado:

1️⃣ sleep 10 & inicia una espera de 10 segundos en segundo plano.
2️⃣ ./minishell se ejecuta sin esperar a que sleep termine.
3️⃣ Si presionamos Ctrl+C:

    •	Si Minishell es interactivo, Ctrl+C debe matar solo sleep y no afectar a Minishell.
    •	Si no es interactivo, el comportamiento dependerá de la configuración de señales.


#### ¿minishell es interactivo?

Se refiere a si el usuario está interactuando directamente con él en una terminal o si está recibiendo comandos desde un archivo o un script.

🔹 Tipos de ejecución en Minishell

1️⃣ Modo interactivo (El usuario escribe comandos directamente)
	
•	Se ejecuta en una terminal normal.
•	Minishell muestra un prompt (Minishell> ) y espera comandos.
•	Ejemplo:

```bash
./minishell
```

•	Aquí es donde Ctrl+C debe limpiar la línea y mostrar un nuevo prompt.

2️⃣ Modo no interactivo (Los comandos vienen de un script o un pipe)

•	No hay interacción directa con el usuario.
•	Minishell ejecuta los comandos de un archivo o pipe y luego sale.
•	Ejemplo:

```bash
echo "ls -l" | ./minishell
./minishell < script.sh
```

•	En este caso, no debería mostrar un prompt y Ctrl+C no debería afectarlo igual que en modo interactivo.

3️⃣ ¿cómo saber si Minishell es interactivo?

Con la función **isatty(STDIN_FILENO)**, que devuelve 1 si la entrada (stdin) es un terminal interactivo.

```c
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    if (isatty(STDIN_FILENO))
        printf("Minishell es interactivo\n");
    else
        printf("Minishell NO es interactivo\n");

    return 0;
}
```

4️⃣ Resumen

Si es interactivo, debes:

•	Mostrar el prompt (Minishell> ).
•	Capturar SIGINT (Ctrl+C) para evitar que cierre el shell.
•	Capturar SIGQUIT (Ctrl+\) para evitar que muestre un core dump.

Si no es interactivo, debes:

•	No mostrar el prompt.
•	No capturar señales como SIGINT, porque si el usuario manda un Ctrl + C, el shell debería terminar.

Ejemplo:

```c
if (isatty(STDIN_FILENO))
{
    signal(SIGINT, sigint_handler);  // Capturar Ctrl+C solo en modo interactivo
    while (1)
    {
        printf("Minishell> ");
        fflush(stdout);
        pause();
    }
}
else
{
    // No capturamos SIGINT en modo no interactivo
}
```
