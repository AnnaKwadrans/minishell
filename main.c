#include "data.h"
#include "lexer.h"

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

int	count_pipes(char *input)
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

void	get_data_program(char *input, t_data *data_program)
{
	t_lines	*line;
	t_cmd	**cmd;

	line = new_line(input, data_program); // Crear nueva linea
	if (line == NULL)
	{
		perror("Error allocating memory for new line");
		return ;
	}
	data_program->pipes = count_pipes(input); // Contar pipes
	cmd = malloc(sizeof(t_cmd *) * (data_program->pipes + 2)); // Crear array de comandos
	cmd = lexer(input); // Llamar al lexer
	// EJECUTAR COMANDOS
	// AÑADIR VERIFICADOR SI ES UN COMANDO QUE SE LOGRÓ EJECUTAR, SINO NO SE GUARDA
	// SI SE USA PIPES, ¿SE GUARDAN SÓLO LOS COMANDO QUE SE PUDIERON EJECUTAR?
	// ¿O SIMPLEMENTE NO SE GUARDA NADA?
	new_line_history(line); // Guardar en historial

}

int	main(void)
{
	char			*input;
	static t_data	*data_program;

	data_program = malloc(sizeof(t_data));
while (1)
	{
		input = readline("minishell > ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		get_data_program(input, data_program); // Configuración inicial

		free(input);
		ft_printer_lines(data.history_lines);
		printf("**********\n");
	}
}

// PARA COMPILAR, APLICAR "-readline"
