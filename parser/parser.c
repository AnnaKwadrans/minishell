/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:49:35 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/18 01:30:34 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../here_doc/here_doc.h"
#include "../vars/varenv.h"

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

t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data)
{
	int		i;
	char	**cmd_aux;
	t_cmd	**cmds;
	char	*input_exp;
	int		will_free;

	// printf("<<<-------------- PARSING LINE -------------->>>\n");
	// printf("PARSING INPUT: %s\n", input);
	if (!input || input[0] == '\0' || !valid_pipes(input))
		return (NULL);
	// printf("Input: %s\n", input);
	if (is_expandable(input))
	{
		// printf("Input expandable: %s\n", input);
		input_exp = expand_vars(data, input);
		will_free = 1;
		// printf("EXPANDED: %s\n", input_exp);
	}
	else
	{
		input_exp = input;
		will_free = 0;
	}
	// printf("\t>>>\t\texpand: %s\n", input_exp);
	cmd_aux = split_pipes(input_exp, '|');
	cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	if (!cmds)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (i <= pipes)
	{
		cmds[i] = malloc(sizeof(t_cmd));
		if (!cmds[i])
			return (perror("malloc failed"), free_array(cmd_aux), NULL);
		if (is_here_doc(cmd_aux[i]))
		{
			init_cmd(cmds[i]);
			cmds[i]->heredoc = here_doc_mode(data, cmd_aux[i]);
			if (!cmds[i]->heredoc)
			{
				free_cmd(cmds[i]);
				free_array(cmd_aux);
				cmds[i] = NULL;
				// printf("Error in heredoc\n");
				return (NULL);
			}
			// printf("heredoc got it\n");
			get_heredoc_cmd(cmd_aux[i], cmds[i]);
		}
		else
		{
			free(cmds[i]);
			cmds[i] = get_cmd(cmd_aux[i]);
			if (!cmds[i])
			{
				free_array(cmd_aux);
				return (NULL);
			}
			//trim_quotes(cmds[i]->args);
		}
		//cmds[i]->env = envp;
		cmds[i]->data = data;
		// printf("CMD ARRAY\n");
		// if (cmds[i]->args)
		// 	print_array(cmds[i]->args);
		// printf("END\n");
		i++;
	}
	cmds[i] = NULL;
	free_array(cmd_aux);
	if (will_free)
		free(input_exp);
	return (cmds);
}
/*
void	trim_quotes(char **args)
{
	int	i;
	char	*trimmed;
	char	*aux;

	i = 0;
	while (args[i])
	{
		
	}
	aux = ft_strtrim(input, " \t\n\v\r\f");
	trimmed = ft_strtrim(aux, "\"\'");
	free(input);
	free(aux);
	return (trimmed);
}
*/

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' || str[i] != '\"' || !ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

t_cmd	*get_cmd(char *aux)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (perror("malloc failed"), NULL);
	init_cmd(cmd);
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
	if (cmd->args)
		cmd->args = rm_quotes(cmd->args);
	else
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (free_cmd(cmd), NULL);
		cmd->args[0] = ft_strdup("cat");
		cmd->args[1] = NULL;
	}
	// printf("ARGS\n");
	// print_array(cmd->args);
	return (cmd);
}

//VAR=abc ; ' cat -e | pipe' def | ghi >>fichero  | sort -R >> file| grep \"hola\"   >>outfile
void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	//cmd->env = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	//cmd->append = 0;
	//cmd->delimit = NULL;
	cmd->heredoc = NULL;
	cmd->data = NULL;
	cmd->p_status = 0;
	cmd->pid = 0;
}


void	skip_delimit(char *aux, int *index)
{
	int	i;

	i = 0;
	while (ft_isspace(aux[i]))
		i++;
	while (aux[i] && !ft_isspace(aux[i]))
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	*index += i;
	return ;
}

void	get_infile(char *aux, int *index, char ***infile) 
{
	char	*new_inf;
	int	i;

	i = 1;
	if (aux[i] == '<')
	{
		i++;
		skip_delimit(&aux[i], &i);
		*index += i;
	}
	else
	{
		new_inf = get_file_str(&aux[i], &i);
		*index += i;
	}
	if (*infile)
		*infile = append_file(*infile, new_inf);
	else
		*infile = first_file(new_inf);
}

char	**first_file(char *new_file)
{
	char	**file;

	file = (char **)malloc(sizeof(char *) * 2);
	if (!file)
		return (NULL);
	file[0] = new_file;
	file[1] = NULL;
	//printf("FISRT FILE\n");
	//printf("%s\n", new_inf);
	//print_array(infile);
	return (file);
}

char	**append_file(char **file, char *new_file)
{
	char	**res;
	char	**new_file_array;
	int	size;

	new_file_array = first_file(new_file);
	res = join_arrays(file, new_file_array);
	return (res);
}


void	get_outfile(char *aux, int *index, char ***outfile, int *append) 
{
	char	*new_outf;
	int	i;

	i = 1;
	if (aux[i] == '>')
	{
		*append = 1;
		i++;
	}
	else
	{
		new_outf = get_file_str(&aux[i], &i);
		*index += i;
	}
	if (*outfile)
		*outfile = append_file(*outfile, new_outf);
	else
		*outfile = first_file(new_outf);
}

char	*get_file_str(const char *aux, int *index)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (ft_isspace(aux[i]))
		i++;
	start = i;
	while (aux[i] && !ft_isspace(aux[i]) && aux[i] != '>' && aux[i] != '<')
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	len = i - start;
	*index += i;
	//printf("index get_file_str: %d\n", *index);
	return (ft_substr(aux, start, len));
}

char	**get_args(char *aux, int *index)
{
	int		len;
	char	*cmd_line;
	char	**args;

	len = 0;
	while (aux[len] && aux[len] != '<' && aux[len] != '>')
		len++;
	cmd_line = ft_substr(aux, 0, len);
	args = split_pipes(cmd_line, ' ');
	// printf("desp del split:\n");
	// print_array(args);
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

char	**rm_quotes(char **args)
{
	char	**res;
	int	i;

	res = (char **)malloc(sizeof(char *) * (array_size(args) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (args[i])
	{
		res[i] = rm_quotes_arg(args[i]);
		i++;
	}
	res[i] = NULL;
	free_array(args);
	return(res);
}

char	*rm_quotes_arg(char *arg)
{
	char	*res;
	int	i;
	int	j;

	res = (char *)malloc(sizeof(char) * (count_no_quotes(arg) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
		{
			res[j] = arg[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	count_no_quotes(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
			count++;
		i++;
	}
	return (count);
}
