/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:37:15 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 18:55:54 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

int	skip_meta(const char *line, int i)
{
	if (line[i] == '\'' || line[i] == '\"')
		return (skip_quote(line, i));
	else if (line[i] == '\\')
		return (i + 2);
	return (i + 1);
}

void	handle_pid(char **temp, int *j, int *i)
{
	temp[(*j)++] = ft_itoa(getpid());
	(*i) += 2;
}

char	*append_char(char *result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(result, tmp));
}

char	*handle_dollar(char *result, char *line, int *i, t_expand *exp)
{
	if (line[*i + 1] == '$')
	{
		*i += 2;
		return (ft_strjoin_free(result, exp->values[exp->count++]));
	}
	else
	{
		(*i)++;
		result = ft_strjoin_free(result, exp->values[exp->count++]);
		*i = skip_var(line, *i - 1);
		return (result);
	}
}
