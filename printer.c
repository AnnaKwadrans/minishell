#include	"data.h"

void	ft_printer_lines(t_lines *lines)
{
	t_lines	*temp;

	temp = lines;
	while (temp)
	{
		printf("\t%d\t%s\n", temp->index, temp->line);
		temp = temp->next;
	}
}

// void	ft_printer_data(t_data *data)
// {
// 	int		i;
// 	t_cmd	*temp_cmd;

// 	i = 0;
// 	temp_cmd = data->cmd;
// 	while (temp_cmd)
// 	{
// 		printf()
// 	}
	
// }
