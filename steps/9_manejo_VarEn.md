#### 9. Manejo de variables de entorno

📌 Qué significa

- $VAR debe expandirse a su valor.
- $? debe expandirse al código de salida del último comando.

🛠️ Implementación

- Usa getenv(var) para obtener el valor de $VAR.
- Usa itoa(WEXITSTATUS(status)) para $?.

⚠️ Errores comunes

- No expandir correctamente $VAR si está pegado a otro texto (echo "$USERhome").

  En este caso si no existe $USERhome, retorna línea vacía.

en caso:

echo "$USERhome abc"

    Debería retornar todo lo escrito después de la variable no establecida (inexistente).

echo "error code: $?"

debería retornar: "error code: 127", por ejemplo.
