#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../here_doc/here_doc.h"
#include "../vars/varenv.h"

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
	bool	q_simple;
	bool	q_double;

	res = (char *)malloc(sizeof(char) * (count_no_quotes(arg) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && q_simple == 0 && q_double == 0)
		{
			q_simple = 1;
			i++;
		}
		else if (arg[i] == '\'' && q_simple == 1)
		{
			q_simple = 0;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 0 && q_simple == 0)
		{
			q_double = 1;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 1)
		{
			q_double = 0;
			i++;
		}
		else
		{
			res[j] = arg[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}

int	count_no_quotes(char *arg)
{
	int	i;
	int	count;
	bool	q_simple;
	bool	q_double;

	i = 0;
	count = 0;
	q_simple = 0;
	q_double = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' && q_simple == 0 && q_double == 0)
		{
			q_simple = 1;
			i++;
		}
		else if (arg[i] == '\'' && q_simple == 1)
		{
			q_simple = 0;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 0 && q_simple == 0)
		{
			q_double = 1;
			i++;
		}
		else if (arg[i] == '\"' && q_double == 1)
		{
			q_double = 0;
			i++;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}
