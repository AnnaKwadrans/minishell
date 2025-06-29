/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:49:35 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/29 13:49:33 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../here_doc/here_doc.h"
#include "../vars/varenv.h"

t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data)
{
	int		i;
	char	**cmd_aux;
	t_cmd	**cmds;
	char	*input_exp;
	int		will_free;

	// printf("<<<-------------- PARSING LINE -------------->>>\n");
	// printf("PARSING INPUT: %s\n", input);
	
	//if (!input || input[0] == '\0' || !valid_pipes(input))
	//	return (NULL);
	// printf("Input: %s\n", input);
	
	input_exp = vars_expansion(input, data, &will_free);
	/*
	if (is_expandable(input))
	{
		printf("Input expandable: %s\n", input);
		input_exp = expand_vars(data, input, 0);
		will_free = 1;
		printf("EXPANDED: %s\n", input_exp);
	}
	else
	{
		input_exp = input;
		will_free = 0;
	}*/
	//printf("\t>>>\t\texpand: %s\n", input_exp);
	cmd_aux = split_pipes(input_exp, '|');
	//print_array(cmd_aux);
	cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	if (!cmds)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (i <= pipes)
	{
		pipeline(data, &cmds[i], cmd_aux[i]);
		if (!cmds[i])
			return (free_array(cmd_aux), NULL); // ver liberacion de memoria
		i++;
	}
	cmds[i] = NULL;
	free_array(cmd_aux);
	if (will_free)
		free(input_exp);
	//print_cmd(cmds);
	return (cmds);
}

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

void	pipeline(t_data *data, t_cmd **cmd, char *cmd_aux)
{
	if (is_here_doc(cmd_aux))
	{
		*cmd = malloc(sizeof(t_cmd));
		if (!(*cmd))
			return (perror("malloc failed"));
		init_cmd(*cmd);
		(*cmd)->heredoc = here_doc_mode(data, cmd_aux);
		if (!(*cmd)->heredoc)
		{
			free_cmd(*cmd);
			//free_array(cmd_aux);
			*cmd = NULL;
			// printf("Error in heredoc\n");
			return ;
		}
		// printf("heredoc got it\n");
		get_heredoc_cmd(cmd_aux, *cmd);
	}
	else
	{
		//free(cmd); // por que?
		*cmd = get_cmd(cmd_aux);
		if (!(*cmd))
			return ;
	}
	//cmds[i]->env = envp;
	(*cmd)->data = data;
	// printf("CMD ARRAY\n");
	// if (cmds[i]->args)
	// 	print_array(cmds[i]->args);
	// printf("END %d\n", i);
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
