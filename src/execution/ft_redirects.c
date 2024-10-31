/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:13:30 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 14:35:08 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Tries to redirect the stdin to the redir file name
// If open fails returns -1 and prints on stderr the
// appropriate error message
static int	ft_redirect_in(t_redir *redir)
{
	close(STDIN_FILENO);
	errno = 0;
	if (open(redir->redir, O_RDONLY) < 0)
	{
		ft_what_happened(redir->redir, strerror(errno));
 		return (-1); // errorP
	}
	return (0); // success
}

/* 
	fd = open ...
	dup2 (fd, 0);
 */

// Tries to redirect the stdout with truncate mode to the
// redir file name
// If open fails returns -1 and prints on stderr the
// appropriate error message
static int	ft_redirect_out(t_redir *redir)
{
	close(STDOUT_FILENO);
    errno = 0;
    if (open(redir->redir, O_CREAT | O_WRONLY | O_TRUNC, 0644) < 0)
	{
		ft_what_happened(redir->redir, strerror(errno));
 		return (-2); // error
	}
	return (0); // success
}

// Tries to redirect the stdout with append mode to the
// redir file name
// If open fails returns -1 and prints on stderr the
// appropriate error message
static int	ft_redirect_append(t_redir *redir)
{
	close(STDOUT_FILENO);
    errno = 0;
    if (open(redir->redir, O_CREAT | O_WRONLY | O_APPEND, 0644) < 0)
	{
		ft_what_happened(redir->redir, strerror(errno));
 		return (-3); // error
	}
	return (0); // success
}
// @brief Recieves the node's redir list and tries to redirect
// it's input &/ output based on the redir list.
//
// There is no need for closing any opened fds because they are opened
// at the stdfd;
// @param redir A pointer to the redir list head
// @return Returns 0 on success and a non-zero value in case of error
int ft_redirects(t_redir *redir)
{
	int	err;

	err = 0;
    while (redir && !err)
    {
        if (redir->type == INREDIR)
			err = ft_redirect_in(redir);
        else if (redir->type == OUTREDIR)
	        err = ft_redirect_out(redir);
        else if (redir->type == APPREDIR)
			err = ft_redirect_append(redir);
        else if (redir->type == HDREDIR) // TODO HEREDOC
        {}
        else // other bad redir type
            return (ft_putstr_fd("Invalid redirection type error\n", STDERR_FILENO), -5);
        redir = redir->next;
    }
    return (err); // 0 on success
}
