#include "lexer.h"
#include "data.h"

/*
int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
*/
bool	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

size_t	ft_strlen_set(const char *s, char *set)
{
	size_t	len;

	len = 0;
	while (s[len] && !is_set(s[len], set))
		len++;
	return (len);
}

char	*ft_strdup_set(const char *s, char *set)
{
	int		len;
	char	*ptr;

	len = ft_strlen_set(s, set) + 1;
	ptr = malloc(sizeof(char) * len);
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s, sizeof(char) * len);
	return (ptr);
}

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
