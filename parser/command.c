/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:27:05 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 16:27:35 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*get_cmd(char *aux)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (perror("malloc failed"), NULL);
	init_cmd(cmd);
	fill_out_cmd(cmd, aux);
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (free_cmd(cmd), NULL);
		cmd->args[0] = ft_strdup("cat");
		cmd->args[1] = NULL;
	}
	if (is_builtin(cmd->args[0]))
		cmd->is_builtin = 1;
	return (cmd);
}

t_cmd	*fill_out_cmd(t_cmd *cmd, char *aux)
{
	int	i;

	i = 0;
	while (aux[i])
	{
		if (ft_isspace(aux[i]))
			i++;
		else if (aux[i] == '<')
			get_infile(&aux[i], &i, &cmd->infile);
		else if (aux[i] == '>')
			get_outfile(&aux[i], &i, &cmd->outfile, &cmd->append);
		else if (!cmd->args)
			cmd->args = get_args(&aux[i], &i);
		else
			cmd->args = append_args(cmd->args, &aux[i], &i);
	}
	return (cmd);
}

char	**get_args(char *aux, int *index)
{
	int		len;
	char	*cmd_line;
	char	**args;

	len = 0;
	while (aux[len] && aux[len] != '<' && aux[len] != '>')
	{
		if (aux[len] == '\'' || aux[len == '\"'])
			len += close_quotes(&aux[len]);
		len++;
	}
	cmd_line = ft_substr(aux, 0, len);
	args = split_pipes(cmd_line, ' ');
	free(cmd_line);
	*index += len;
	return (args);
}

char	**append_args(char **args, char *aux, int *i)
{
	char	**add;
	char	**joined;

	add = get_args(aux, i);
	joined = join_arrays(args, add);
	free_array(add);
	free_array(args);
	return (joined);
}
