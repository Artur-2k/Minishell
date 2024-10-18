/* /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:30 by artuda-s          #+#    #+#             */
/*   Updated: 2024/10/18 09:51:09 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * REDIRECTIONS 
 *  primeiro heardocs. depois outros redirs. 
 *  > file1 > file2 abre file1 e file2 se nao existir e escreve apenas no ultimo
 * 
 * typedef struct   s_command
 *  {
 *      char    **cmd_arr;
 *      char    *in_redir;
 *      char    *out_redir;
 *      bool    append;
 *      bool    piping;
 *  }   t_command;
 * 
*/


int ft_get_cmd_len(char **tkn_arr, int i)
{
    int len;
    
    len = 0;
    // cat < file1 | teste arg2 > file2
    while (tkn_arr[i])
    {
        if (tkn_arr[i][0] == '|')
            break ;
        if (!ft_strchr("<>", tkn_arr[i][0]))
            len++;
        i++;
    }
        
    return (len);
}

// Allocates memory for a new command node and inits it
// Returns the new command
// Returns NULL in case of malloc error
t_command    *ft_new_cmd(t_shell *shell, char **tkn_arr, int i)
{
    t_command   *ncmd;
    t_command   *curr;
       
    ncmd = (t_command *)malloc(sizeof(t_command));
    if (!ncmd)
        return (NULL);
    ncmd->cmd_arr = (char **)ft_calloc(ft_get_cmd_len(tkn_arr, i) + 1, sizeof(char *));
    if (!ncmd->cmd_arr)
        return (NULL);
    ncmd->in_redir = NULL;
    ncmd->out_redir = NULL;
    ncmd->append = false;
    ncmd->piping = false;
    ncmd->next = NULL;
    if (!shell->cmd_list)
        shell->cmd_list = ncmd;
    else
    {
        curr = shell->cmd_list;
        while (curr->next)
            curr = curr->next;
        curr->next = ncmd;
    }
    return (ncmd);
}



int ft_create_commands(char **tkn_arr, t_shell *shell)
{
    int         i;
    t_command   *cur;
    int         in_fd;
    int         pipe_fd[2];

    i = 0;
    shell->cmd_list = NULL;
    cur = ft_new_cmd(shell, tkn_arr, i);
    // cat < file1 | teste arg2 > file2
    in_fd = 0;
    while (tkn_arr[i])
    {
        if (!ft_strcmp(tkn_arr[i], "<<")){} // heredoc
        else if (!ft_strcmp(tkn_arr[i], "<")) // input redirect
        {
            // < file1     file1 not arg
            i++;
            if (cur->in_redir)
                free(cur->in_redir);
            cur->in_redir = ft_strdup(tkn_arr[i]);
        }
        else if (!ft_strcmp(tkn_arr[i], ">>")) // output redirect + append
        {
            // > file1     file1 not arg
            i++;
            if (cur->out_redir)
                free(cur->out_redir);
            cur->out_redir = ft_strdup(tkn_arr[i]);
            cur->append = true;
            int fd = open(cur->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            close(fd);
        }
        else if (!ft_strcmp(tkn_arr[i], ">")) // output redirect
        {
            // > file1     file1 not arg
            i++;
            if (cur->out_redir)
                free(cur->out_redir);
            cur->out_redir = ft_strdup(tkn_arr[i]);
            int fd = open(cur->out_redir, O_WRONLY | O_CREAT, 0644);
            close(fd);
        }
        else if (!ft_strcmp(tkn_arr[i], "|")) // pipe and add cmd
        {
            i++;
            cur = ft_new_cmd(shell, tkn_arr, i);
            if (pipe(pipe_fd))
                return (-1);
            pid_t pid = fork();
            if (pid == 0)
            {
                dup2(in_fd, STDIN_FILENO);
                dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
                close(pipe_fd[READ_END]);
                for (int z = 0; cur->cmd_arr[z]; z++)
                {
                    printf("ola: ");                ;
                    printf("%s\n", cur->cmd_arr[z]);
               }
                execvp(cur->cmd_arr[0], cur->cmd_arr);
                perror("Erro ao executar comando\n");
            }
            close(pipe_fd[WRITE_END]);
            in_fd = pipe_fd[READ_END];
        }
        else // add to cmd_arr
        {
            int j = 0;
            while (cur->cmd_arr[j] != NULL)
                j++;
            cur->cmd_arr[j] = ft_strdup(tkn_arr[i]);     
        }
        i++;
    }     

    // Executar o último comando, se houver
    int pid = fork();
    if (pid == 0) {
        dup2(in_fd, STDIN_FILENO);  // Redirecionar a entrada do último pipe
        close(in_fd);
        // Se houver redirecionamento de saída, configurar
        if (cur->out_redir) {
            int fd;
            if (cur->append)
                fd = open(cur->out_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd = open(cur->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Erro ao abrir o arquivo de saída");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);  // Redirecionar saída para o arquivo
            close(fd);
        }
        execvp(cur->cmd_arr[0], cur->cmd_arr);
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
    }

    close(in_fd);  // Fechar o último pipe
    // Esperar por todos os processos filhos
    while (wait(NULL) > 0);

    exit (0); // success
}
