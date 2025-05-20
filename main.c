#include "data.h"
#include "parser.h"
#include "executor.h"

// void	set_raw_mode(void)
// {
// 	struct termios term;

// 	tcgetattr(STDIN_FILENO, &term); // Obtener configuración actual
// 	term.c_lflag &= ~(ICANON | ECHO); // Deshabilitar entrada en bloque y eco
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Aplicar cambios inmediatamente
// }

// void	reset_terminal_mode(void)
// {
// 	struct termios term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag |= (ICANON | ECHO); // Restaurar modo normal
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

int	count_pipes(char *input) // <- MEJOR LA FUNCION int count_pipe(char *line) PQ ESTA NO TIENE EN CUENTA COMILLAS
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

// void	get_data_program(char *input, t_data *data_program)
// {
// 	t_lines	*line;
// 	t_cmd	**cmd;

// 	line = new_line(input, data_program); // Crear nueva linea
// 	if (line == NULL)
// 	{
// 		perror("Error allocating memory for new line");
// 		return ;
// 	}
// 	data_program->pipes = count_pipes(input); // Contar pipes
// 	cmd = malloc(sizeof(t_cmd *) * (data_program->pipes + 2)); // Crear array de comandos
// 	cmd = lexer(input); // Llamar al lexer		<- ESTO SERA LA FUNCION t_cmd	**parse_line(char *input, int pipes)
// 	// EJECUTAR COMANDOS
// 	// AÑADIR VERIFICADOR SI ES UN COMANDO QUE SE LOGRÓ EJECUTAR, SINO NO SE GUARDA
// 	// SI SE USA PIPES, ¿SE GUARDAN SÓLO LOS COMANDO QUE SE PUDIERON EJECUTAR?
// 	// ¿O SIMPLEMENTE NO SE GUARDA NADA?
// 	new_line_history(line); // Guardar en historial

// }

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	static t_data	*data_program;

	(void)argc;
	(void)argv;
	(void)envp;

	data_program = malloc(sizeof(t_data));
	init_data(data_program); // lo he puesto temporalmente para poder trabajar en el lexer
	
	while (1)
	{
		if (data_program->is_interactive)
			input = readline("minishell > ");
		else
			input = get_next_line(STDIN_FILENO); // Cambiar por la función que lee del archivo
		if (!input || !input[0]) // Ctrl+D o línea vacía
		{
			free(input);
			break;
		}
		//get_data_program(input, data_program); // Configuración inicial
		// add_history(input); // Añadir al historial
		add_mhistory(data_program, input); // Añadir al historial propio
		parse_data(input, data_program, envp); // lo he puesto temporalmente para poder trabajar en el lexer
		exec_all_lines(data_program);
		clean_data_program(data_program); // lo he puesto temporalmente para poder trabajar en el lexer
		free(input);
		//ft_printer_lines(data_program->history_lines);
		//printf("**********\n");
	}
}

// PARA COMPILAR, APLICAR "-lreadline"
