/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/20 12:52:07 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HERED_ABS_PATH "here_doc_v0"

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
    dyn_path = ft_gen_here_path();
    ft_replace_token(token_arr, i + 1, dyn_path);
    fd = open(dyn_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1)
        printf("ERRO AO CRIAR FD\n");
    else
    {
        while(1)
        {
            input = readline(RED"> "RES);
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
    return (0);
}

int     ft_heredoc_process(char **token_arr, t_shell *shell)
{
    for(int i = 0; token_arr[i] != NULL; i++)
    {    
        if (ft_strcmp(token_arr[i], "<<") == 0)
        {
            /* printf("HEREDOC DETECTADO!!\n"); */
            ft_heredoc_logic(token_arr, i, shell); //SE ENCONTRA HEREDOC EXECUTA FUNCAO RESPECTIVA A ELE
        }
        /* printf("[%d][TOKEN_ARR]: %s\n", i, token_arr[i]); */
    }
    return (0);
}

