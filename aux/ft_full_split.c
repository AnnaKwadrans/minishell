/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:33:26 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 12:53:14 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	count_parts(char *s, char c)
{
	int	count;

	count = 1;
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
	char	*sub;
	size_t	i;

	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
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
	int		i;
	char	*start;
	char	**result;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_parts(s, c);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = s;
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
