#include "data.h"

void	add_mhistory(t_data *data_program, t_cmd *cmd)
{

}

void	show_history(void *arg)
{
	t_data	*data_program;

	data_program = (t_data *)arg;
	ft_printer_lines(data_program->history_lines);
}
