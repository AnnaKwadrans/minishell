# MINISHELL

1.  [Recomendaciones](../minishell%202/manual.md#recomendaciones)
    a.  [Leer y entender el subject](#1-lee-bien-el-subject)
    b.  [Divide el proyectos](#2-divide-el-proyecto-en-módulos)
    c.  [Crea la estructura](#3-define-una-buena-estructura-de-datos)
    d.  [Usar readline y termios](#4-usa-readline-y-termios)
    e.  [Buen uso de la memoria](#5-maneja-bien-la-memoria)
    f.  [Empieza con lo básico](#6-empieza-con-lo-básico)
    g.  [Pruebas constantes](#7-prueba-constantemente)
2.  [Subject](#subject)
    a.  [Funciones autorizadas](#funciones-autorizadas)
    b.  [Requerimientos](#requerimientos)
    c.  [Resumen](#resumen)

## RECOMENDACIONES:

### 1. Lee bien el subject

Antes de empezar, asegúrate de entender todas las reglas y restricciones. Minishell tiene muchas especificaciones que pueden ser fáciles de pasar por alto.

---

### 2. Divide el proyecto en módulos

Minishell puede parecer abrumador si intentas hacer todo de golpe. Te recomiendo dividirlo en partes manejables:

✅ Lexer → Divide la entrada en tokens.

✅ Parser → Organiza los tokens en una estructura válida (árbol de ejecución o lista).

✅ Expansiones → Maneja variables de entorno ($VAR), *, ~, etc.

✅ Ejecutor → Ejecuta comandos y gestiona pipes/redirecciones.

✅ Built-ins → Implementa comandos internos como cd, echo, exit, etc.

✅ Señales → Maneja CTRL+C, CTRL+D, CTRL+\.

✅ Herencia y pipes → Maneja |, <, >, <<, >>.

---

### 3. Define una buena estructura de datos

Tener una estructura clara te ayudará mucho. Algo como:

```c
    typedef struct s_cmd
    {
        char **args;
        char *infile;
        char *outfile;
        int append;
        struct s_cmd *next;
    } t_cmd;
```
Podría ser útil para representar los comandos en una lista encadenada.

---

### 4. Usa readline y termios

-	readline() → Para capturar la entrada del usuario y manejar el historial.
-	termios → Para desactivar el echo de CTRL+C y CTRL+D.

---

### 5. Maneja bien la memoria

-	Minishell usa muchas listas y asignaciones dinámicas, así que usa valgrind con frecuencia.
-	Libera bien la memoria en cada ejecución.

---

### 6. Empieza con lo básico

Haz que tu shell pueda ejecutar comandos simples primero, luego agrega tuberías y redirecciones.

---

### 7. Prueba constantemente

Crea un script con casos de prueba para comandos, pipes, redirecciones y señales.

---

### 🚀 Consejo extra

No intentes replicar Bash al 100%. El objetivo es que funcione bien con lo básico y que siga las reglas del proyecto.

---

## SUBJECT

### Funciones autorizadas:

#### Librería Readline (manejo de entrada)

Estas funciones son útiles para capturar y gestionar la entrada del usuario.

✅ readline(prompt) → Muestra un prompt y espera a que el usuario escriba. Devuelve la línea ingresada.

✅ add_history(line) → Guarda la línea ingresada en el historial para poder navegar con las flechas ↑ ↓.

✅ rl_clear_history() → Borra el historial de entrada.

✅ rl_on_new_line() → Indica que se ha empezado una nueva línea.

✅ rl_replace_line("texto", 0) → Reemplaza la línea actual en el prompt sin imprimirla.

✅ rl_redisplay() → Redibuja el prompt con la línea actual (útil cuando se manejan señales).

⸻

#### Entrada y salida estándar (I/O)

✅ printf() → Imprime texto en la salida estándar.

✅ write(fd, buf, count) → Escribe count bytes desde buf en el descriptor de archivo fd.

✅ read(fd, buf, count) → Lee count bytes desde fd hacia buf.

✅ access(path, mode) → Verifica si un archivo existe o si se tienen permisos de acceso (F_OK, R_OK, etc.).

⸻

#### Manejo de archivos

✅ open(path, flags, mode) → Abre un archivo y devuelve su descriptor (fd). Puede crear archivos si no existen.

✅ close(fd) → Cierra el descriptor de archivo fd.

✅ unlink(path) → Elimina un archivo.

✅ stat(path, struct stat *buf) → Obtiene información sobre un archivo (tamaño, permisos, etc.).

✅ lstat(path, struct stat *buf) → Igual que stat(), pero si es un enlace simbólico, obtiene info del enlace en sí.

✅ fstat(fd, struct stat *buf) → Igual que stat(), pero usa un descriptor de archivo en lugar de una ruta.

⸻

#### Manejo de procesos

✅ fork() → Crea un nuevo proceso duplicando el actual. Devuelve 0 en el hijo y el PID del hijo en el padre.

✅ execve(path, argv, envp) → Reemplaza el proceso actual por un nuevo programa ejecutable.

✅ wait(&status) → El padre espera a que un proceso hijo termine.

✅ waitpid(pid, &status, options) → Similar a wait(), pero espera a un proceso específico (pid).

✅ wait3(&status, options, struct rusage *rusage) → Como waitpid(), pero con info sobre uso de recursos.

✅ wait4(pid, &status, options, struct rusage *rusage) → Igual que wait3(), pero puede esperar a un PID específico.

⸻

#### Manejo de señales

✅ signal(signum, handler) → Asigna un manejador de señales para signum.

✅ sigaction(signum, struct sigaction *act, struct sigaction *oldact) → Versión más avanzada de signal().

✅ kill(pid, sig) → Envía una señal sig a un proceso con ID pid.

⸻

#### Directorios

✅ opendir(path) → Abre un directorio para leer su contenido.

✅ readdir(DIR *dirp) → Lee una entrada del directorio abierto.

✅ closedir(DIR *dirp) → Cierra el directorio.

⸻

#### Manejo del entorno

✅ getcwd(buf, size) → Obtiene el directorio actual y lo guarda en buf.

✅ chdir(path) → Cambia el directorio de trabajo del proceso actual.

✅ getenv("VAR") → Obtiene el valor de una variable de entorno (PATH, HOME, etc.).

⸻

#### Redirección y duplicación de fds

✅ dup(fd) → Duplica un descriptor de archivo y devuelve uno nuevo.

✅ dup2(fd, new_fd) → Duplica fd y lo asigna a new_fd (útil para redirecciones).

✅ pipe(int fd[2]) → Crea un pipe con dos extremos (fd[0] lectura, fd[1] escritura).

⸻

#### Manejo de terminales

✅ isatty(fd) → Verifica si un fd es un terminal (útil para saber si Minishell está en una terminal interactiva).

✅ ttyname(fd) → Obtiene el nombre del terminal asociado a fd.

✅ ttyslot() → Obtiene el número de terminal en uso.

✅ ioctl(fd, request, …) → Controla dispositivos de entrada/salida (usado para terminales).

✅ tcgetattr(fd, struct termios *termios_p) → Obtiene atributos de la terminal.

✅ tcsetattr(fd, optional_actions, const struct termios *termios_p) → Modifica atributos de la terminal.

⸻

#### Manejo de errores

✅ strerror(errno) → Devuelve una string con la descripción de un error (errno).

✅ perror(msg) → Imprime msg seguido de la descripción del último error (errno).

⸻

### Requerimientos:

#### 1. Mostrar una entrada mientras espera un comando nuevo

📌 ¿Qué significa?

-   Tu Minishell debe mostrar un prompt (ejemplo: minishell$ ) y esperar a que el usuario ingrese un comando.

🛠️ Implementación

-	Usa readline("minishell$ ") para obtener la entrada del usuario.
-	Si el usuario no escribe nada y presiona Enter, el prompt debe reaparecer sin hacer nada.

⚠️ Errores comunes

-	No mostrar el prompt correctamente (ejemplo: si readline() no se ejecuta dentro de un bucle).
-	No manejar EOF (Ctrl+D) → Si readline() devuelve NULL, debes terminar el shell limpiamente.

---

#### 2. Tener un historial funcional

📌 ¿Qué significa?

-   El shell debe recordar los comandos previos para que el usuario pueda navegar con las flechas ↑ y ↓.

🛠️ Implementación

-	Usa add_history(input) para agregar cada comando ingresado al historial.
-	Usa rl_clear_history() si quieres resetear el historial en algún punto.

⚠️ Errores comunes

-	No guardar los comandos porque add_history() no se llama correctamente.
-	Historial perdido al reiniciar el shell → readline() no guarda el historial en un archivo por defecto.

---

#### 3. Buscar y ejecutar el ejecutable correcto

📌 ¿Qué significa?

-   Debes buscar comandos en la variable PATH o aceptar rutas absolutas (/bin/ls) y relativas (./a.out).

🛠️ Implementación

-	Usa getenv("PATH") para obtener los directorios donde buscar los ejecutables.
-	Divide PATH en rutas y prueba cada una con access(path, X_OK).
-	Usa execve(path, args, envp) para ejecutar el programa.

⚠️ Errores comunes

-	No manejar PATH vacío → Si getenv("PATH") es NULL, solo puedes ejecutar con rutas absolutas.
-	No mostrar error si el comando no existe (command not found).
-	Olvidar liberar memoria tras dividir PATH.

---

#### 4. No usar más de una variable global para señales

📌 ¿Qué significa?

-   Solo puedes usar una variable global para manejar señales, y solo para guardar el número de la señal recibida.

🛠️ Implementación

-	Declara volatile sig_atomic_t g_signal = 0;
-	Usa signal(SIGINT, handler), donde handler solo modifica g_signal.
-	Maneja la señal en el loop principal sin acceder a estructuras globales.

⚠️ Errores comunes

-	Intentar acceder a estructuras en el handler, lo cual puede romper el programa.
-	Modificar g_signal en lugares innecesarios.

---

#### 5. No interpretar comillas sin cerrar o caracteres especiales como ; o \

📌 ¿Qué significa?

-   Si el usuario escribe echo "hola, Minishell no debe intentar ejecutarlo, sino mostrar un error.

🛠️ Implementación

-	Lleva un contador de comillas (' y ").
-	Si hay un número impar de comillas al final de la línea, muestra syntax error: unclosed quotes.
-	Ignora ; y \, ya que no son metacaracteres permitidos.

⚠️ Errores comunes

-	No detectar comillas sin cerrar.
-	Interpretar ; o \ como válidos, lo cual no es necesario.

⸻

####  6. Manejo de comillas

📌 ¿Qué significa?

-	Comillas simples ' ' → Todo dentro se trata como texto literal, sin expansión de variables.
-	Comillas dobles " " → Se expande $VAR, pero otros caracteres (*, |) se tratan como texto.

🛠️ Implementación

-	Cuando parses el input, detecta las comillas y elimina las correctas según su tipo.
-	Expande variables dentro de comillas dobles pero no simples.

⚠️ Errores comunes

-	Expandir $VAR dentro de ' ', lo cual es incorrecto.
-	No cerrar comillas correctamente al ejecutar el comando.

⸻

#### 7. Implementar redirecciones

📌 Qué significa

-	'<' → Redirige la entrada desde un archivo.
-	'>' → Redirige la salida a un archivo (sobreescribe).
-	'>>' → Redirige la salida en modo append.
-	'<<' (heredoc) → Lee input hasta un delimitador.

🛠️ Implementación

-	Usa open(filename, O_RDONLY) para <.
-	Usa open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644) para >.
-	Usa open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644) para >>.
-	Para heredoc, lee el input en un loop hasta encontrar el delimitador.

⚠️ Errores comunes

-	No cerrar fds después de redirigir.
-	No manejar archivos inexistentes con <.

⸻

####  8. Implementar pipes

📌 ¿Qué significa?

Debe permitir comandos encadenados como ls | grep txt | wc -l.

🛠️ Implementación

-	Usa pipe(fd).
-	Redirige la salida del primer comando (dup2(fd[1], STDOUT_FILENO)).
-	Redirige la entrada del segundo comando (dup2(fd[0], STDIN_FILENO)).
-	Usa fork() y execve() para cada proceso.

⚠️ Errores comunes

-	No cerrar correctamente fd, causando fugas de descriptores.
-	No esperar a que todos los procesos terminen (waitpid()).

---

####  9. Manejo de variables de entorno

📌 Qué significa

-	$VAR debe expandirse a su valor.
-	$? debe expandirse al código de salida del último comando.

🛠️ Implementación

-	Usa getenv(var) para obtener el valor de $VAR.
-	Usa itoa(WEXITSTATUS(status)) para $?.

⚠️ Errores comunes

-	No expandir correctamente $VAR si está pegado a otro texto (echo "$USERhome").

    ---

#### 10. Built-ins

📌 Qué significa

-   Debes implementar echo, cd, pwd, export, unset, env, exit.

⚠️ Errores comunes

-	No validar argumentos (cd sin ruta, export sin =).
-	No manejar exit con números grandes.

### Resumen:

1️⃣ Empieza con el prompt y lectura de comandos.

2️⃣ Haz un parser básico para detectar pipes y redirecciones.

3️⃣ Implementa ejecución de comandos externos (execve).

4️⃣ Añade built-ins y expansión de variables.