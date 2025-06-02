/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:02:46 by akwadran          #+#    #+#             */
/*   Updated: 2025/06/01 19:07:08 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../data.h"
#include "../parser.h"
#include "../executor.h"
#include "../vars/varenv.h"

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
	char	**str_vars;

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		cmd->p_status = 127;
		return ;
	}
	// path_var = getenv("PATH");
	str_vars = vars_to_char(cmd->data->vars);
	path_var = get_var_value(cmd->data, "PATH");
	if (path_var == NULL || ft_strlen(path_var) < 5)
	{
		ft_putendl_fd("PATH variable not set or empty", 2);
		cmd->p_status = 127;
		exit(127);
	}
	path_tab = ft_split(path_var + 5, ':');
	path = get_path(cmd->args, path_tab);
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
