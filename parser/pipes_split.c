/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:53:57 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/06 21:47:19 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	close_quotes(char const *s)
{
	int	i;

	i = 0;
	//printf("\tCLOSE QUOTES\n");
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '\"')
	{
		i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	return (i);
}

static int	split_strlen(char c, char const *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		if (s[len] == '\'' || s[len] == '\"')
			len += close_quotes(&s[len]);
		len++;
	}
	return (len);
}

static int	split_count(char const *s, char c)
{
	int	count;
	int	new_string;
	int	i;

	//printf("\t SPLITTING COUNT\n");
	new_string = 0;
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += close_quotes(&s[i]);
		if (s[i] == c)
			new_string = 0;
		else if (s[i] != c && new_string == 0)
		{
			new_string = 1;
			count++;
		}
		i++;
	}
	//printf("\tCount: %d\n", count);
	return (count);
}

static char	**init_array(char const *s, int count, char c)
{
	char	**array;
	int		i;
	int		j;

	array = (char **)ft_calloc(count + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		array[i] = (char *)ft_calloc(split_strlen(c, &s[j]) + 1, sizeof(char));
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		while (s[j] != '\0' && s[j] != c)
		{
			if (s[j] == '\'' || s[j] == '\"')
				j += close_quotes(&s[j]);
			j++;
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**split_pipes(char const *s, char c)
{
	int		count;
	char	**array;
	int		i;
	int		j;

	//printf("<<<-------------- SPLITTING PIPES -------------->>>\n");
	count = split_count(s, c);
	array = init_array(s, count, c);
	if (array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i] != NULL)
	{
		while (s[j] != '\0' && s[j] == c)
			j++;
		ft_strlcpy(array[i], &s[j], split_strlen(c, &s[j]) + 1);
		while (s[j] != '\0' && s[j] != c)
		{
			if (s[j] == '\'' || s[j] == '\"')
				j += close_quotes(&s[j]);
			j++;
		}
		i++;
	}
	//print_array(array);
	return (array);
}