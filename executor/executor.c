#include "../data.h"
#include "../parser.h"
#include "../executor.h"
/*
int	exec_line(t_cmd ***cmds, int *pipes)
{
	int	i;
	int	j;
	int	fds[2];

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (pipe(fds) < 0)
			{
				// err pipe
			}
			cmds[i][j]->pid = fork();
			if (cmds[i][j]->pid < 0)
			{
				// err fork
			}
			else if (cmds[i][j]->pid == 0)
			{
				exec_cmd(cmds[i][j]);
			}
			else if (cmds[i][j]->pid > 0)
			{
				// parent
				waitpid(cmds[i][j]->pid, NULL, 0);
			}
			j++;
		}
		i++;
	}
	return (0);
}
*/
/*
int	execute_line(t_cmd ***cmds, int *pipes, int **fds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		fds = create_pipes(pipes[i]);
		first_child(cmds[i][j], j, fds);
		j = 1;
		while (cmds[i][j] && j < pipes[i])
		{
			new_child(cmds[i][j], pipes[i], j, fds[i]);
			j++;
		}
		if (j = pipes[i])
			last_child(cmds[i][j], j, fds[i]);
		free_fds(fds, pipes[i]);
		i++;
	}
	return (0);
}
*/
/*
int	new_child(t_cmd *cmd, int pipes, int process, int *fds)
{
	if (pipe(fds) < 0)
	{
		// err pipe
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		// err fork
	}
	else if (cmd->pid == 0)
	{
		// child
		if (index == 0 && index == pipes)
		{
			// no pipes
			if (cmd->infile)
				cmd->fd_in = handle_infile(cmd->infile, cmd->delimit);
			if (cmd->outfile)
				handle_outfile(cmd->outfile, cmd->append);
			cmd->p_status = exec_cmd(cmd);
			
		}
		else if (index == 0 && index != pipes)
		{
			// first pipe
			if (cmd->infile)
				handle_infile(cmd->infile, cmd->delimit);
			if (cmd->outfile)
				handle_outfile(cmd->outfile, cmd->append);
			else
				dup2(fds[1], STDOUT_FILENO);
			cmd->p_status = exec_cmd(cmd);
		}
		else if (index != 0 && index == pipes)
		{
			// last pipe
			if (cmd->infile)
				handle_infile(cmd->infile, cmd->delimit);
			else
				dup2(fds[0], STDIN_FILENO);
			if (cmd->outfile)
				handle_outfile(cmd->outfile, cmd->append);
			cmd->p_status = exec_cmd(cmd);
		}
		else
		{
			// middle pipe
			if (cmd->infile)
				handle_infile(cmd->infile, cmd->delimit);
			else
				dup2(fds[0], STDIN_FILENO);
			if (cmd->outfile)
				handle_outfile(cmd->outfile, cmd->append);
			else
				dup2(fds[1], STDOUT_FILENO);
			cmd->p_status = exec_cmd(cmd);
		}
	}
	else if (cmd->pid > 0)
	{
		// parent
		waitpid(cmd->pid, NULL, 0);
	}
	return (0);
}
*/
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

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		cmd->p_status = 127;
		return ;
	}
	path_var = getenv("PATH");
	path_tab = ft_split(path_var + 5, ':');
	path = get_path(cmd->args, path_tab);
	if (path_tab)
		free_array(path_tab);
	if (path)
	{
		cmd->p_status = execve(path, cmd->args, cmd->env);
		free(path);
		perror("Execve failed");
	}
	else
	{
		ft_putendl_fd("Command not found", 2);
		cmd->p_status = 127;
	}
	return ;
}
/*
char	**parse_path_var(char **envp)
{
	int		i;
	char	**path_tab;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0 && envp[i][5])
		{
			path_tab = ft_split(envp[i] + 5, ':');
			if (path_tab)
				return (path_tab);
		}
		i++;
	}
	return (NULL);
}
*/
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

