#include "data.h"

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
	if (!fd_history)
		ft_strjoin(fd_history, "/t1");
	ft_strjoin(fd_history, "/t");
	// AÑADIR NUMERACIÓN 
			// LEER NÚMERO Y +1
	ft_strjoin(fd_history, "/t");
	ft_strjoin(fd_history, line);
	ft_strjoin(fd_history, "/n");

}

int	main(void)
{
	char *input;
	int fd_history;

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
		free(input);
	}
}

// PARA COMPILAR, APLICAR "-readline"
