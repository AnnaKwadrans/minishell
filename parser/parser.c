#include "../parser.h"
#include "../data.h"
#include "../libft/libft.h"

t_cmd	**parse_line(char *input, int pipes, char **envp, t_data *data)
{
	int	i;
	char	**cmd_aux;
	t_cmd	**cmds;

	printf("%s\n", input);
	if (!input || input[0] == '\0' || !valid_pipes(input))
		return (ft_putendl_fd("Parse error", 2), NULL);
	//if (is_var(input))
	//	return (handle_var(input, data), NULL);		DESCOMENTAR
	cmd_aux = split_pipes(input, '|');
	print_array(cmd_aux); // para testear
	cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	if (!cmds)
		return (perror("malloc failed"), NULL);
	i = 0;
	while (i <= pipes)
	{
		cmds[i] = get_cmd(cmd_aux[i]);
		cmds[i]->env = envp;
		cmds[i]->data = data;
		i++;
	}
	cmds[i] = NULL;
	free_array(cmd_aux);
	return (cmds);
}

t_cmd        *get_cmd(char *aux)
{
        t_cmd        *cmd;
        int        i;

        cmd = init_cmd();
        if (!cmd)
                return (NULL);
        i = 0;
        while (aux[i])
        {
                if (ft_isspace(aux[i]))
			i++;
		else if (aux[i] == '<')
			cmd->infile = get_infile(&aux[i], &cmd->delimit, &i);
		else if (aux[i] == '>')
                        cmd->outfile = get_outfile(&aux[i], &cmd->append, &i);
		else if (!cmd->args)
                        cmd->args = get_args(&aux[i], &i);
		else
                        cmd->args = append_args(cmd->args, &aux[i], &i);
	}
	if (cmd->args == NULL)
	{
		cmd->args = malloc(sizeof(char *));
		if (!cmd->args)
			return (free_cmd(cmd), NULL);
		cmd->args[0] = ft_strdup("cat");
	}
	//printf("%s %s %s %d\n", cmd->infile, cmd->delimit, cmd->outfile, cmd->append); // para testear
	//print_array(cmd->args);
	//printf("END PIPE\n");
        return (cmd);
}
//VAR=abc ; ' cat -e | pipe' def | ghi >>fichero  | sort -R >> file| grep \"hola\"   >>outfile
t_cmd        *init_cmd()
{
        t_cmd        *cmd;
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
                return (NULL);
        cmd->args = NULL;
        cmd->env = NULL;
        cmd->infile = NULL;
        cmd->fd_in = STDIN_FILENO;
        cmd->outfile = NULL;
        cmd->fd_out = STDOUT_FILENO;
        cmd->append = 0;
        cmd->delimit = NULL;
	cmd->heredoc = NULL;
        cmd->data = NULL;
	return (cmd);
}
/*
char	*get_infile(char *aux, char **delimit, int *index)
{
	int	i;
	int	start;
	int	len;
	int	heredoc;

	i = 1;
	if (aux[i] == '<')
	{
		heredoc = 1;
		i++;
	}
	else
		heredoc = 0;
	while (ft_isspace(aux[i]))
		i++;
	start = i;
	while (!ft_isspace(aux[i]))
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	len = i - start;
	*index += i;
	if (heredoc)
	{
		*delimit = ft_substr(aux, start, len);
		return (NULL);
	}
	return (ft_substr(aux, start, len));
}
*/
char	*get_infile(char *aux, char **delimit, int *index)
{
	int	i;
	char	*infile;

	i = 1;
	if (aux[i] == '<')
	{
		i++;
		*delimit = get_file_str(&aux[i], &i);
		*index += i;
		return (NULL);
	}
	else
	{
		infile = get_file_str(&aux[i], &i);
		*index += i;
		return (infile);
	}
}

char	*get_outfile(char *aux, int *append, int *index)
{
	int	i;
	char	*outfile;

	i = 1;
	if (aux[i] == '>')
	{
		*append = 1;
		i++;
	}
	outfile = get_file_str(&aux[i], &i);
	*index += i;
	return (outfile);
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
	while (aux[i] && !ft_isspace(aux[i]))
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
	int	len;
	char	*cmd_line;
	char	**args;

	len = 0;
	while (aux[len] && aux[len] != '<' && aux[len] != '>')
		len++;
	cmd_line = ft_substr(aux, 0, len);
	args = split_pipes(cmd_line, ' ');
	//printf("desp del split:\n");
	//print_array(args);
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
