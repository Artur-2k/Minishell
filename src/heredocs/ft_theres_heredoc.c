/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_theres_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:21:05 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/21 13:30:27 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Generate a pathname to each heredoc to fill the t_heredoc
 * @param Void
 * @return (String) Pathname
*/
char	*ft_gen_here_path(void)
{
	static int	index;
	char		*index_itoa;
	char		*result;

	result = NULL;
	index_itoa = ft_itoa(index);
	result = ft_strjoin("/tmp/here_doc_v", index_itoa);
	index++;
	free(index_itoa);
	return (result);
}
