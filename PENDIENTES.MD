# REDIRECCIONES (HECHO)

    cat <" fd1 "<" fd2 "<" fd3 > fasdf sa sdfsd"
    no tiene que pasar el executor si la verificaci'on da error - distinguir entre comando (exit) y builtin

split()
0 cat
1 " fd1 " >> "fd1"
2 " fd2 " >> "fd2"
3 " fd3 > fsfgdfg sdf" >> "fd3"

    debería verificar los 3 fd e imprimir error en el primero que encuentre. de no encontrar errores, la rediección final será la del último fd.

---

# COMANDOS VACÍOS

## manejo errores del cat predeterminado.(HECHO)

Línea vacía:

```bash
minishell > "      "
```

inicia un cat por predeterminado. debería sólo generar otro prompt.

## Línea con NADA genera un SEGFAULT (HECHO)

con:

```bash
minishell > ""
```

el programa explota por SEGFAULT. Deberíamos manejar ese error. ZSH retorna un error de permisos (?) y **no ejecuta nada**

---

# ECHO (HECHO)

debería haber sólo "-n" o "-nnnnnnn" para que imprima. todo lo demás, deberá imprimir incluido el intento de flag.

---

# EXPAND VARS (HECHO)

manejo de comillas dobles, imprime innecesariamente. Y expansión regulada por un verificador que debemos implementar.

---

# PIPES (HECHO)

Errores de memoria (double free).

# ELIMINAR FLAGS

El proyecto, según subject, debe compilar sólo con las flags -Wextra -Werror -Wall

# ECHO (HECHO)

Echo sin argumentos retorna SEGFAULT:

==64367==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000100d36b94 bp 0x00016f0caf20 sp 0x00016f0caeb0 T0)
==64367==The signal is caused by a READ memory access.
==64367==Hint: address points to the zero page.
#0 0x000100d36b94 in ft_strncmp+0x44 (minishell:arm64+0x100002b94)
#1 0x000100d3c3e0 in ft_builtin+0x44 (minishell:arm64+0x1000083e0)
#2 0x000100d3bfd8 in exec_builtin+0x58 (minishell:arm64+0x100007fd8)
#3 0x000100d3bc80 in execute_line+0xdc (minishell:arm64+0x100007c80)
#4 0x000100d3e2e8 in main+0xc4 (minishell:arm64+0x10000a2e8)
#5 0x0001929beb94 in start+0x17b8 (dyld:arm64e+0xfffffffffff3ab94)

# $\_ . (HECHO)

Debería actualizar la lista de variables de entorno, sobretodo, la variable "\_" (el último argumento del último comando ejecutado). Ejemplo:

```bash
    echo hola > f1"
```

Y luego,

```bash
    "echo $_ "
```

cat -e fd1.txt
$\_ = fd1.txt

ls -l
$\_ = -l

pwd
$\_ = pwd

" "
$\_ = \n

debería retornar: "hola"

En caso de que lo último ejecutado, sea un ejecutable, debería salir la ruta del ejecutable.
Cuando se trata de una expansión de variables, esta variable ($\_) no debe actualizar.

$\_

# EJECUTAR MINISHELL DENTRO DE MINISHELL (HECHO, pero pendiente el valor de la variable SHLVL)

# CORRECCIÓN ALTERNA

1.⁠ ⁠Historial (los comandos vacíos) (ME PARECE QUE FUNCIONA)
 2.⁠ ⁠"" o ' ' (segfault) (HECHO)
 3.⁠ ⁠Echo $a""a > $a( ) a >> a a (ELIMINA $, TIENE QUE SER ASÍ SI NO EXISTE LA VARIABLE?)
 4.⁠ ⁠Echo $kk tomate (FUNCIONA)
 5.⁠ ⁠Echo patata "" tomate (HECHO)
 6.⁠ ⁠Export kk="echo tomate". $kk

<!--  7.⁠ ⁠Exit con los long XXXXXXX -->

10.⁠ ⁠Variable global: ^C y después $? debería salir 130 y el nuestro sale 0.

<!-- 11.⁠ ⁠> kk (segfault) -->
<!-- 12.⁠ ⁠Cuando hay PATH, hay que indicar la ruta, pero cuando no hay PATH (porque se ha hecho unset), busca en la propia carpeta donde estás.
13.⁠ ⁠< cat (segfault) -->

11. leaks:
    $?
    $

# Actualizar \_ antes del fork, al menos en ENV

# BUILTINS

ECHO
echo $? $USER $HOME (solo expande $?)
echo $ y echo "$"
echo $?hola
echo '$PWD'

EXPORT (HECHO)
export hello
export "GHI=abc hola"
Valid variable names:
export MY_VAR=value # Starts with letter
export \_MY_VAR=value # Starts with underscore
export MY-VAR=value # Contains hyphen (but not at start)
export MY_VAR_1=value # Contains numbers after letters
Invalid attempts:
export -VAR=value # ❌ Starts with hyphen
export VAR-=value # ❌ Contains -=
export =VALUE # ❌ Starts with equals sign
export @VAR=value # ❌ Contains special character

CD (hecho)
actualizar variable PWD
cd $PWD hola -> err too many arguments
cd 123 -> err no such dir ->exit code 1

# PIPES (hecho)

env | grep HOME
ls | grep c | env
(exits minishell)

# unclosed fds (hecho)
ps | grep minishell | awk '{print $1}' | xargs lsof -p

# export sin argumentos: sort envs y print  (hecho) 
# export: norm too many lines

# join arrays norm: too long

# exit: >1 args y texto (HECHO)

PROBLEMS:
here_doc.c sigint.c signals.c 

export -> segfult
exit con palabra -> codigo salida 2
cd - -> va al directorio anterior
se borra PATH en heredoc y en validator
no debe guardar espacios en el historico
codigo salida del validator