/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:36 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/21 00:39:41 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
	{
		joined = ft_strdup(s1);
		free(s1);
		return (joined);
	}
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	free_vars(void *args)
{
	t_vars	*var;
	t_vars	*next;
	t_data	*data_program;

	data_program = (t_data *)args;
	var = data_program->vars;
	while (var)
	{
		next = var->next;
		free(var->name);
		free(var->value);
		free(var);
		var = next;
	}
}

int	skip_var(const char *line, int i)
{
	i++;
	while (line[i] && (line[i] == '_' || ft_isalnum(line[i])))
		i++;
	return (i);
}

int	skip_quote(const char *line, int i)
{
	char	quote;

	quote = line[i++];
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}
