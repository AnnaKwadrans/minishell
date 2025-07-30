/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:49:35 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 12:03:47 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data)
{
	int		i;
	char	**cmd_aux;
	char	*input_exp;

	cmd_aux = split_pipes(input, '|');
	data->cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	if (!data->cmds)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (i <= pipes)
	{
		pipeline(data, cmd_aux, i);
		if (!data->cmds[i])
		{
			printf("check cmds[i] NULL %d\n", data->last_status);
			free_array(cmd_aux);
			clean_data_program(data);
			return (NULL);
		}
		i++;
	}
	data->cmds[i] = NULL;
	free_array(cmd_aux);
	return (data->cmds);
}

void	pipeline(t_data *data, char **cmd_aux, int i)
{
	if (is_here_doc(cmd_aux[i]))
	{
		data->cmds[i] = malloc(sizeof(t_cmd));
		if (!(data->cmds[i]))
			return (perror("malloc failed"));
		init_cmd(data->cmds[i]);
		(data->cmds[i])->heredoc = here_doc_mode(data, cmd_aux[i]);
		if (!(data->cmds[i])->heredoc)
		{
			printf("check heredoc NULL %d\n", data->last_status);
			free_cmd(data->cmds[i]);
			data->cmds[i] = NULL;
			return ;
		}
		get_heredoc_cmd(cmd_aux[i], data->cmds[i]);
	}
	else
	{
		data->cmds[i] = get_cmd(cmd_aux[i]);
		if (!(data->cmds[i]))
			return ;
	}
	data->cmds[i]->data = data;
	data->cmds[i + 1] = NULL;
	vars_expansion(data, data->cmds[i]);
	rm_quotes(data, data->cmds[i]);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->data = NULL;
	cmd->p_status = 0;
	cmd->pid = 0;
	cmd->is_builtin = 0;
}

void	vars_expansion(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (is_expandable(cmd->args[i]))
		{
			cmd->args[i] = expand_vars(data, cmd->args[i], 0, 1);
		}
		i++;
	}
}

int	is_expandable(char *input)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		else if (input[i] == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (input[i] == '\'' && s_quote && !d_quote)
			s_quote = 0;
		else if (input[i] == '\"' && d_quote && !s_quote)
			d_quote = 0;
		else if (input[i] == '$' && !s_quote)
			return (1);
		i++;
	}
	return (0);
}
