/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:15:54 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 15:29:44 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    **ft_recreate_envp(t_envp *l_envp)
{
    char    **envp;
    t_envp  *backup;
    int     len;

    if (!l_envp)
        return (NULL);
    backup = l_envp;
    len = 0;
    while (l_envp && ++len) //! short circuiting for lines WATCH OUT
        l_envp = l_envp->next;
    l_envp = backup;
    envp = (char **)malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return (NULL);
    len = 0;
    while (l_envp)
    {
        envp[len] = ft_strappend(ft_strjoin(l_envp->key, "="), l_envp->value); //! WATCH OUT FOR NULL PARAMS
        if (!envp[len])
            return (ft_free_str_arr(envp), NULL);
        len++;
        l_envp = l_envp->next;
    }
    envp[len] = NULL;
    return (envp);
}



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
        if (tkns[i]->token && tkns[i]->type == EXEC)
            len++;
        i++;
    }
	printf("cmd len = [%d]\n", len); // TODO deleteme
    return (len);
}

static int    ft_new_redir(t_exec *cmd, t_tokens **tkns)
{
    t_redir *new;
    t_redir   *cur;

    new = (t_redir*)ft_calloc(1, sizeof(t_redir));
    if (!new) // Malloc error
        return (1); // Malloc error
    if (!ft_strcmp(tkns[0]->token, "<"))
        new->type = INREDIR;
    else if (!ft_strcmp(tkns[0]->token, "<<"))
        new->type =  HDREDIR;
    else if (!ft_strcmp(tkns[0]->token, ">"))
        new->type = OUTREDIR;
    else
        new->type = APPREDIR;
    new->redir = ft_strdup(tkns[1]->token);
    if (!new->redir)
        return (free(new), ft_free_redir_list(&cmd->redir_list), 2); // Malloc error
    if (cmd->redir_list == NULL)
        cmd->redir_list = new;
    else
    {
        cur = cmd->redir_list;
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
    return (0); // Success
}

t_cmd  *ft_build_exec(t_tokens ***tkns, t_shell *shell)
{
    t_exec  *cmd;
    int     i;
    int     j;

    cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
    if (!cmd)
        return (NULL);

    cmd->type = EXEC;
    cmd->av = (char**)ft_calloc((ft_cmd_len(*tkns) + 1), sizeof(char *));
    if (!cmd->av)
        return (free(cmd), NULL);
    i = 0;
    j = 0;
    // (null) cmd ola < infile | cmd > outfile
     while ((*tkns)[i] && (*tkns)[i]->type != PIPE)
    {
		if ((*tkns)[i]->token == NULL)
			i++;
        else if ((*tkns)[i]->type != EXEC)
        {
            if (ft_new_redir(cmd, &(*tkns)[i])) // Malloc error
                return (ft_free_str_arr(cmd->av), free(cmd), NULL);                               
            i += 2;
        }
        else
		{
            cmd->av[j] = ft_strdup((*tkns)[i]->token);
            if (!cmd->av[j]) // Malloc Error
                return (ft_free_str_arr(cmd->av), ft_free_redir_list(&cmd->redir_list), free(cmd), NULL);
			j++;
			i++;
		}
    }
    cmd->av[j] = NULL;
    cmd->envp = shell->my_envp_h;
    if (shell->my_envp_h)
        cmd->tenvp = ft_recreate_envp(shell->my_envp_h);
    (*tkns) += i;
    return ((t_cmd *)cmd);
}