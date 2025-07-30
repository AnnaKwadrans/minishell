/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:37:15 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 18:37:47 by kegonza          ###   ########.fr       */
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
