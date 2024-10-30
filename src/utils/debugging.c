#include "minishell.h"

void	print_tree(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		t_exec	*exec = (t_exec *)cmd;
		//* AV
		printf("\nExec Node:\n");
		printf("av &:[ %p ]\n", &exec->av);
		int i = 0;
		while (exec->av[i])
		{
			printf("AV[%i]: [%s]\n", i , exec->av[i]);
			i++;
		}
		printf("AV[%i]: [%s]\n", i , exec->av[i]);

		// redir list
		t_redir *curr = exec->redir_list;
		printf("REDIRES:\n");
		while (curr != NULL)
		{
			// type de redir
				printf("TYPE: [%i]\t", curr->type);
			// redir
				printf("FILE: [%s]\n", curr->redir);
			curr = curr->next;
		}
	}
	else if (cmd->type == PIPE)
	{
		t_pipe *pipe = (t_pipe *)cmd;
		// chamar para printar esquerdo
		print_tree((t_cmd *)pipe->left);

		printf(GRN"\nPIPALHAO HEHE\n"RES);
		// chamar para a direita
		print_tree((t_cmd *)pipe->right);
	}
}