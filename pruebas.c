#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *ent;

    // Open the directory
    if ((dir = opendir(path)) == NULL) {
        fprintf(stderr, "Could not open directory %s: %s\n",
                path, strerror(errno));
        return;
    }

    // Read and display each entry
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }

    // Close the directory
    if (closedir(dir) == -1) {
        fprintf(stderr, "Error closing directory: %s\n",
                strerror(errno));
    }
}
/*
int main() {
    char cwd[1024];

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "Error getting current directory: %s\n",
                strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Current directory: %s\n", cwd);

    // List contents of current directory
    printf("\nContents:\n");
    list_directory(".");

    // Try to change directory
    if (chdir("~") == -1) {
        fprintf(stderr, "Could not change to subdir: %s\n",
                strerror(errno));
    } else {
        printf("\nChanged to new directory\n");
        
        // Verify the change
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("New current directory: %s\n", cwd);
        }
    }

    return EXIT_SUCCESS;
}
*/


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
