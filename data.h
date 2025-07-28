/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:40:03 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/28 01:45:10 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>

# include "libft/libft.h"
# include "signals/signals.h"
# include "aux/aux.h"

extern int					g_signal;

typedef struct s_heredoc	t_heredoc;
typedef struct s_data		t_data;
typedef struct s_vars		t_vars;
typedef struct s_cmd		t_cmd;

typedef struct s_expand
{
	t_data	*data;
	char	**values;
	int		count;
}	t_expand;

typedef struct s_heredoc
{
	char	**delimiters;
	char	*last_delimiter;
	int		is_expandable;
	char	**buffer;
	t_data	*data;
}	t_heredoc;

typedef struct s_data
{
	struct s_cmd	**cmds;
	struct s_vars	*vars;
	int				pipes;
	int				is_interactive;
	int				is_expandable;
	int				*fds;
	int				last_status;
}	t_data;

typedef struct s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*next;
	int				is_exportable;
	t_data			*data;
}	t_vars;

typedef struct s_cmd
{
	char		**args;
	char		**infile;
	int			fd_in;
	char		**outfile;
	int			fd_out;
	int			append;
	t_heredoc	*heredoc;
	pid_t		pid;
	int			p_status;
	t_data		*data;
	bool		is_builtin;
}	t_cmd;

void	free_cmd(t_cmd *cmd);

#endif
