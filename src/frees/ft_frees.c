#include "minishell.h"
  
void ft_free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void ft_free_envp_lst(t_envp *my_envp)
{
    t_envp  *temp;

    while (my_envp != NULL)
    {
        temp = my_envp->next;
        free(my_envp->key);
        free(my_envp->value);
        free(my_envp);
        my_envp = temp;
    }
}

