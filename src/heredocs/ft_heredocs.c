/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/12/02 18:39:56 by dmelo-ca         ###   ########.fr       */
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

    close(STDIN_FILENO);
    printf("\n");
    // Notifica o Readline que uma nova linha será iniciada
    /* rl_on_new_line(); */
    // Substitui o conteúdo da linha atual por uma linha em branco
    rl_replace_line("", 0);
    // Redesenha o prompt limpo após o sinal
    rl_redisplay();
}

void restore_stdin(int temp_fd) {
    if (temp_fd != -1) {
        dup2(temp_fd, STDIN_FILENO);
        close(temp_fd);
        temp_fd = -1;
    }
}

int     ft_heredoc_logic(char **token_arr, int i, t_shell *shell)
{
    char *delimiter;
    char *input;
    int  fd;
    char *dyn_path;
    int  expand;
    
    expand = 0;
    delimiter = ft_hered_del(token_arr[i + 1], &expand);
    /* printf("[DELIMITER]: %s\n", delimiter); */
    dyn_path = ft_gen_here_path(shell->pid);
    ft_replace_token(token_arr, i + 1, dyn_path);
    fd = open(dyn_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1)
        printf("ERRO AO CRIAR FD\n");
    else if (shell->heredoc_ignore == 0)
    {
        while(1)
        {
            input = readline(RED"> "RES);
			if (g_signal == SIGINT)
			{
				g_signal = 0;
				shell->heredoc_ignore = 1;
                break ;
				/* printf("SIGINT DETECTADO!\n"); */
			}
            if (input == NULL)
                break;
            if (ft_strcmp(input, delimiter) == 0)
                break;
            if (expand == 0)
                input = ft_heredoc_expand(input, shell);
            input = ft_append_char_to_str(input, '\n');
            ft_putstr_fd(input, fd);
            free(input);
        }
        free(delimiter);
        close(fd);
    }
	else
		free(delimiter);
    return (0);
}

void    ft_init_hered_signals(void)
{
    struct sigaction    sa_int;
    struct sigaction    sa_quit;

    // Sigint
    sa_int.sa_handler = ft_heredoc_sigint;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    // Sigquit
    sa_quit.sa_handler = SIG_IGN;
    sa_quit.sa_flags = 0;
    sigemptyset(&sa_quit.sa_mask);
    sigaction(SIGQUIT, &sa_quit, NULL);
}

int     ft_heredoc_process(char **token_arr, t_shell *shell)
{
    int temp_fd;

    temp_fd = dup(STDIN_FILENO);
	shell->heredoc_ignore = 0;
    g_signal = 0;
    for(int i = 0; token_arr[i] != NULL; i++)
    {    
        if (ft_strcmp(token_arr[i], "<<") == 0)
        {
            /* printf("HEREDOC DETECTADO!!\n"); */
            ft_init_hered_signals();
            ft_heredoc_logic(token_arr, i, shell); //SE ENCONTRA HEREDOC EXECUTA FUNCAO RESPECTIVA A ELE
        }
        /* printf("[%d][TOKEN_ARR]: %s\n", i, token_arr[i]); */
    }
    restore_stdin(temp_fd);
    ft_signal_restore();
    ft_init_signals();
    if (shell->heredoc_ignore == 1)
    {
        shell->heredoc_ignore = 0;
        return (-1);
    }
    return (0);
}

