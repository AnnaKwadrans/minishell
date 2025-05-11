#include "../data.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

char	**ft_full_split(char *s, char c);

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

char *without_last_spaces(char *str)
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
	char *delimiter = NULL;
	char **temp = NULL;

	temp = ft_full_split(line, ' ');
	if (temp == NULL)
	{
		printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	while (temp[i] != NULL)
	{
		if (ft_strncmp(temp[i], "<<", 2) == 0 && temp[i + 1] != NULL)
		{
			delimiter = ft_strdup(temp[i + 1]);
			free_array(temp);
			return (delimiter);
		}
		i++;
	}
	return (delimiter);
}

void	here_doc_mode(char *line)
{
	char	*delimiter = NULL;
	char	*new_line = NULL;
	char	**buffer = NULL;
	int		i = 0;


	printf("<< HERE_DOC MODE RUNNING >>\n");
	setup_heredoc_signals();
	delimiter = get_delimiter(line);
	if (delimiter == NULL)
	{
		printf("Error: No delimiter provided\n");
		restore_signals();
		return;
	}
	if (ft_strncmp(delimiter, "EOF", 4) == 0)
		printf("delimeter is: EOF\n");
	else
		printf("delimeter is: %s\n", delimiter);
	printf("here_doc > ");
	while (1)
	{
		fflush(stdout);
		new_line = without_last_spaces(get_next_line(STDIN_FILENO));
		if (g_heredoc_interrupted)
		{
			printf("<<< HERE_DOC MODE INTERRUPTED\n");
			free(new_line);
			free(delimiter);
			free_array(buffer);
			restore_signals();
			return;
		}
		if (!new_line)
		{
			printf("warning: heredoc delimited by end-of-file (wanted `%s`)\n", delimiter);
			free(delimiter);
			free_array(buffer);
			restore_signals();
			return;
		}
		if (ft_strncmp (new_line, delimiter, ft_strlen(delimiter)) == 0)
		{
			// printf("search for delimiter in '%s'\n", new_line);
			free(new_line);
			break;
		}
		buffer = add_buffer(buffer, new_line);
	}
	restore_signals();
	printf("<<< HERE_DOC MODE STOPPED\n");
	while (buffer[i] != NULL)
	{
		printf("buffer[%d]: %s\n", i, buffer[i]);
		i++;
	}
	free(new_line);
	free(delimiter);
	free_array(buffer);
}
	
int is_here_doc(char *line)
{
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '<')
		{
		 	if (line[i + 1] == '<' && line[i + 2] == ' ')
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
	char *line;

	line = readline("test >");
	while (1)
	{
		if ((ft_strncmp(line, "here_doc", 8) == 0) && is_here_doc(line))
		{
			here_doc_mode(line);
			printf("\t !!! here should make execve !!!\n");
		}
		else if (ft_strncmp(line, "exit", 4) == 0)
		{
			printf("Exiting...\n");
			free(line);
			return (0);
		}
		line = readline("test >");
	}
}


// FALTARÍA CORREGIR Y HACER QUE HERE_DOC DEVUELVA EL BUFFER. 
// LUEGO SERÁ ESTE BUFFER LOS QUE SE EJECUTARÁ CON EL CMD AL INICIO DE CADA TOKEN.
