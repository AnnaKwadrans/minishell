#include "lexer.h"
#include "data.h"
#include "aux.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

size_t	array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

char	**join_arrays(char **array, char **add)
{
	int	i;
	int	j;
	char	**joined;

	joined = malloc(sizeof(char **) * (array_size(array) + array_size(add) + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (array[i])
	{
		joined[i] = ft_strdup(array[i]);
		i++;
	}
	j = 0;
	while (add[j])
	{
		joined[i] = ft_strdup(add[j]);
		i++;
		j++;
	}
	joined[i] = NULL;
	return (joined);
}
