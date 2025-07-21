/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:26:11 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 11:53:34 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static char	*copy_temp(char *line, int *i)
{
	char	*temp;
	int		start;
	int		end;

	(*i)++;
	new_i(line, i, "spaces");
	start = *i;
	new_i(line, i, "word");
	end = *i;
	if (start < 0 || end < 0 || start >= end || !line)
		return (NULL);
	temp = malloc(end - start + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, line + start, end - start + 1);
	return (temp);
}

static int	process_outfile(char **outfiles, char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				cmd->append = 1;
				i++;
			}
			tmp = copy_temp(line, &i);
			if (!tmp || !tmp[0])
				return (-1);
			outfiles[j++] = ft_strdup(tmp);
			free(tmp);
		}
	}
	outfiles[j] = NULL;
	return (0);
}

char	**outfile_heredoc(char *line, t_cmd *cmd)
{
	char	**outfiles;
	int		count;

	count = count_outfiles(line);
	if (count == 0)
		return (NULL);
	outfiles = malloc(sizeof(char *) * (count + 1));
	if (!outfiles)
		return (NULL);
	if (process_outfile(outfiles, line, cmd) == -1)
	{
		free(outfiles);
		return (NULL);
	}
	return (outfiles);
}
