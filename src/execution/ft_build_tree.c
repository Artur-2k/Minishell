/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:12 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/31 15:59:43 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
 * @brief First node will always be an exec node and only if there
 * is a pipe we then create a pipe node and give to the left the left
 * cmd and to the right whatever is after the pipe
 * @param tokens Tokens for convinience lol 
 * @param shell Root struct that has everything we need
 * @return Returns the generic command with the appropriate type
*/
t_cmd   *ft_build(t_tokens **tokens, t_shell *shell)
{
    t_cmd  *cmd;
    t_cmd  *tmp;

    cmd = ft_build_exec(&tokens, shell);
    if (!cmd) // Malloc error
        return (NULL);
    if (*tokens && (*tokens)->type == PIPE)
    {
        tokens++;
        tmp = cmd;
        cmd = ft_build_pipe((t_cmd *)cmd, tokens, shell);
        if (!cmd)
            return (ft_free_tree(tmp), NULL);
    }
    return (cmd);
}
