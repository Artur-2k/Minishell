/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:13:30 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/23 17:24:14 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_redirects(t_redir *redir)
{
    while (redir)
    {
        if (redir->type == INREDIR)
        {
            if (!access(redir->redir, R_OK)) // success
            {
                close(STDIN_FILENO);
                if (open(redir->redir, O_RDONLY) < 0) // TODO ERROR CHECK
                    return (-1);
            }
            else // error
            {
                printf("%s : nao tenho permissao\n", redir->redir);
                return (-2); // TODO 
            }
        }
        else if (redir->type == OUTREDIR)
        {
            close(STDOUT_FILENO);
            errno = 0;
            if (open(redir->redir, O_CREAT | O_WRONLY | O_TRUNC, 0777) < 0)
            {
                if (errno == EACCES)
                {
                    ft_putstr_fd(redir->redir, 2);
                    ft_putstr_fd(": Permission denied\n", 2);
                }
                perror(redir->redir);
            }
        }
        else if (redir->type == APPREDIR)
        {
            close(STDOUT_FILENO);
            errno = 0;
            if (open(redir->redir, O_CREAT | O_WRONLY | O_APPEND, 0777) < 0)
            {
                if (errno == EACCES)
                {
                    ft_putstr_fd(redir->redir, 2);
                    ft_putstr_fd(": Permission denied\n", 2);
                }
                perror(redir->redir);
            }
        }
        else if (redir->type == HDREDIR) // TODO HEREDOC
        {}
        else // other bad redir type
            return (-10);
        redir = redir->next;
    }
    return (0); // success
}
