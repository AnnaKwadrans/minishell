/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:40:38 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/30 18:39:48 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*expand_vars(t_data *data_program, char *str, bool rm_quotes,
			bool free_line);
char	**ft_full_split(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	rl_replace_line(const char *text, int clear_undo);

int	here_doc_init(char *line, t_heredoc *here_doc, t_data *data_program)
{
	int		check;
	t_ctx	*ctx;

	here_doc->delimiters = NULL;
	here_doc->buffer = NULL;
	here_doc->last_delimiter = NULL;
	here_doc->is_expandable = 0;
	here_doc->data = data_program;
	g_signal = 0;
	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (here_doc_error(here_doc, "MALLOC"), 1);
	here_doc->ctx = ctx;
	setup_heredoc_signals();
	if (delimeters_validator(line))
		return (here_doc_error(here_doc, "DELIMITERS"), 1);
	get_delimiters(line, here_doc);
	if (!here_doc->delimiters)
		here_doc_error(here_doc, "PARSE");
	here_doc->last_delimiter = here_doc->delimiters
	[array_size(here_doc->delimiters) - 1];
	return (0);
}

static void	finishing_here_doc(t_heredoc *here_doc, t_data *data_program)
{
	int	i;

	if (!here_doc)
		return ;
	if (here_doc->buffer && here_doc->is_expandable)
	{
		i = 0;
		while (here_doc->buffer[i])
		{
			here_doc->buffer[i] = expand_vars(data_program, here_doc->buffer[i],
					0, 1);
			if (!here_doc->buffer[i])
				return (here_doc_error(here_doc, "EXPAND_VARS"));
			i++;
		}
	}
	if (data_program->is_interactive)
		setup_interactive_signals();
	else
		restore_signals();
}

int	check_delimeters(char *line, t_heredoc *here_doc)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	while (here_doc->delimiters[i])
	{
		found = ft_strcmp(here_doc->delimiters[i], line);
		if (!found)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	read_heredoc_loop(t_heredoc *here_doc)
{
	char	*new_line;

	new_line = NULL;
	while (here_doc && here_doc->delimiters)
	{
		write(1, "heredoc > ", 10);
		new_line = remove_trailing_newline(get_next_line(STDIN_FILENO));
		if (!new_line || g_signal)
		{
			if (new_line)
				free(new_line);
			new_line = NULL;
			break ;
		}
		if (ft_strcmp(here_doc->last_delimiter, new_line) == 0)
		{
			here_doc->buffer = add_buffer(here_doc->buffer, ft_strdup(""));
			return (free(new_line), 0);
		}
		else if (!check_delimeters(new_line, here_doc))
			here_doc->buffer = add_buffer(here_doc->buffer, new_line);
		if (!here_doc || !here_doc->buffer)
			return (free(new_line), here_doc_error(here_doc, "MALLOC"), 1);
	}
	return (0);
}

t_heredoc	*here_doc_mode(t_data *data_program, char *line)
{
	t_heredoc	*here_doc;

	here_doc = malloc(sizeof(t_heredoc));
	if (!here_doc)
		return (here_doc_error(here_doc, "MALLOC"), NULL);
	if (here_doc_init(line, here_doc, data_program))
		return (NULL);
	if (read_heredoc_loop(here_doc))
		return (NULL);
	if (g_signal)
		return (here_doc_error(here_doc, "SIGINT"), NULL);
	finishing_here_doc(here_doc, data_program);
	return (here_doc);
}
