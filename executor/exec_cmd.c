/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:18 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/21 19:53:54 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec_cmd(t_cmd *cmd)
{
	char	*path;
	char	**str_vars;

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
		exit(127);
	str_vars = vars_to_char(cmd->data->vars);
	path = get_exec_path(cmd);
	if (path)
	{
		cmd->p_status = execve(path, cmd->args, str_vars);
		free(path);
		perror("Execve failed");
		clean_data_program(cmd->data);
		exit(2);
	}
	else
	{
		ft_putendl_fd("Command not found", 2);
		clean_data_program(cmd->data);
		exit(127);
	}
	return ;
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
	str_vars[i] = NULL;
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

char	*get_exec_path(t_cmd *cmd)
{
	char	*path_var;
	char	**path_tab;
	char	*path;

	path_var = get_paths(cmd->data);
	if (path_var == NULL || ft_strlen(path_var) < 5)
	{
		ft_putendl_fd("PATH variable not set or empty", 2);
		cmd->p_status = 127;
		exit(127);
	}
	path_tab = ft_split(path_var + 5, ':');
	free(path_var);
	path = get_path(cmd->args, path_tab);
	if (path_tab)
		free_array(path_tab);
	return (path);
}
