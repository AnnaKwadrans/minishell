/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:43:11 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 14:54:37 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_cmd_for_spaces(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*cmd_arg;

	cmd_arg = ft_strdup(cmd->args[0]);
	i = 0;
	while (cmd_arg[i])
	{
		if (isspace(cmd_arg[i]))
		{
			split_cmd(data, cmd, cmd_arg);
			break ;
		}
		i++;
	}
	free(cmd_arg);
	return ;
}

void	split_cmd(t_data *data, t_cmd *cmd, char *cmd_arg)
{
	char	**split_args;
	char	**command;
	char	**aux;

	command = ft_split(cmd_arg, ' ');
	aux = rm_first_arg(cmd->args);
	if (!aux)
	{
		free_array(command);
		return ;
	}
	split_args = join_arrays(command, aux);
	free_array(aux);
	free_array(command);
	if (!split_args)
		return ;
	free_array(cmd->args);
	cmd->args = split_args;
}

char	**rm_first_arg(char **args)
{
	char	**new_args;
	int		i;
	int		j;

	new_args = (char **)malloc(sizeof(char *) * array_size(args));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 1;
	while (args && args[j])
	{
		new_args[i] = ft_strdup(args[j]);
		if (!new_args[i])
		{
			free_array(new_args);
			return (NULL);
		}
		i++;
		j++;
	}
	new_args[i] = NULL;
	return (new_args);
}
