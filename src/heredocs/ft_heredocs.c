/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:22:19 by dmelo-ca          #+#    #+#             */
/*   Updated: 2024/11/13 18:15:20 by dmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TEMP_DIR ".temp"

int     ft_heredoc_logic(char **token_arr, int i, t_shell *shell)
{
    char *delimiter;
    char *input;
    int  fd;
    
    delimiter = token_arr[i + 1];
    fd = open(TEMP_DIR".txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
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

