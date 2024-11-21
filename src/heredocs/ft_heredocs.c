/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/21 13:27:46 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_token(char **token_to_swap, int i, char *path)
{
	free(token_to_swap[i]);
	token_to_swap[i] = path;
}

char	*ft_hered_del(char *tkn, int *i)
{
	char	*str;
	int		j;
	char	quote_char;

	j = 0;
	str = NULL;
	quote_char = 0;
	if (tkn[j] == '\'' || tkn[j] == '\"')
	{
		quote_char = tkn[j];
		j++;
		*i = 1;
		while (tkn[j] && tkn[j] != quote_char)
		{
			str = ft_append_char_to_str(str, tkn[j]);
			j++;
		}
	}
	else
	{
		while (tkn[j])
			str = ft_append_char_to_str(str, tkn[j++]);
	}
	return (str);
}

int	ft_heredoc_io(t_heredoc *data, t_shell *shell)
{
	data->input = readline(RED"> "RES);
	if (data->input == NULL)
		return (-1);
	if (ft_strcmp(data->input, data->delimiter) == 0)
		return (-1);
	if (data->expand == 0)
		data->input = ft_heredoc_expand(data->input, shell);
	data->input = ft_append_char_to_str(data->input, '\n');
	ft_putstr_fd(data->input, data->fd);
	free(data->input);
	return (0);
}

int	ft_heredoc_logic(char **token_arr, int i, t_shell *shell)
{
	t_heredoc	hered_data;

	hered_data.expand = 0;
	hered_data.delimiter = ft_hered_del(token_arr[i + 1], &hered_data.expand);
	hered_data.dyn_path = ft_gen_here_path();
	ft_replace_token(token_arr, i + 1, hered_data.dyn_path);
	hered_data.fd = open(hered_data.dyn_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	hered_data.input = NULL;
	if (hered_data.fd == -1)
		printf("ERRO AO CRIAR FD\n");
	else
	{
		while (1)
		{
			if (ft_heredoc_io(&hered_data, shell) < 0)
				break ;
		}
		free(hered_data.delimiter);
		close(hered_data.fd);
	}
	return (0);
}

int	ft_heredoc_process(char **token_arr, t_shell *shell)
{
	int	i;

	i = 0;
	while (token_arr[i] != NULL)
	{
		if (ft_strcmp(token_arr[i], "<<") == 0)
			ft_heredoc_logic(token_arr, i, shell);
		i++;
	}
	return (0);
}
