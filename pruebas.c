#include  <stdlib.h>
#include  <stdio.h>
#include "lexer.h"
 
/* Where the environment variable 'PATH' is set to a value. */

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

t_data  *data;

