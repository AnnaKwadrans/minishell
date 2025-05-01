#include "parser.h"
#include "data.h"
#include "libft/libft.h"

void	init_data(t_data *data)
{
	data->line = NULL;
	data->cmds = NULL;
	data->history_lines = NULL;
	data->pipes = 0;
}

void	parse_data(char *input, t_data *data)
{
	//t_lines	*history_last;

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
	data->pipes = count_pipe(input);
	data->tokens = split_pipes(input, ';');
	/*
	data->cmds = parse_line(input, data->pipes);
	if (!data->line || !data->cmds || !data->cmds)
		free_data(data);
	*/
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
