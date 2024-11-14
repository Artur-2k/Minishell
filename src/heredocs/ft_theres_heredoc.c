/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theres_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:21:05 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/14 17:11:51 by dmelo-ca         ###   ########.fr       */
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
    int count;
    
    i = 0;
    count = 0;
    while(tkns[i] != NULL)
    {
        if (ft_strcmp(tkns[i]->token, "<<") == 0)
            count++;
        i++;
    }
    return (count);
}

/* 
 * @brief Generate a pathname to each heredoc to fill the t_heredoc
 * @param Void
 * @return (String) Pathname 
*/
char    *ft_gen_here_path(void)
{
    static int index;

    return (ft_strjoin("here_doc_v", ft_itoa(index)));
}

t_heredoc     *ft_link_heredocs(t_tokens **tkns, t_heredoc *heredoc)
{
    t_heredoc   *cur;
    int         num_heredocs;
    char        *temp_path;
    int         i;

    cur = NULL;
    temp_path = NULL;
    num_heredocs = ft_theres_heredoc(tkns);
    i = 0;
    if (num_heredocs)
    {
        while (i++ < num_heredocs)
            if (!heredoc)
            {
                heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
                if (!heredoc)
                    return (NULL);
                temp_path = ft_gen_here_path();
                if (open(temp_path, O_CREAT | O_RDWR | O_TRUNC, 0644) < 0)
                    return (NULL);
                heredoc->path = temp_path;
                cur = heredoc;
            }
            else
            {
                cur->next = (t_heredoc *)malloc(sizeof(t_heredoc));
                if (!cur->next)
                    return (NULL);
                                temp_path = ft_gen_here_path();
                if (open(temp_path, O_CREAT | O_RDWR | O_TRUNC, 0644) < 0)
                    return (NULL);
                heredoc->path = temp_path;
            }
            printf("[DEBUG][GEN_HERE_PATH]: %s\n", heredoc->path);
    }
    return (heredoc);
}