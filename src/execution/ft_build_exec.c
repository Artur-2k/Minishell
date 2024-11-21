/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:15:54 by artuda-s          #+#    #+#             */
/*   Updated: 2024/11/21 16:45:33 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Creates a char **envp to send to exec with the same contents as
 * the envp list
 * @return Returns the char **envp or NULL for malloc errors
*/
static char	**ft_recreate_envp(t_envp *l_envp)
{
	char	**envp;
	t_envp	*backup;
	int		len;

	if (!l_envp)
		return (NULL);
	backup = l_envp;
	len = 0;
	while (l_envp && ++len)
		l_envp = l_envp->next;
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	l_envp = backup;
	len = 0;
	while (l_envp)
	{
		envp[len] = ft_strappend(ft_strjoin(l_envp->key, "="), l_envp->value);
		if (!envp[len])
			return (ft_free_str_arr(envp), NULL);
		len++;
		l_envp = l_envp->next;
	}
	envp[len] = NULL;
	return (envp);
}

/*
 * @brief Counts the lenght in tokens of the current command.
 * Skips while the token type isnt exec and stops at the end of the
 * token list or when a pipe is found
*/
static int	ft_cmd_len(t_tokens **tkns)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (tkns[i])
	{
		if (tkns[i]->type == PIPE)
			break ;
		if (tkns[i]->token && tkns[i]->type == EXEC)
			len++;
		i++;
	}
	return (len);
}

/*
 * @brief Allocates memory for a new redir node and fills it up
 * and adds it to the end of the list
 * @param *cmd A pointer to the command so we can add it to the end of
 * it's redir list
 * @param tkns Token list
 * return Returns 0 on success and a non-zero value on malloc errors
*/
static int	ft_new_redir(t_exec *cmd, t_tokens **tkns)
{
	t_redir	*new;
	t_redir	*cur;

	new = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (1);
	if (!ft_strcmp(tkns[0]->token, "<"))
		new->type = INREDIR;
	else if (!ft_strcmp(tkns[0]->token, "<<"))
		new->type = HDREDIR;
	else if (!ft_strcmp(tkns[0]->token, ">"))
		new->type = OUTREDIR;
	else
		new->type = APPREDIR;
	new->redir = ft_strdup(tkns[1]->token);
	if (cmd->redir_list == NULL)
		cmd->redir_list = new;
	else
	{
		cur = cmd->redir_list;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	return (0);
}

static int	ft_norminete(t_tokens ***tkns, t_exec *cmd, \
	int *i)
{
	int	j;

	j = 0;
	while ((*tkns)[*i] && (*tkns)[*i]->type != PIPE)
	{
		if ((*tkns)[*i]->token == NULL)
			i++;
		else if ((*tkns)[*i]->type != EXEC)
		{
			if (ft_new_redir(cmd, &(*tkns)[*i]))
				return (ft_free_str_arr(cmd->av), free(cmd), 1);
			(*i) += 2;
		}
		else
		{
			cmd->av[j] = ft_strdup((*tkns)[*i]->token);
			if (!cmd->av[j])
				return (ft_free_str_arr(cmd->av), \
				ft_free_redir_list(&cmd->redir_list), free(cmd), 2);
			j++;
			(*i)++;
		}
	}
	cmd->av[j] = NULL;
	return (0);
}

/*
* @brief allocates memory for a exec node and for it's content 
* (argv and redirection
* list) and fills them. Ignores NULL tokens but not empty tokens!
* @param tkns Token list
* @param shell Root struct
* @return An exec node typecasted into cmd node or NULL for malloc errors
*/
t_cmd	*ft_build_exec(t_tokens ***tkns, t_shell *shell)
{
	t_exec	*cmd;
	int		i;

	cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	cmd->av = (char **)ft_calloc((ft_cmd_len(*tkns) + 1), sizeof(char *));
	if (!cmd->av)
		return (free(cmd), NULL);
	i = 0;
	if (ft_norminete(tkns, cmd, &i))
		return (NULL);
	cmd->shell = shell;
	cmd->envp = shell->my_envp_h;
	if (shell->my_envp_h)
		cmd->tenvp = ft_recreate_envp(shell->my_envp_h);
	(*tkns) += i;
	return ((t_cmd *)cmd);
}
