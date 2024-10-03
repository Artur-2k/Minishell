#include <unistd.h> // access
#include <stdlib.h> // malloc free
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>


#include "../libft/libft.h" // ft_split (strtok) ft_strdup

#define MAX_ENV_VARS 100 // ter em atencao quando atingir este numero tens de dar handle corretamente
#define MAX_PATHS 100 // same

char **ft_copy_envp(char *envp[])
{
    char **my_envp;

    int i = 0;
    while(envp[i])
        i++;

    my_envp = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i] != NULL)
    {
        my_envp[i] = ft_strdup(envp[i]);
        i++;
    }
    my_envp[i] = NULL;
    return (my_envp);
}

char *ft_find_path(char **my_envp)
{
    char *path_var = NULL;
    int j = 0;
    while (my_envp[j] != NULL)
    {
        if (ft_strncmp(my_envp[j], "PATH=", 5) == 0)
        {
            path_var = my_envp[j] + 5; // skip over PATH= and is now pointing to the first path
            break ;
        }
        j++;
    }
    if (!path_var || !*path_var) // nao tem path ou nao tem nenhum valor PATH= o
        return NULL;
	return path_var;
}

char *ft_check_paths_for_cmd(char **paths, char *cmd)
{
    char *full_path;
    int j = 0;
    while (paths[j] != NULL)
    {
        paths[j] = ft_append_char_to_str(paths[j], '/');
        full_path = ft_strjoin(paths[j], cmd);
        if (access(full_path, X_OK) == 0)
        {
            printf("Comando ENCONTRADO!\n");
            break ;
        }
        free(full_path); // comando errado freed
        full_path = NULL;
        j++;
    }
    return full_path;
}

void ft_free(char **my_envp, char **paths, char *full_path, char**options)
{
    // free all
    int i = 0;
    while (my_envp[i] != NULL)
        free(my_envp[i++]);
    free(my_envp);
    i = 0;
    while (paths[i] != NULL)
        free(paths[i++]);
    free(paths);
    free(full_path);
    for (int j = 0; j < 2; j++) {
        free(options[j]);
    }
    free(options);
}

int main(int ac, char **av, char *envp[])
{
    // input simulation of input after parsing: ls -la
    char *cmd = "ls";
    char **options = malloc(3 * sizeof(char *));
    options[0] = ft_strdup("ls");
    options[1] = ft_strdup("-la");
    options[2] = NULL;

    // dinamic envp
    char **my_envp;
    my_envp = ft_copy_envp(envp);

    // getting paths
    char *path_var;
    path_var = ft_find_path(my_envp);
    if (!path_var) // nao tem nenhum PATH
        return -1;
    char **paths = ft_split(path_var, ':');
    if (!paths)
        return -2;

    // checking if there is a comand from paths
    char *full_path = ft_check_paths_for_cmd(paths, cmd);
    if (!full_path)
    {
        ft_free(my_envp, paths, full_path, options);
        printf("no comand\n");
        return -3;
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        // child
        if(execve(full_path, options, NULL) == -1)
            return -42;
    }
    wait(NULL);
    ft_free(my_envp, paths, full_path, options);
    return 0;
}