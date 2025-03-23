#include <termios.h>
#include <unistd.h>
#include <stdio.h>

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

int	main(void)
{
	char *str;
	int i = 0;

	set_raw_mode();
	printf("Presiona una tecla (Ctrl+D para salir):\n");
	while (read(STDIN_FILENO, &str, 2) > 0)
		printf("Tecla presionada[%d]: %s\n", i++, str);
	reset_terminal_mode();
	return (0);
}
