/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/15 17:32:58 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define HERED_ABS_PATH "here_doc_v0"

void     ft_replace_token(char **token_to_swap, int i, char *path)
{
    /* free(token_to_swap[i]); */
    token_to_swap[i] = path;
}

int     ft_heredoc_logic(char **token_arr, int i, t_shell *shell)
{
    char *delimiter;
    char *input;
    int  fd;
    char *dyn_path;
    
    delimiter = token_arr[i + 1];
    dyn_path = ft_gen_here_path();
    //TODO SUBSTITUIR TOKEN POR PATH
    ft_replace_token(token_arr, i + 1, dyn_path);
    //TODO LOGICA DE CRIAR OU ACESSAR MESMOS PATHS CRIADO NOS REDIRS
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
            
            input = ft_expand_token(input, shell);
            input = ft_append_char_to_str(input, '\n');

            ft_putstr_fd(input, fd);
            free(input);
        }
        /* printf("DELIMITADOR %s\n", delimiter); */
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

