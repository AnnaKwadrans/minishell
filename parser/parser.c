/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:49:35 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/12 13:34:08 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data)
{
	int		i;
	char	**cmd_aux;
	//t_cmd	**cmds;
	char	*input_exp;
	//int		will_free;

	printf("<<<-------------- PARSING LINE -------------->>>\n");

	//input_exp = vars_expansion(input, data, &will_free);
	//printf("%d, %s\n", is_expandable(input), input_exp);
	//cmd_aux = split_pipes(input_exp, '|');
	cmd_aux = split_pipes(input, '|');
	//print_array(cmd_aux);
	data->cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	if (!data->cmds)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (i <= pipes)
	{
		pipeline(data, cmd_aux, i);
		if (!data->cmds[i])
			return (free_array(cmd_aux), NULL); // ver liberacion de memoria
		i++;
	}
	data->cmds[i] = NULL;
	free_array(cmd_aux);
	//if (will_free)
	//	free(input_exp);
	//print_cmd(data->cmds);
	return (data->cmds);
}
/*
char	*vars_expansion(char *input, t_data *data, int *will_free)
{
	char	*input_exp;
	
	if (is_expandable(input))
	{
		//printf("Input expandable: %s\n", input);
		input_exp = expand_vars(data, input, 0);
		*will_free = 1;
		//printf("EXPANDED: %s\n", input_exp);
	}
	else
	{
		input_exp = input;
		*will_free = 0;
	}
	return (input_exp);
}
*/
int is_expandable(char *input)
{
	int	simple_quotes;
	int	double_quotes;
	int	i;
	int	size;

	simple_quotes = 0;
	double_quotes = 0;
	i = 0;
	size = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '\'' && input[i + 1] == '\'')
			simple_quotes++;
		else if (input[i] == '\"')
			double_quotes++;
		i++;
	}
	// printf("Simple quotes: %d, Double quotes: %d\n", simple_quotes, double_quotes);
	if ((simple_quotes % 2 == 0 && simple_quotes != 0) || double_quotes % 2 == 0)
		return (1);
	else
		return (0);
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
	vars_expansion(data, data->cmds[i]);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	//cmd->env = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	//cmd->delimit = NULL;
	cmd->heredoc = NULL;
	cmd->data = NULL;
	cmd->p_status = 0;
	cmd->pid = 0;
	cmd->is_builtin = 0;
}

void	*vars_expansion(t_data *data, t_cmd *cmd)
{
	int	i;
	//char	*input_exp;
	
	i = 0;
	while (cmd->args[i])
	{
		if (is_expandable(cmd->args[i]))
		{
			cmd->args[i] = expand_vars(data, cmd->args[i], 0, 1);
		}
		i++;
	}
	/*
	if (is_expandable(input))
	{
		//printf("Input expandable: %s\n", input);
		input_exp = expand_vars(data, input, 0);
		*will_free = 1;
		//printf("EXPANDED: %s\n", input_exp);
	}
	else
	{
		input_exp = input;
		*will_free = 0;
	}
	return (input_exp);
	*/
}
