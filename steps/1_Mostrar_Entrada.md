#### 1. Mostrar una entrada mientras espera un comando nuevo

📌 ¿Qué significa?

- Tu Minishell debe mostrar un prompt (ejemplo: minishell$ ) y esperar a que el usuario ingrese un comando.

🛠️ Implementación

- Usa readline("minishell$ ") para obtener la entrada del usuario.
- Si el usuario no escribe nada y presiona Enter, el prompt debe reaparecer sin hacer nada.

⚠️ Errores comunes

- No mostrar el prompt correctamente (ejemplo: si readline() no se ejecuta dentro de un bucle).
- No manejar EOF (Ctrl+D) → Si readline() devuelve NULL, debes terminar el shell limpiamente.

Utilizaremos readline y lo añadiremos al historial.

```c
	char *input;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		add_history(input); // Guardar en historial
		free(input);
	}
```
