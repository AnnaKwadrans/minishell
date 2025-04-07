#include "data.h"
#include "lexer.h"

void	set_raw_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term); // Obtener configuración actual
	term.c_lflag &= ~(ICANON | ECHO); // Deshabilitar entrada en bloque y eco
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Aplicar cambios inmediatamente
}

void	reset_terminal_mode(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO); // Restaurar modo normal
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void	write_Minihistory(char *line, int fd_history)
{

}

void miniHistory(void *arg)
{
	t_data	*data_program;
	
	data_program = (t_data *)arg;
	ft_printer_lines(data_program->history_lines);
}

int	main(void)
{
	char *input;
	int fd_history;
	t_data	data;

	init_data(&data);
	fd_history = open(".minihistory", O_WRONLY, O_RDONLY, O_CREAT);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		add_history(input); // Guardar en historial
		write_Minihistory(input, fd_history);
		parse_data(input, &data);
		free(input);
		ft_printer_lines(data.history_lines);
		printf("**********\n");
	}
}

// PARA COMPILAR, APLICAR "-readline"
