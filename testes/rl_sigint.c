#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void    ft_handle_sigint(int signo)
{
    // Notifica o Readline que uma nova linha será iniciada
    rl_on_new_line();
    // Substitui o conteúdo da linha atual por uma linha em branco
    rl_replace_line("", 0);
    // Redesenha o prompt limpo após o sinal
    rl_redisplay();
}

int main() {
    char *input;
    struct sigaction sa;

    sa.sa_handler = ft_handle_sigint; // void handler(int signo);
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL); // TODO ver sigaction

    // Loop que lê várias linhas de entrada
    while (1) {
        input = readline("Digite algo: ");  // Exibe o prompt e aguarda a entrada

        if (input == NULL) {
            // Se o usuário digitar Ctrl+D (EOF), readline retorna NULL
            printf("\nEOF detectado. Saindo...\n");
            break;
        }

        // Verifica se o input não está vazio antes de adicionar ao histórico
        if (*input != '\0') {
            add_history(input);  // Adiciona a linha ao histórico
        }

        printf("Você digitou: %s\n", input);

        free(input);  // Libera a memória alocada por readline
    }

    return 0;
}

