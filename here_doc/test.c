#include <stdlib.h>
#include <stdio.h>

size_t ft_strlen(const char *s);

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

int main(void)
{
	char *line;

	line = "hello world ";
	char *new_line = without_last_spaces(line);
	printf("Original line: '%s'\n", line);
	printf("New line: '%s'\n", new_line);
}
