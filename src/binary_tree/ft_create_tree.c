/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:12 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/18 17:48:13 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

    build:
        node = new_exec_node
        if |:
            node = pipe(node, build)
        return (node);


*/

static int ft_cmd_len(char **tkn_arr)
{
    int len;
    int i;

    len = 0;
    // cat < file1 | teste arg2 > file2
    i = 0;
    while (tkn_arr[i])
    {
        if (tkn_arr[i][0] == '|')
            break ;
        if (!ft_strchr("<>", tkn_arr[i][0]))
            len++;
        i++;
    }
    return (len);
}

static void    ft_new_redir(t_exec *cmd, char **tkn_arr)
{
    t_redir *new;
    t_exec   *cur;
    
    new = (t_redir*)ft_calloc(1, sizeof(t_redir));
    if (ft_strcmp(tkn_arr[0], "<"))
        new->type = INREDIR;
    else if (ft_strcmp(tkn_arr[0], "<<"))
        new->type =  HDREDIR;
    else if (ft_strcmp(tkn_arr[0], ">"))
        new->type = OUTREDIR;
    else
        new->type = APPREDIR;
    new->redir = ft_strdup(tkn_arr[1]);
    if (cmd->redir_list == NULL)
        cmd->redir_list = new;
    else
    {
        cur = cmd->redir_list;
        while (cur->redir_list->next)    
            cur->redir_list = cur->redir_list->next;
        cur->redir_list->next = new;
    }
}

t_exec  *ft_build_exec(t_exec *cmd, char ***tkn_arr)
{
    t_exec  *cmd;
    int     i;
    int     j;

    cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
    cmd->type = EXEC;
    cmd->av = (char**)malloc(sizeof(char *) * (ft_cmd_len(*tkn_arr) + 1));
    i = 0;
    j = 0;
    // cmd ola < infile | cmd > outfile
    while (tkn_arr[i] && tkn_arr[i][0] != '|')
    {
        if (ft_strchr("<>", tkn_arr[i][0]))
        {
            ft_new_redir(cmd, &tkn_arr[i]); 
            i += 2;
        }
        else
            cmd->av[j++] = ft_strdup(tkn_arr[i++]);
    }
    *tkn_arr = *tkn_arr + i;
    return (cmd);
}



t_cmd *ft_build(char **tkn_arr)
{
    t_exec  *cmd;
    int     i;
    
    cmd = ft_build_exec(cmd, &tkn_arr);
    i = 0;
    while (tkn_arr[i])
    {
        if (tkn_arr[i] == '|')
            cmd = ft_build_pipe(cmd, &tkn_arr[i]); // todo
        i++;
    }
    return ((t_cmd*)cmd);
} 