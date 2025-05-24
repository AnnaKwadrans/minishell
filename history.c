#include "data.h"

// void	add_mhistory(t_data *data_program, char *input)
// {
// 	t_lines	*line;

// 	line = new_line(input, data_program);
// 	if (line == NULL)
// 	{
// 		perror("Error allocating memory for new line");
// 		return ;
// 	}
// 	new_line_history(line, data_program);
// }

void	show_history(void *arg)
{
	t_data	*data_program;
	t_lines	*temp;

	data_program = (t_data *)arg;
	temp = data_program->history_lines;
	while (temp)
	{
		ft_printer_lines(temp);
		temp = temp->next;
	}
}
