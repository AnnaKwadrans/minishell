#include  <stdlib.h>
#include  <stdio.h>
#include "parser.h"
#include "data.h"
 
/* Where the environment variable 'PATH' is set to a value. */
/*
int main(int agrc, char **argv, char **envp)
{
    char *pathvar;
 
    //pathvar = getenv("PATH");
    //printf("pathvar=%s",pathvar);
    char *name;
 	
        name = get_var("PATH sdhgbsdk egaea");
        printf("name: %s\n", name);
         
 	//free(name);

 	
        return (0);
 }
*/
/*
int    main(void)
{
       char   **array;
       char   *line;
       s_cmd   **cmds;
       
       line = ft_strdup(" VAR=abc; ' cat -e | pipe' def | ghi  ");
       array = split_pipes(line, ';');
       print_array(array);
       free_array(array);
       free(line);

       line = ft_strdup(" VAR=abc | ' cat -e | pipe' def | ghi  ");
       array = split_pipes(line, '|');
       print_array(array);
       free_array(array);
       free(line);

       line = ft_strdup(" VAR=abc | ' cat -e | pipe' def | ghi  | sort -R | grep \"hola\"   ");
       array = split_pipes(line, '|');
       print_array(array);
       free_array(array);
       free(line);
       return (0);
}
*/
