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
void rl_replace_line(const char *text, int clear_undo);


volatile sig_atomic_t g_heredoc_interrupted = 0;

//  sig_atomic_t
// 	•	Es un tipo definido por la biblioteca estándar de C (viene de <signal.h>).
// 	•	Es un tipo entero garantizado para poder ser accedido y modificado de forma atómica por una señal. 
//		Esto significa que el acceso no puede ser interrumpido, lo cual es importante cuando se trabaja con manejadores de señales (signal handlers).
// ⚠️ Si una señal interrumpe la ejecución del programa, puede modificar esta variable sin provocar un comportamiento indefinido.

// volatile
// 	•	Informa al compilador que la variable puede cambiar en cualquier momento 
//		fuera del control del flujo del programa (por ejemplo, desde un signal handler).
// 	•	Esto impide optimizaciones que podrían suponer que el valor no cambia “mágicamente”.
// En otras palabras, volatile dice: “compilador, no hagas suposiciones sobre esta variable”.
// Por ejemplo:
//
// int running = 1;
// while (running) { hacer algo... }
// El compilador podría asumir que running nunca cambia y podría optimizarlo así:
// while (1) { /* hacer algo... */ }
// PERO, si otra parte del programa modifica running, entonces esa optimización crearía un bucle infinito.



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

void free_here_doc(t_heredoc *here_doc)
{
	if (here_doc)
	{
		if (here_doc->delimiter)
			free(here_doc->delimiter);
		if (here_doc->buffer)
			free_array(here_doc->buffer);
		free(here_doc);
	}
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
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 1);
	free(str);
	return (new_str);
}

char **add_buffer(char **buffer, char *line)
{
	int		count = 0;
	int		i = 0;
	char	**temp;

	printf("add_buffer: %s\n", line);
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

int check_is_expandable(char *line)
{
	int i = 0;
	int is_expandable = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			is_expandable = 1;
			i++;
			while (line[i] && line[i] != line[i - 1])
				i++;
		}
		else if (line[i] == '$')
			return (1);
		i++;
	}
	return (is_expandable);
}

char	*aux_get_delimiter(char *line)
{
	int		start = 0;
	int		end;
	char	*temp;

	while (line[start] == ' ' || line[start] == '\'' || line[start] == '\"' || line[start] == ' ')
		start++;
	end = ft_strlen(line) - 1;
	while (end > start && (line[end] == ' ' || line[end] == '\'' || line[end] == '\"'))
		end--;
	temp = malloc(sizeof(char) * (end - start + 2));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &line[start], end - start + 2);
	return (temp);
}

void get_delimiter(char *line, t_heredoc *here_doc)
{
	int i = 0;
	int start = 0;
	char *temp;
	
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			start = i + 2;
			while (line[start] == ' ')
				start++;
			while (line[start] && line[start] != ' ' && line[start] != '\n')
				start++;
			temp = malloc(sizeof(char) * (start - i + 1));
			if (!temp)
				return ;
			ft_strlcpy(temp, &line[i + 2], start - i);
			printf(">> temp is:%s\n", temp);
			here_doc->delimiter = aux_get_delimiter(temp);
			here_doc->is_expandable = check_is_expandable(temp);
			free(temp);
			return ;
		}
		i++;
	}
}

void	here_doc_init(char *line, t_heredoc *here_doc)
{
	setup_heredoc_signals();
	get_delimiter(line, here_doc);
	if (!here_doc->delimiter || *here_doc->delimiter == '\0')
	{
		printf("Parse error near `\\n`\n");
		free_here_doc(here_doc);
		restore_signals();
	}
	if (here_doc->delimiter)
		printf("delimeter is: %s\n", here_doc->delimiter);
}
void here_doc_error(t_heredoc *here_doc, char *error_msg)
{
	if (error_msg)
	{
		if (ft_strcmp(error_msg, "EOF") == 0)
			printf("EOF detected\n");
		else if (ft_strcmp(error_msg, "SIGINT") == 0)
			printf("SIGINT detected\n");
		else if (ft_strcmp(error_msg, "MALLOC") == 0)
			printf("MALLOC ERROR\n");
	}
	else
		printf("EOF detected\n");
	printf("<<----- \t HERE_DOC MODE STOPPED \t ----->>\n");
	free_here_doc(here_doc);
	restore_signals();
}

t_heredoc	*here_doc_mode(char *line)
{
	t_heredoc	*here_doc;
	char		*new_line;
	int		i = 0;


	here_doc = malloc(sizeof(t_heredoc));
	if (!here_doc)
		return (here_doc_error(here_doc, "MALLOC"), NULL);
	here_doc_init(line, here_doc);
	while (1)
	{
		write(1, "heredoc >", 10);
		new_line = remove_trailing_newline(get_next_line(STDIN_FILENO));
		if (g_heredoc_interrupted)
			return (here_doc_error(here_doc, "SIGINT"), NULL);
		if (!new_line)
			return (here_doc_error(here_doc, "EOF"), NULL);
		if (ft_strcmp (new_line, here_doc->delimiter) == 0)
			break;
		here_doc->buffer = add_buffer(here_doc->buffer, new_line);
		if (!here_doc->buffer)
			return (here_doc_error(here_doc, "MALLOC"), NULL);
	}
	free(new_line);
	return(here_doc);
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
	char		*token; // LO QUE HAY ENTRE PIPES
	t_heredoc	*here_doc;
	t_cmd		*cmd;
	int i;

	while (1)
	{
		token = readline("test >");
		if (is_here_doc(token))
		{
			here_doc = here_doc_mode(token);
			if (!here_doc)
			{
				free(token);
				continue;
			}
			printf("\t !!! here should make execve !!!\n");
			if (here_doc->buffer && here_doc->buffer[0] != NULL)
			{
				i = 0;
				while (here_doc->buffer[i] != NULL)
				{
					printf("buffer[%d]: %s\n", i, here_doc->buffer[i]);
					i++;
				}
			}
			free(here_doc->buffer);
			free(here_doc->delimiter);
			free(here_doc);
		}
		else if (ft_strcmp(token, "exit") == 0 || !token)
		{
			printf("Exiting...\n");
			free(token);
			return (0);
		}
	}
}

// PARA COMPILAR:
// cc aux/ft_full_split.c aux/array_functions.c libft/libft.a here_doc/here_doc.c -lreadline

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
