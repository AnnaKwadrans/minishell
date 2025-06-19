/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:02:46 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/19 20:19:39 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../parser.h"
#include "../executor.h"
#include "../vars/varenv.h"

int	handle_infile(t_cmd *cmd, t_data *data)
{
	if (cmd->heredoc)
		return (0);
	else
	{
		if (check_infile(cmd->infile, data) == -1)
			return (-1);
		if (open_infile(cmd, data) == -2)
			return (-2);
	}
        return (0);
}

int	check_infile(char **infile, t_data *data)
{
	int	i;
	
	i = 0;
	while (infile[i])
	{
		if (access(infile[i], F_OK) == -1)
		{
			perror("No such file");
			data->last_status = 1;
			return (-1);
		}
		if (access(infile[i], R_OK) == -1)
		{
			perror("Permission denied");
			data->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_infile(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->infile[i])
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = open(cmd->infile[i], O_RDONLY);
		if (cmd->fd_in == -1)
		{
			perror("Open failed");
			data->last_status = 1;
			return (-2);
		}
		i++;
	}
	return (0);
}

int	handle_outfile(t_cmd *cmd, t_data *data)
{
	int	fd;

        if (check_outfile(cmd->outfile, data) == -1)
                return (-1);
        if (open_outfile(cmd, data) == -2)
                return (-2);
	return (0);
}

int	check_outfile(char **outfile, t_data *data)
{
	int	i;

	i = 0;
	while (outfile[i])
	{
		if (access(outfile[i], F_OK) == 0 && access(outfile[i], W_OK) == -1)
		{
			perror("Permission denied");
			data->last_status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	open_outfile(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->outfile[i])
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (cmd->append)
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			perror("Open failed");
			data->last_status = 1;
			return (-2);
		}
		i++;
	}
	return (0);
}
void	exec_cmd(t_cmd *cmd)
{
	char	*path_var;
	char	**path_tab;
	char	*path;
	char	**str_vars;
	int		i;
	int		j;

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		cmd->p_status = 127;
		return ;
	}
	else
	{
		str_vars = vars_to_char(cmd->data->vars);
		path_var = get_paths(cmd->data);
		if (path_var == NULL || ft_strlen(path_var) < 5)
		{
			ft_putendl_fd("PATH variable not set or empty", 2);
			cmd->p_status = 127;
			exit(127);
		}
		path_tab = ft_split(path_var + 5, ':');
		path = get_path(cmd->args, path_tab);
	}
	if (path_tab)
		free_array(path_tab);
	if (path)
	{
		cmd->p_status = execve(path, cmd->args, str_vars);
		free(path);
		perror("Execve failed");
		cmd->p_status = -1;
		exit(-1);
	}
	else
	{
		ft_putendl_fd("Command not found", 2);
		cmd->p_status = 127;
		exit(127);
	}
	return ;
}

char	*get_paths(t_data *data_program)
{
	char	*path_var;
	char	*pwd_var;
	char	*all_paths;
	char	*aux;

	path_var = get_var_value(data_program, "PATH");
	pwd_var = get_var_value(data_program, "PWD");
	aux = ft_strjoin(path_var, ":");
	free(path_var);
	all_paths = ft_strjoin(aux, pwd_var);
	free(aux);
	return(all_paths);
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

char	**vars_to_char(t_vars *vars)
{
	t_vars	*temp;
	int		size;
	char	**str_vars;
	int		i;

	temp = vars;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	str_vars = malloc(sizeof(char *) * size);
	if (!str_vars)
		return (NULL);
	temp = vars;
	i = 0;
	while (temp)
	{
		str_vars[i] = get_str_var(temp->name, temp->value);
		i++;
		temp = temp->next;
	}
	return (str_vars);
}

char	*get_str_var(char *name, char *value)
{
	char	*str_var;
	char	*aux;

	aux = ft_strjoin(name, "=");
	str_var = ft_strjoin(aux, value);
	free(aux);
	return (str_var);
}
