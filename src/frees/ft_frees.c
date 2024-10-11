#include "minishell.h"
  
static void ft_free_str_arr(char **arr)
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

static void ft_free_envp_lst(t_envp *my_envp)
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

void        ft_free_resources(int count, ...)
{
    va_list         args;
    t_resource_type type;
    int             i;

    va_start(args, count);
    i = 0;
    while (i < count)
    {
        type = va_arg(args, t_resource_type); // t_resource_type == int
        if (type == PTR) // basic type
            free(va_arg(args, void*));
        else if (type == STR_ARR) // string array
            ft_free_str_arr(va_arg(args, void*));
        else if (type == ENV_PTR) // env linked list
            ft_free_envp_lst(va_arg(args, void*));
        i++;
    }
    va_end(args);
}
