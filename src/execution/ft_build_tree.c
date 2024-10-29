/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:12 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/28 17:33:26 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_cmd_len(char **tkn_arr, t_shell *shell)
{
    int len;
    int i;
    

    len = 0;
    // cat < file1 | teste arg2 > file2
    i = 0;
    while (tkn_arr[i])
    {
        if (shell->tkn_types[shell->n + i] == PIPE)
            break ;
        if (shell->tkn_types[shell->n + i] == EXEC)
            len++;
        i++;
    }
    return (len);
}

static void    ft_new_redir(t_exec *cmd, char **tkn_arr)
{
    t_redir *new;
    t_redir   *cur;
    
    new = (t_redir*)ft_calloc(1, sizeof(t_redir));
    if (!ft_strcmp(tkn_arr[0], "<"))
        new->type = INREDIR;
    else if (!ft_strcmp(tkn_arr[0], "<<"))
        new->type =  HDREDIR;
    else if (!ft_strcmp(tkn_arr[0], ">"))
        new->type = OUTREDIR;
    else
        new->type = APPREDIR;
    new->redir = ft_strdup(tkn_arr[1]);
    if (cmd->redir_list == NULL)
        cmd->redir_list = new;
    else
    {
        cur = cmd->redir_list;
        while (cur->next)    
            cur = cur->next;
        cur->next = new;
    }
}

t_cmd  *ft_build_exec(char ***tkn_arr, t_shell *shell)
{
    t_exec  *cmd;
    int     i;
    int     j;

    cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
    cmd->type = EXEC;
    cmd->av = (char**)malloc(sizeof(char *) * (ft_cmd_len(*tkn_arr, shell) + 1));
    i = 0;
    j = 0;
    // cmd ola < infile | cmd > outfile
    while ((*tkn_arr)[i] && shell->tkn_types[shell->n] != PIPE)
    {
        if (shell->tkn_types[shell->n] != EXEC)
        {
            ft_new_redir(cmd, &(*tkn_arr)[i]); 
            i += 2;
            shell->n += 2;
        }
        else
        {
            cmd->av[j++] = ft_strdup((*tkn_arr)[i++]);
            shell->n++;
        }
    }
    cmd->av[j] = NULL;
    cmd->envp = shell->my_envp_h;
    if (shell->my_envp_h)
        cmd->tenvp = ft_recreate_envp(shell->my_envp_h);
    *tkn_arr = *tkn_arr + i;
    return ((t_cmd *)cmd);
}

t_cmd   *ft_build_pipe(t_cmd *cmd, char **tkn_arr,t_shell *shell)
{
    t_pipe  *pipe;

    pipe = (t_pipe *)malloc(sizeof(t_pipe));
    if (!pipe) //todo error
    {}
    pipe->type = PIPE;
    pipe->left = cmd;
    pipe->right = ft_build(tkn_arr, shell);
    
    return ((t_cmd *)pipe);
}

t_cmd   *ft_build(char **tkn_arr, t_shell *shell)
{
    t_cmd  *cmd;

    cmd = ft_build_exec(&tkn_arr, shell);
    if (*tkn_arr && shell->tkn_types[shell->n] == PIPE)
    {
        tkn_arr++;
        shell->n++;
        cmd = ft_build_pipe((t_cmd *)cmd, tkn_arr, shell);
    }
    return (cmd);
}
