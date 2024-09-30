#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

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

