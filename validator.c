#include "data.h"
#include "parser.h"
#include "executer.h"
#include "vars/varenv.h"

bool    valid_pipes(char *line)
{
        int     i;
        bool    pipe;

        pipe = 0;
        i = 0;
        while (line[i])
        {
                if (line[i] == '|')
                {
                        i++;
                        while (ft_isspace(line[i]))
                        {
                                if (line[i + 1] == '|')
                                        return (0);
                                i++;
                        }
                }
                i++;
        }
        return (1);
}

bool    is_var(char *line)
{
        int     i;
        
        i = 0;
        while(line[i])
        {
                if (line[i]== '=')
                        return (1);
        }
        return (0);
}

void    handle_var(char *input, t_data *data)
{
        t_vars	*var;
        char    *name;
        char    *value;
        int     i;

        i = 0;
        while (ft_isspace(input[i]))
                i++;
        name = ft_strdup_set(&input[i], "=");
        while (input[i] != '=')
                i++;
        value = ft_strdup_set(&input[i + 1], " \t\n\v\r\f");
        var = new_var(name, value, 0);
        add_var(data, var);
}