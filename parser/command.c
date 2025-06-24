#include "parser.h"
#include "../data.h"
#include "../libft/libft.h"
#include "../here_doc/here_doc.h"
#include "../vars/varenv.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	//cmd->env = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	//cmd->delimit = NULL;
	cmd->heredoc = NULL;
	cmd->data = NULL;
	cmd->p_status = 0;
	cmd->pid = 0;
	cmd->is_builtin = 0;
}

t_cmd	*get_cmd(char *aux)
{
	t_cmd	*cmd;
	int		i;

        printf("%s\n", aux);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (perror("malloc failed"), NULL);
	init_cmd(cmd);
	i = 0;
	//printf("get_cmd - aux: %s\n", aux);
	while (aux[i])
	{
		if (ft_isspace(aux[i]))
			i++;
		else if (aux[i] == '<')
			get_infile(&aux[i], &i, &cmd->infile);
		else if (aux[i] == '>')
			get_outfile(&aux[i], &i, &cmd->outfile, &cmd->append);
		else if (!cmd->args)
			cmd->args = get_args(&aux[i], &i);
		else
			cmd->args = append_args(cmd->args, &aux[i], &i);
	}
	if (cmd->args)
		cmd->args = rm_quotes(cmd->args);
	else
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return (free_cmd(cmd), NULL);
		cmd->args[0] = ft_strdup("cat");
		cmd->args[1] = NULL;
	}
	// printf("ARGS\n");
	// print_array(cmd->args);
	return (cmd);
}

