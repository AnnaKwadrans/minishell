/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:53:45 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/23 22:43:13 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../data.h"

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

char	*get_var(char *line)
{
	char	*name;
	char	*var;

	name = ft_strdup_set(line, " \t\n\v\r\f");
	//printf("%s\n", name);
	var = getenv(name);
	free(name);
	return (var);
}

t_lines	*last_line(t_lines *history_lines)
{
	t_lines	*last;

	if (!history_lines)
		return (NULL);
	last = history_lines;
	while (last->next)
		last = last->next;
	return (last);
}
