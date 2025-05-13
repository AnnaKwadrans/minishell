#include "../data.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

char	**ft_full_split(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);

volatile sig_atomic_t g_heredoc_interrupted = 0;

void sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
}

void setup_heredoc_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char *remove_trailing_newline(char *str)
{
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len + 1);
	return (new_str);
}

char **add_buffer(char **buffer, char *line)
{
	int		count = 0;
	int		i = 0;
	char	**temp;

	while (buffer && buffer[count])
		count++;
	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return (NULL);
	while(i < count)
	{
		temp[i] = ft_strdup(buffer[i]);
		if (!temp[i])
		{
			free_array(temp);
			return (NULL);
		}
		i++;
	}
	temp[count] = ft_strdup(line);
	temp[count + 1] = NULL;
	if (buffer)
		free_array(buffer);
	return (temp);
}

char *get_delimiter(char *line)
{
	int i = 0;
	int start = 0;
	char *delimiter = NULL;
	
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
		{
				i += 2;
				while (line[i] == ' ')
					i++;
				if (!line[i])
				{
					printf("Parse error near `\\n`\n");
					return (NULL);
				}
				start = i;
				while (line[i] && line[i] != ' ')
					i++;
				delimiter = malloc(i - start + 1);
				if (!delimiter)
					return (NULL);
				ft_strlcpy(delimiter, &line[start], i - start + 1);
				delimiter[i - start] = '\0';
				return (delimiter);
			}
		i++;
	}
	return (NULL);
}

char	**here_doc_mode(char *line)
{
	char	*delimiter = NULL;
	char	*new_line = NULL;
	char	**buffer = NULL;
	int		i = 0;


	printf("<< HERE_DOC MODE RUNNING >>\n");
	setup_heredoc_signals();
	delimiter = get_delimiter(line);
	if (!delimiter || *delimiter == '\0')
	{
		printf("Parse error near `\\n`\n");
		restore_signals();
	    return (NULL);
	}
	if (ft_strncmp(delimiter, "EOF", 4) == 0)
		printf("delimeter is: EOF\n");
	else
		printf("delimeter is: %s\n", delimiter);
	printf("here_doc > ");
	while (1)
	{
		fflush(stdout);
		new_line = remove_trailing_newline(get_next_line(STDIN_FILENO));
		if (g_heredoc_interrupted)
		{
			printf("<<< HERE_DOC MODE INTERRUPTED\n");
			free(new_line);
			free(delimiter);
			free_array(buffer);
			restore_signals();
			return (NULL);
		}
		if (!new_line)
		{
			printf("EOF found without the delimeter\n");
			free(delimiter);
			free_array(buffer);
			restore_signals();
			return (NULL);
		}
		if (ft_strcmp (new_line, delimiter) == 0)
			break;
		buffer = add_buffer(buffer, new_line);
		if (!buffer)
		{
			printf("Error: Memory allocation failed\n");
			free(new_line);
			free(delimiter);
			restore_signals();
			return (NULL);
		}
	}
	restore_signals();
	printf("<<< HERE_DOC MODE STOPPED\n");
	return(buffer);
}
	
int is_here_doc(char *line)
{
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '<')
		{
		 	if (line[i + 1] == '<' && line[i + 2] != '<')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int main(void)
{
	char *token; // LO QUE HAY ENTRE PIPES
	char **buffer = NULL;
	int i = 0;

	while (1)
	{
		token = readline("test >");
		if (is_here_doc(token))
		{
			buffer = here_doc_mode(token);
			printf("\t !!! here should make execve !!!\n");
			if (buffer)
			{
				while (buffer[i] != NULL)
				{
					printf("buffer[%d]: %s\n", i, buffer[i]);
					i++;
				}
			}
		}
		else if (ft_strncmp(token, "exit", 4) == 0 || !token)
		{
			printf("Exiting...\n");
			free(token);
			return (0);
		}
	}
}


// PENDIENTE:


// Detectar si el delimitador está en comillas simples, dobles o sin comillas.

// Si está en comillas simples, no se debe expandir.

	// cat << EOF
	// Hola $USER
	// Fecha: `date`
	// EOF

	// Hola tu_nombre_de_usuario
	// Fecha: Sun May 11 12:34:56 UTC 2025

	// •	Se expanden variables ($USER) y comandos (`date`).
	// •	El delimitador EOF puede estar en cualquier lugar mientras esté solo en una línea.

	// kev@MacBook-Air-de-Kevin minishell % cat << EOF
	// heredoc> hello $USER
	// heredoc> date: `date`
	// heredoc> EOF
	// hello kev
	// date: martes, 13 de mayo de 2025, 01:32:36 CEST

// Si está en comillas dobles, se debe expandir.

	// cat << "EOF"
	// Hola $USER
	// Fecha: `date`
	// EOF

	// Hola $USER
	// Fecha: `date`

	// •	No se expande nada.
	// •	El delimitador "EOF" debe coincidir exactamente con "EOF" 
	// 	(aunque el shell lo reconoce bien sin comillas al cerrar).

	// kev@MacBook-Air-de-Kevin minishell % cat << "EOF"
	// heredoc> hello $USER
	// heredoc> date `date`
	// heredoc> EOF
	// hello $USER
	// date `date`

// Si no está en comillas, se debe expandir.

// 	cat << 'EOF'
// 	Hola $USER
// 	Fecha: `date`
// 	EOF

// 	Hola $USER
// 	Fecha: `date`

// 	•	Igual que el anterior: nada se expande.
// 	•	'EOF' también hace que el delimitador sea interpretado literalmente.


// 	kev@MacBook-Air-de-Kevin minishell % cat << 'EOF'
// 	heredoc> hello $USER
// 	heredoc> date `date`
// 	heredoc> EOF
// 	hello $USER
// 	date `date`

// Entonces una vez obtenido el delimitador real, 
// deberíamos tener en cuenta si el buffer será expandible.
// Esto podríamos almacenarlo en una variable para saber si el buffer es expandible o no
// para luego ejecutar y/o expandirlo en la ejecución.

// ¿USAR UNA ESTRUCTURA PARA ELLO?

// Sí

// typedef struct s_heredoc
// {
// 	char	*delimiter;    // delimitador sin comillas
// 	int		quoted;        // 0 = expandible, 1 = literal (no expandir nada)
// 	char	**buffer;      // contenido del heredoc
// }	t_heredoc;

// FALTA CONSIDERAR QUE EXISTIRÁN LÍNEAS VACÍAS EN EL BUFFER
