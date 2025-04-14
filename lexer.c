#include "lexer.h"
#include "data.h"
#include "libft/libft.h"

t_cmd	**parse_line(char *input, int pipes)
{
	int	i;
	char	**cmd_aux;
	t_cmd	**cmds;
	//t_cmd	*head;

	cmd_aux = split_pipes(input, '|');
	print_array(cmd_aux); // para testear
	cmds = malloc(sizeof(t_cmd *) * (pipes + 2));
	i = 0;
	while (i <= pipes)
	{
		cmds[i] = get_cmd(cmd_aux[i]);
		//cmds[i]->infile = get_infile(input, cmds[i]->delimit);
		//cmds[i]->outfile = get_outfile(input, cmds[i]->append);
		//if (i == 0)
		//	head = cmds[i];
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
                        cmd->infile = get_infile(&aux[i], cmd->delimit, &i);
                else if (aux[i] == '>')
                        cmd->outfile = get_outfile(&aux[i], &cmd->append, &i);
                else if (!cmd->args)
                        cmd->args = get_args(&aux[i], &i);
                else
                        cmd->args = append_args(cmd->args, &aux[i], &i);
                //i++;
		printf("%s %s %s %d\n", cmd->infile, cmd->delimit, cmd->outfile, cmd->append);
		print_array(cmd->args);
        }
        return (cmd);
}

t_cmd        *init_cmd()
{
        t_cmd        *cmd;
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
                return (NULL);
        cmd->args = NULL;
        //cmd->env = envp;
        cmd->infile = NULL;
        cmd->fd_in = STDIN_FILENO;
        cmd->outfile = NULL;
        cmd->fd_out = STDOUT_FILENO;
        cmd->append = 0;
        cmd->delimit = NULL;
        //pid_t         pid;
        //int                p_status;
        //struct s_cmd *next;
        //t_data        *data;
	return (cmd);
}

char	*get_infile(char *aux, char *delimit, int *index)
{
	int	i;
	char	*infile;
	int	start;
	int	len;
	int	heredoc;

	i = 0;
	if (aux[i + 1] == '<')
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
	len = i - start + 1;
	*index += i;
	if (heredoc)
	{
		delimit = ft_substr(aux, start, len);
		return (NULL);
	}
	return (ft_substr(aux, start, len));
}

char	*get_outfile(char *aux, int *append, int *index)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	if (aux[i + 1] == '>')
	{
		*append = 1;
		i++;
	}
	while (ft_isspace(aux[i]))
		i++;
	start = i;
	while (!ft_isspace(aux[i]))
	{
		if (aux[i] == '\'' || aux[i] == '\"')
			i += close_quotes(&aux[i]);
		i++;
	}
	len = i - start + 1;
	*index += i;
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
	args = ft_split(cmd_line, ' ');
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
