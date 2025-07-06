#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../here_doc/here_doc.h"
#include "../vars/varenv.h"
#include "../executor/executor.h"

t_cmd	*get_cmd(char *aux)
{
	t_cmd	*cmd;
	//int		i;

        //printf("%s\n", aux);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (perror("malloc failed"), NULL);
	init_cmd(cmd);
	//i = 0;
	//printf("get_cmd - aux: %s\n", aux);
	fill_out_cmd(cmd, aux);
	/*
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
			*/
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
			len +=close_quotes(&aux[len]);
		len++;
	}
	cmd_line = ft_substr(aux, 0, len);
	//printf("cmd_line: %s\n", cmd_line);
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
