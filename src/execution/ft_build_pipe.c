/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:19:00 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 15:47:52 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Allocates memory for a new pipe node and sets the exec cmd to the left
 * and to the right recursivly calls the build
 * functio with a pointer to the tokens
 * that are missing to append to the tree
 * @return Returns the right side of the pipe or NULL in case of error
*/
t_cmd	*ft_build_pipe(t_cmd *cmd, t_tokens **tkns ,t_shell *shell)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->type = PIPE;
	pipe->left = cmd;
	pipe->right = ft_build(tkns, shell);
	if (!pipe->right)
		return (free(pipe), NULL);
	return ((t_cmd *)pipe);
}
