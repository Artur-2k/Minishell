/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/09 17:16:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char g_signal;

void     ft_replace_token(char **token_to_swap, int i, char *path)
{
    free(token_to_swap[i]);
    token_to_swap[i] = path;
}

char     *ft_hered_del(char *tkn, int *i)
{
    char *str;
    int  j;
    char quote_char;

    j = 0;
    str = NULL;
    quote_char = 0;
    if (tkn[j] == '\'' || tkn[j] == '\"')
    {
        quote_char = tkn[j];
        j++;
        *i = 1;
        while(tkn[j] && tkn[j] != quote_char)
        {
            str = ft_append_char_to_str(str, tkn[j]);
            j++;
        }
    }
    else
    {
        while(tkn[j])
            str = ft_append_char_to_str(str, tkn[j++]);
    }
    return (str);
}

static void    ft_heredoc_sigint(int signo)
{
    g_signal = signo;
    rl_on_new_line();
    rl_replace_line("", 0);
    ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static int	ft_heredoc_io(t_heredoc *hered_data, t_shell *shell)
{
    hered_data->input = readline(RED"> "RES);
    if (g_signal == SIGINT)
    {
        shell->heredoc_ignore = 1;
        return (-1);
    }
    if (hered_data->input == NULL)
        return (-2);
    if (ft_strcmp(hered_data->input, hered_data->delimiter) == 0)
        return (-3);
    if (hered_data->expand == 0)
        hered_data->input = ft_heredoc_expand(hered_data->input, shell);
    hered_data->input = ft_append_char_to_str(hered_data->input, '\n');
    ft_putstr_fd(hered_data->input, hered_data->fd);
    free(hered_data->input);
    return (0);
}

int     ft_heredoc_logic(char **token_arr, int i, t_shell *shell)
{
    t_heredoc	hered_data;

    hered_data.expand = 0;
    hered_data.delimiter = ft_hered_del(token_arr[i + 1], &hered_data.expand);
    hered_data.dyn_path = ft_gen_here_path(shell->pid);
    ft_replace_token(token_arr, i + 1, hered_data.dyn_path);
    hered_data.fd = open(hered_data.dyn_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (hered_data.fd == -1)
        return (ft_putstr_fd("Error creating fd, sir\n", 2), -1);
    if (shell->heredoc_ignore == 0)
    {
        while(1)
        {
            if (ft_heredoc_io(&hered_data, shell))
                break ;
        }
    }
    free(hered_data.delimiter);
    close(hered_data.fd);
    return (0);
}

void    ft_init_hered_signals(void)
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

    sa_int.sa_handler = ft_heredoc_sigint;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int     ft_heredoc_process(char **token_arr, t_shell *shell)
{
    int i;

	shell->heredoc_ignore = 0;
    g_signal = 0;
    i = 0;
    while (token_arr[i])
    {
        if (ft_strcmp(token_arr[i], "<<") == 0)
        {
            ft_init_hered_signals();
            ft_heredoc_logic(token_arr, i, shell);
        }
        i++;
    }
    if (g_signal)
    {
        shell->exit_status = 128 + g_signal;
        free(shell->sexit_status);
        shell->sexit_status = ft_itoa(shell->exit_status);
    }
    ft_init_signals();
    if (shell->heredoc_ignore == 1)
        return (shell->heredoc_ignore = 0, -1);
    return (0);
}

