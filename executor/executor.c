#include "../data.h"
#include "../parser.h"
#include "../executor.h"

int	handle_infile(char *infile, char *delimit)
{
	int	fd;

	if (delimit)
	{
		// heredoc
		return (0);
	}
	else
	{
		if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
		{
			perror("Cannot access infile");
			return (-1);
		}
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			perror("Open failed");
		return (fd);
	}
}

int	handle_outfile(char *outfile, int append)
{
	int	fd;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Cannot access outfile");
		return (-1);
	}
	if (append)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666); // check permisos
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666); // check permisos
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

void	exec_cmd(t_cmd *cmd)
{
	char	*path_var;
	char	**path_tab;
	char	*path;

	path_var = getenv("PATH");
	path_tab = ft_split(path_var + 5, ':');
	path = get_path(cmd->args, path_tab);
	if (path_tab)
		free_array(path_tab);
	if (path)
	{
		printf("PATH %s\n", path);
		cmd->p_status = execve(path, cmd->args, cmd->env);
		free(path);
		perror("Execve failed");
	}
	else
	{
		ft_putendl_fd("Command not found", 2);
		cmd->p_status = 127;
		printf("EXIT %d\n", cmd->p_status);
		exit(127);
	}
	return ;
}

char	*get_path(char **cmd_tab, char **path_tab)
{
	int		i;
	char	*aux;
	char	*path;

	if (path_tab == NULL || cmd_tab == NULL)
		return (NULL);
	if (!cmd_tab[0])
		cmd_tab[0] = ft_strdup("cat");
	i = 0;
	while (path_tab[i] != NULL)
	{
		if (ft_strncmp(cmd_tab[0], path_tab[i], ft_strlen(path_tab[i])) == 0)
			path = ft_strdup(cmd_tab[0]);
		else
		{
			aux = ft_strjoin(path_tab[i], "/");
			path = ft_strjoin(aux, cmd_tab[0]);
			free(aux);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
