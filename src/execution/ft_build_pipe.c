#include "minishell.h"

t_cmd   *ft_build_pipe(t_cmd *cmd, t_tokens **tkns ,t_shell *shell)
{
    t_pipe  *pipe;

    pipe = (t_pipe *)malloc(sizeof(t_pipe));
    if (!pipe) // Malloc error
        return (NULL);
    pipe->type = PIPE;
    pipe->left = cmd;
    pipe->right = ft_build(tkns, shell);
    if (pipe->right)
    {
        return (free(pipe), NULL);
    }
    return ((t_cmd *)pipe);
}
