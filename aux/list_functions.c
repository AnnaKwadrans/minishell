#include "../data.h"

t_lines	*last_line_history(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_lines	*new_line(char *line, t_data *data_program)
{
	t_lines	*new;

	new = malloc(sizeof(t_lines));
	if (new == NULL)
		perror("Error allocating memory for new line");
	new->line = line;
	new->index = 0;
	new->next = NULL;
	new->data = data_program;
	return (new);
}

t_lines	*new_line_history(t_lines *line)
{
	t_data	*data_program;
	t_lines	*tmp;

	data_program = line->data;
	if (data_program->history_lines == NULL)
	{
		data_program->history_lines = line;
		data_program->history_lines->index = 1;
	}
	else
	{
		tmp = last_line_history(data_program->history_lines);
		tmp->next = line;
		tmp->next->index = tmp->index + 1;
	}
}
