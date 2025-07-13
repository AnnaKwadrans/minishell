/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:43:11 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 15:53:46 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	rm_quotes(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (has_quotes_to_rm(cmd->args[i]))
			cmd->args[i] = rm_quotes_arg(cmd->args[i]);
		i++;
	}
	i = 0;
	while (cmd->infile && cmd->infile[i])
	{
		if (has_quotes_to_rm(cmd->infile[i]))
			cmd->infile[i] = rm_quotes_arg(cmd->infile[i]);
		i++;
	}
	i = 0;
	while (cmd->outfile && cmd->outfile[i])
	{
		if (has_quotes_to_rm(cmd->outfile[i]))
			cmd->outfile[i] = rm_quotes_arg(cmd->outfile[i]);
		i++;
	}
}

bool	has_quotes_to_rm(char *str)
{
	if (!str)
		return (0);
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
		return (1);
	else
		return (0);
}

char	*rm_quotes_arg(char *arg)
{
	char	*res;
	int		i;
	int		j;
	bool	q_simple;
	bool	q_double;

	res = (char *)malloc(sizeof(char) * (count_no_quotes(arg) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (cpy_char(arg[i], &q_simple, &q_double))
		{
			res[j] = arg[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(arg);
	return (res);
}

bool	cpy_char(char arg, bool *q_simple, bool *q_double)
{
	if (arg == '\'' && *q_simple == 0 && *q_double == 0)
	{
		*q_simple = 1;
		return (0);
	}
	else if (arg == '\'' && *q_simple == 1)
	{
		*q_simple = 0;
		return (0);
	}
	else if (arg == '\"' && *q_double == 0 && *q_simple == 0)
	{
		*q_double = 1;
		return (0);
	}
	else if (arg == '\"' && *q_double == 1)
	{
		*q_double = 0;
		return (0);
	}
	else
		return (1);
}

int	count_no_quotes(char *arg)
{
	int		i;
	int		count;
	bool	q_simple;
	bool	q_double;

	i = 0;
	count = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (cpy_char(arg[i], &q_simple, &q_double))
			count++;
		i++;
	}
	return (count);
}
