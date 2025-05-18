#include "../parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include <readline/readline.h>

void rl_replace_line(const char *text, int clear_undo);

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0); // Limpiar la línea actual
	rl_on_new_line(); // Mover el cursor a la nueva línea
	rl_redisplay(); // Redibujar la línea
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); // Ignorar Ctrl+\;
}

void	init_data(t_data *data)
{
	data->line = NULL;
	data->cmds = NULL;
	data->history_lines = NULL;
	data->part_lines = NULL;
	data->vars = NULL;
	data->pipes = 0;
	data->is_interactive = isatty(STDIN_FILENO);
	if (data->is_interactive)
    	setup_interactive_signals();
	else
	{
		signal(SIGINT, SIG_IGN); // Ignorar Ctrl+C
		signal(SIGQUIT, SIG_IGN); // Ignorar Ctrl+\;
	}
	data->fds = NULL;
}

void	parse_data(char *input, t_data *data, char **envp)
{
	//t_lines	*history_last;
	char	**part_lines;
	int		i;

	if (ft_strncmp(input, "mhistory", 8) == 0)
	{
		show_history(data);
		return ;
	}
	printf("input: %s\n", input);
	if (!even_quotes(input))
	{}
		// err invalid syntax
	data->line = malloc(sizeof(t_lines));
	data->line->line = ft_strdup(input);
	printf("line: %s\n", data->line->line);
	data->line->next = NULL;
	/*
	ESTO ESTA MAL
	history_last = last_line(data->history_lines);
	if (!history_last)
		data->line->index = 0;
	else
		data->line->index = history_last->index + 1;
	if (data->history_lines)
		history_last->next = data->line;
	else
		data->history_lines = data->line;
	history_last = last_line(data->history_lines);
	printf("last history line: %s\n", data->history_lines->line);
	*/
	part_lines = split_pipes(input, ';');
	print_array(part_lines);
	data->pipes = get_pipes(part_lines, array_size(part_lines));
	data->cmds = malloc(sizeof(t_cmd **) * array_size(part_lines));
	if (!data->cmds)
	{
		free(data);
		return ;
	}
	i = 0;
	while (part_lines[i])
	{
		data->cmds[i] = parse_line(part_lines[i], data->pipes[i], envp, data);
		if (!data->line || !data->cmds || !data->cmds)
		{
			free_data(data);
			return ;
		}
		i++;
	}
	data->cmds[i] = NULL;
}

int	*get_pipes(char **part_lines, size_t size)
{
	int	*pipes;
	int	i;

	pipes = (int *)malloc(sizeof(int) * (size + 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (part_lines[i])
	{
		pipes[i] = count_pipe(part_lines[i]);
		i++;
	}
	pipes[size] = -1;
	return (pipes);
}

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
