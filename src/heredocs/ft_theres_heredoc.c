/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theres_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:21:05 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/09 16:57:54 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * @brief Generate a pathname to each heredoc to fill the t_heredoc
 * @param Void
 * @return (String) Pathname 
*/
char    *ft_gen_here_path(int pid)
{
    static int  index;
    char        *index_itoa;
    char        *result;

    result = NULL;
    index_itoa = ft_itoa(index);
    result = ft_strjoin("/tmp/here_doc_v", index_itoa);
    free(index_itoa);
    index_itoa = ft_itoa(pid);
    result = ft_strappend(result, index_itoa);
    index++;
    free(index_itoa);
    return (result);
}
