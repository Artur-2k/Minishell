/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theres_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:21:05 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/02 15:25:21 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * @brief Check if theres heredocs in the tokens array 
 * @param (t_token*) Array of tokens
 * @return amount of heredocs in the token array | 0 if dont find
*/
int     ft_theres_heredoc(t_tokens **tkns)
{
    int i;
    /* int count; */
    
    i = 0;
    /* count = 0; */
    while(tkns[i] != NULL)
    {
        if (ft_strcmp(tkns[i]->token, "<<") == 0)
            return (1);
        i++;
    }
    return (0);
}

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
    /* printf("[DIRETORIO COMPLETO HEREDOC]: %s\n", result); */
    index++;
    free(index_itoa);
    return (result);
}

/* 
 * @brief Retorna o redir do respectivo heredoc
 * @param (t_tokens**) tkns
 * @return (String) Pathname 
*/
char    *ft_redir_after_heredoc(t_tokens **tkns)
{
    int i;

    i = 0;
    while(tkns[i])
    {
        if (ft_strcmp(tkns[i]->token, ">"))
            return (tkns[i+ 1]->token);
        i++;
    }
    return (NULL);
}