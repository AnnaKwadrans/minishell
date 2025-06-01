/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:33:26 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/01 16:57:38 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	count_parts(char *s, char c)
{
	int	count = 1;

	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

static char	*fill_str(char *start, size_t len)
{
	char	*sub = malloc(len + 1);
	size_t	i = 0;

	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = start[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**ft_full_split(char *s, char c)
{
	int		i = 0;
	char	*start = s;
	char		**result;
	size_t		count;

	if (!s)
		return (NULL);
	count = count_parts(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s == c)
		{
			result[i++] = fill_str(start, s - start);
			start = s + 1;
		}
		s++;
	}
	result[i++] = fill_str(start, s - start);
	result[i] = NULL;
	return (result);
}
// int main(void)
// {
// 	char line[28] = "hello world, this is a test";
// 	char **buffer = ft_full_split(line, ' ');
// 	if (buffer == NULL)
// 	{
// 		printf("Error: Memory allocation failed\n");
// 		return (1);
// 	}
// 	int i = 0;
// 	while (buffer[i] != NULL)
// 	{
// 		printf("buffer[%d]: %s\n", i, buffer[i]);
// 		i++;
// 	}
// }

