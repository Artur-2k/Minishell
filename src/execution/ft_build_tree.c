/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:12 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/29 19:39:45 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_cmd_len(t_tokens **tkns)
{
    int len;
    int i;
    

    len = 0;
    // cat < file1 | teste arg2 > file2
    i = 0;
    while (tkns[i])
    {
        if (tkns[i]->type == PIPE)
            break ;
        if (tkns[i]->type == EXEC)
            len++;
        i++;
    }
    return (len);
}

static void    ft_new_redir(t_exec *cmd, t_tokens **tkns)
{
    t_redir *new;
    t_redir   *cur;
    
    new = (t_redir*)ft_calloc(1, sizeof(t_redir));
    if (!new) {}; // TODO malloc error
    if (!ft_strcmp(tkns[0]->token, "<"))
        new->type = INREDIR;
    else if (!ft_strcmp(tkns[0]->token, "<<"))
        new->type =  HDREDIR;
    else if (!ft_strcmp(tkns[0]->token, ">"))
        new->type = OUTREDIR;
    else
        new->type = APPREDIR;
    new->redir = ft_strdup(tkns[1]->token);
    if (!new->redir){}; // TODO malloc error
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

t_cmd  *ft_build_exec(t_tokens ***tkns, t_shell *shell)
{
    t_exec  *cmd;
    int     i;
    int     j;

    cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
    if (!cmd){}; // TODO malloc error
    cmd->type = EXEC;
    cmd->av = (char**)malloc(sizeof(char *) * (ft_cmd_len(*tkns) + 1));
    if (!cmd->av){}; // TODO malloc error
    i = 0;
    j = 0;
    // cmd ola < infile | cmd > outfile
    while ((*tkns)[i] && (*tkns)[i]->type != PIPE)
    {
        if ((*tkns)[i]->type != EXEC)
        {
            ft_new_redir(cmd, &(*tkns)[i]); 
            i += 2;
        }
        else
            cmd->av[j++] = ft_strdup((*tkns)[i++]->token);
    }
    cmd->av[j] = NULL;
    cmd->envp = shell->my_envp_h;
    if (shell->my_envp_h)
        cmd->tenvp = ft_recreate_envp(shell->my_envp_h);
    (*tkns) += i;
    return ((t_cmd *)cmd);
}

t_cmd   *ft_build_pipe(t_cmd *cmd, t_tokens **tkns ,t_shell *shell)
{
    t_pipe  *pipe;

    pipe = (t_pipe *)malloc(sizeof(t_pipe));
    if (!pipe) //TODO malloc error
    {}
    pipe->type = PIPE;
    pipe->left = cmd;
    pipe->right = ft_build(tkns, shell);
    
    return ((t_cmd *)pipe);
}

t_cmd   *ft_build(t_tokens **tokens, t_shell *shell)
{
    t_cmd  *cmd;

    cmd = ft_build_exec(&tokens, shell);
    if (*tokens && (*tokens)->type == PIPE)
    {
        tokens++;
        cmd = ft_build_pipe((t_cmd *)cmd, tokens, shell); //TODO
    }
    return (cmd);
}
