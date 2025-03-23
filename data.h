typedef struct s_data
{
	char	**line;
	char	**env;
}	t_minishell;

typedef struct s_lines
{
	char			*line;
	int				status;
	struct s_lines	*next;
}	t_lines;

typedef	struct	s_lines_list
{
	t_lines	*top;
	t_lines	*next;
	int		size;
}	t_lines;
