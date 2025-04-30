# 9. Manejo de variables de entorno

## 📌 Qué significa

- $VAR debe expandirse a su valor.
- $? debe expandirse al código de salida del último comando.

## 🛠️ Implementación

- Usa getenv(var) para obtener el valor de $VAR.
- Usa itoa(WEXITSTATUS(status)) para $?.

## ⚠️ Errores comunes

- No expandir correctamente $VAR si está pegado a otro texto (echo "$USERhome").

  En este caso si no existe $USERhome, retorna línea vacía.

en caso:

```bash
echo "$USERhome abc"
```

Debería retornar todo lo escrito después de la variable no establecida (inexistente).

```bash
echo "error code: $?"
```

debería retornar: "error code: 127", por ejemplo.

## REALIZACIÓN

### Crear variables de entorno

Dado a que lo que recibe nuestro programa "\*\*env" es una copia de las variables originales, tendremos que copiar las variables y enlistarlas en nuestro programa.

```C
  typedef struct s_vars
  {
    char			*name; // Nombre de la variable
    char			*value; // Valor de la variable
    struct	s_vars	*next; // Siguiente variable
    int				is_exportable; // Si es exportable o no
  } t_vars;
```

### Uso de la lista de variables

Cuando detectemos que estamos asignando una variable:

```bash
MY_VAR="42"
```

añadiremos a la lista, la variable MY_VAR con el valor 42.

Y cuando detectemos que vamos a usar una variable de entorno, con el uso del '$':

```bash
echo $MY_VAR
```

tendremos que reemplazar todo el string por el valor de la variable:

```bash
echo 42
```

y finalmente, ejecutar el comando.
