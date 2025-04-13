
#include "lexer.h"
#include "data.h"
#include "libft/libft.h"

int	count_pipe(char *line)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += close_quotes(&line[i]);
		if (line[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

bool	even_quotes(char *line)
{
	int	single_com;
	int	double_com;
	int	i;

	single_com = 0;
	double_com = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			single_com++;
		else if (line[i] == '\"')
			double_com++;
		i++;
	}
	if ((single_com % 2 != 0) || (double_com % 2 != 0))
	{
		// err invalid syntax
		return (0);
	}
	return (1);
}

char	*get_var(char *line)
{
	char	*name;
	char	*var;

	name = ft_strdup_set(line, " \t\n\v\r\f");
	printf("%s\n", name);
	var = getenv(name);
	free(name);
	return(var);
}

void	init_data(t_data *data)
{
	data->line = NULL;
	data->cmds = NULL;
	data->history_lines = NULL;
	data->pipes = 0;
}

void	parse_data(char *input, t_data *data)
{
	t_lines	*history_last;

	if (!even_quotes(input))
	{}
		// err invalid syntax
	data->line = malloc(sizeof(t_lines));
	data->line->line = ft_strdup(input);
	data->line->next = NULL;
	history_last = last_line(data->history_lines);
	if (!history_last)
		data->line->index = 0;
	else
		data->line->index = history_last->index + 1;
	//data->cmds = malloc(sizeof(t_cmd));
	if (data->history_lines)
		history_last->next = data->line;
	else
		data->history_lines = data->line;
	data->pipes = count_pipe(input);
	data->cmds = parse_line(input, data->pipes);
	if (!data->line || !data->cmds || !data->cmds)
		free_data(data);
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmds)
		free(data->cmds);
	if (data->cmds)
	{}
		// free cmds struct
}

t_lines	*last_line(t_lines *history_lines)
{
	t_lines	*last;

	if (!history_lines)
		return (NULL);
	last = history_lines;
	while (last->next)
		last = last->next;
	return (last);
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

t_cmd	**parse_line(char *input, int pipes)
{
	int	i;
	char	**cmd_aux;
	t_cmd	**cmds;
	t_cmd	*head;

	cmd_aux = split_pipes(input, '|');
	print_array(cmd_aux);
	
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
                        cmd->infile = get_inflile(&aux[i], cmd->delimit, &i);
                else if (aux[i] == '>')
                        cmd->outfile = get_outfile(&aux[i], &cmd->append, &i);
                else if (!cmd->args)
                        cmd->args = get_args(&aux[i], &i);
                else
                        cmd->args = append_args(cmd->args, &aux[i], &i);
                //i++;
        }
        return (cmd);
}

char	*get_inflile(char *aux, char *delimit, int *index)
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

