#include "../data.h"
#include <readline/readline.h>
#include <readline/history.h>

char	**ft_full_split(char *s, char c);

char *without_last_spaces(char *str)
{
	int i = 0;
	int size = 0;

	size = ft_strlen(str);
	char *new_str = malloc(sizeof(char) * size);
	if (new_str == NULL)
		return (NULL);
	while (i < size - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char **add_buffer(char **buffer, char *line)
{
	int i = 0;
	int j = 0;
	char **temp = NULL;
	int index = 0;

	printf("\t <<<< ADDING BUFFER >>>\n");
	printf("\t line: %s\n", line);
	if (buffer == NULL)
	{
		printf("\t buffer is NULL\n");
		buffer = malloc(sizeof(char *) * 2);
		if (buffer == NULL)
			return (NULL);
		buffer[0] = ft_strdup(line);
		buffer[1] = NULL;
		return (buffer);
	}
	else
	{
		while (buffer[index])
		{
			printf("\t the last buffer[%d]: %s\n", index, buffer[index]);
			index++;
		}
		while (buffer[i] != NULL)
			i++;
		temp = malloc(sizeof(char *) * (i + 2));
		if (temp == NULL)
			return (NULL);
		while (buffer[j] != NULL)
		{
			temp[j] = ft_strdup(buffer[j]);
			j++;
		}
		temp[j] = ft_strdup(line);
		temp[j + 1] = NULL;
		free_array(buffer);
	}
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
		if (ft_strncmp(temp[i], "<<", 2) == 0)
		{
			delimiter = ft_strdup(temp[i + 1]);
			free(temp);
			return (delimiter);
		}
		i++;
	}
	return (delimiter);
}

void	here_doc_mode(char *line)
{
	char	*delimiter;
	char	*new_line;
	char	**buffer;
	int		i = 0;

	printf("here_doc > ");
	fflush(stdout);
	delimiter = get_delimiter(line);
	if (delimiter == NULL)
	{
		printf("Error: No delimiter provided\n");
		return;
	}
	// if (ft_strncmp(delimiter, "EOF", 4) == 0)
	// 	printf("delimeter is: EOF\n");
	// else
	// 	printf("delimeter is: %s\n", delimiter);
	new_line = without_last_spaces(get_next_line(STDIN_FILENO));
	buffer = NULL;
	while(ft_strncmp (new_line, delimiter, ft_strlen(delimiter)) != 0)
	{
		printf("search for delimiter in '%s'\n", new_line);
		fflush(stdout);
		buffer = add_buffer(buffer, new_line);
		free(new_line);
		new_line = without_last_spaces(get_next_line(STDIN_FILENO));
	}
	printf("<<< HERE_DOC MODE STOPPED\n");
	while (buffer[i] != NULL)
	{
		printf("buffer[%d]: %s\n", i, buffer[i]);
		i++;
	}
	free(new_line);
	free(buffer);
	free(delimiter);
}
	

int main(void)
{
	char *line;

	line = readline("test >");
	while (1)
	{
		if (ft_strncmp(line, "here_doc", 8) == 0)
		{
			printf("<< HERE_DOC MODE RUNNING >>\n");
			here_doc_mode(line);
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
