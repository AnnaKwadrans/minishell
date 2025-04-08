
#include "lexer.h"
#include "data.h"
#include "libft/libft.h"


int	count_pipes(char *line)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

bool	count_comas(char *line)
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

	data->line = malloc(sizeof(t_lines));
	data->line->line = ft_strdup(input);
	data->line->next = NULL;
	history_last = last_line(data->history_lines);
	if (!history_last)
		data->line->index = 0;
	else
		data->line->index = history_last->index + 1;
	data->cmds = malloc(sizeof(t_cmd));
	if (data->history_lines)
		history_last->next = data->line;
	else
		data->history_lines = data->line;
	data->pipes = count_pipes(input);
	if (!data->line || !data->cmds || !data->history_lines)
		free_data(data);
}

void	free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cmds)
		free(data->cmds);
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

//t_cmd	*parse_cmds()

/*
t_lex	*get_tokens(char *line)
{
	
	
	t_lex	*lex;
	int	i;

	lex = malloc(sizeof(t_lex));
	if (!lex)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '<')
			lex->infile = get_infile(&line[i], &i);
		else if (line[i] == '>')
			lex->outfile = get_outfile(&line[i]);
		else if (line[i] == '|')
			get_command(&line[i]);
		else
			get_command(&line[i]);
		i++;
	}
	return (lex);
}

char	*get_infile(char *line, int *index)
{
	int	i;

	i = 0;
	if (line[i + 1] == '<')
	{
		// <<
	}
	else
	{
		// <
		while (ft_isspace(line[i]))
			i++;
		*index += i;
		while (line[i])
		{
			if (line[i] == '\'')
			{
				//cpy hasta '\''
				ft_strdup_set(&line[i], "\'");
				*index += ft_strlen_set(&line[i], "\'");
			}
			else if (line[i] == '\"')
			{
				//cpy hasta '\"'
				ft_strdup_set(&line[i], "\"");
				*index += ft_strlen_set(&line[i], "\"");
			}
			else
			{
				// cpy hasta ft_isspace(line[i])
				ft_strdup_set(&line[i], " \t\n\v\r\f");
				*index += ft_strlen_set(&);
			}
		}
	}
}
*/