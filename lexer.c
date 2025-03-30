#include "lexer.h"

t_lex	**get_tokens(char *line)
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
