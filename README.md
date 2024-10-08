# readline(), add_history() e rl_clear_history()

```
#include <readline/readline.h>
#include <readline/history.h>
```
                     
A função `readline()` é usada para ler uma linha de texto do terminal de forma interativa, permitindo ao usuário editar a linha, mover o cursor, e navegar no histórico de comandos.
Mostra um prompt (texto que aparece antes da linha de entrada) e aguarda o usuário digitar algo.
Retorna um ponteiro para a string digitada ou NULL se o usuário pressionar Ctrl+D (EOF).

Assinatura: `char *readline(const char *prompt);`

Assinatura: `void add_history(const char *line);`

Assinatura: `void rl_clear_history(void);`

### Principais recursos:

Edição de linha: Permite corrigir a entrada antes de pressionar "Enter".
Histórico de comandos: Permite armazenar e recuperar entradas anteriores usando funções como add_history().
Autocompletar: Pode ser configurada para sugerir ou completar automaticamente palavras.

__Compilação: Ao compilar, é necessário linkar a biblioteca com -lreadline.__
Para adicionar um input ao historico usamos a add_history e podemos navegar pelo historico atraves das setas

`add_history(string)` `string` seria a string a ser gravada no historico

`rl_clear_history()` limpa todos os itens do histórico que foram adicionados por chamadas a add_history().
Se o histórico for salvo em um arquivo usando write_history(), isso não afetará o histórico já salvo no arquivo, apenas o histórico em memória será limpo.


# Estrutura struct termios

`#include <termios.h>`

A `struct termios` contém as configurações do terminal. Cada campo dessa estrutura controla uma parte do comportamento do terminal, e você pode manipulá-los para modificar como o terminal lida com entradas e saídas.

Assinatura: `struct termios termios_p;`

### Estrutura termios:
 - `c_lflag` (Local modes): Controla as opções de modo local, como se o terminal deve ecoar os caracteres digitados e como os sinais são tratados (por exemplo, Ctrl+C).
 - `c_iflag` (Input modes): Controla as opções de modo de entrada, como se o terminal deve processar caracteres de controle.
 - `c_oflag` (Output modes): Controla as opções de modo de saída, como se o terminal deve processar os caracteres de controle de nova linha.
 - `c_cflag` (Control modes): Controla as opções de modo de controle, como a velocidade da comunicação serial.
 - `c_cc[]` (Control characters): Um array de caracteres de controle, como o caractere que representa a tecla de "fim de arquivo" (EOF) ou "apagar" (DEL).

__c_lflag (Local Mode Flags)__
`ECHOCTL`: Se essa flag estiver definida, os caracteres de controle (como Ctrl+C, Ctrl+D) são exibidos no terminal na forma de ^C, ^D, etc. 
Quando removemos essa flag (usando `&= ~ECHOCTL`  => **BITWISE** HELLO XD), esses caracteres de controle não são mais exibidos no terminal.

# Funções tcgetattr e tcsetattr

`#include <termios.h>`

## tcsetattr()

Esta função `tcsetattr()` lê as configurações atuais do terminal e armazena-as na estrutura termios apontada por termios_p.
Essa função retorna 0 em caso de sucesso e -1 em caso de falha.

Assinatura: `tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`

### Parametros:
- fd: O descritor de arquivo que representa o terminal. Para manipular a entrada padrão (teclado), usamos STDIN_FILENO (definido como 0), que é o descritor para o terminal de entrada.
- termios_p: Um ponteiro para uma estrutura termios, onde as configurações atuais do terminal serão armazenadas.

## tcsetattr()

Esta função `tcsetattr()` aplica as configurações do terminal armazenadas na estrutura termios apontada por termios_p para o terminal indicado pelo descritor de arquivo fd.
Essa função também retorna 0 em caso de sucesso e -1 em caso de falha.

Assinatura: `tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`

### Parametros:
- fd: O descritor de arquivo do terminal (como STDIN_FILENO).
- optional_actions: Determina quando as mudanças nas configurações devem ser aplicadas. Algumas opções incluem:
    - TCSANOW: Aplica as mudanças imediatamente.
    - TCSADRAIN: Aplica as mudanças após esvaziar os buffers de saída.
    - TCSAFLUSH: Aplica as mudanças após esvaziar tanto os buffers de entrada quanto os de saída.
- termios_p: Ponteiro para a estrutura termios que contém as configurações que serão aplicadas.
    
### Exemplo de uso

```
struct termios termios_t;
tcgetattr(STDIN_FILENO, &termios_t);
termios_t.c_lflags &= ~ECHOCTL;
tcsetattr(STDIN_FILENO, TCSANOW, &termios_t);
```

# Fork()

`#include <unistd.h>`

### Comportamento do fork()
Copia o espaço de memória: O processo filho recebe uma cópia do espaço de memória do processo pai. Inicialmente, isso inclui todas as variáveis, pilha e heap. No entanto, o sistema usa uma técnica chamada copy-on-write (COW), onde a cópia real da memória só é feita se um dos processos (pai ou filho) tentar modificar a memória.
Execução paralela: Após a chamada para `fork()`, ambos os processos (pai e filho) continuam a ser executados. Não há garantias sobre a ordem em que eles serão executados, pois o escalonador do sistema operacional decide isso.
Process IDs diferentes: O processo filho tem um PID diferente do pai. O pai pode obter o PID do filho a partir do valor retornado por `fork()`, enquanto o filho pode obter o PID do pai usando `getppid()`.

Assinatura: `pid_t fork(void);`

### Retorno da função
- Retorno do processo pai: `fork()` retorna o PID (Process ID) do processo filho.
- Retorno do processo filho: `fork()` retorna 0 no processo filho.
- Erro: Se ocorrer um erro ao tentar criar o processo, `fork()` retorna -1 e define o valor da variável global errno para indicar o erro.

#### Exemplo de uso
```
int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Se fork() falhou
        printf("Erro ao criar processo filho\n");
    } else if (pid == 0) {
        // Código executado pelo processo filho
        printf("Processo filho: Meu PID é %d\n", getpid());
    } else {
        // Código executado pelo processo pai
        printf("Processo pai: Criei um filho com PID %d\n", pid);
    }
    return 0;
}
```

### _pid_t_ 

`#include <sys/types.h>`

É um tipo de dado definido em `<sys/types.h>` que representa o Process ID (PID), que é um identificador único atribuído a cada processo em execução no sistema.
Este tipo é usado principalmente em chamadas de sistema que lidam com processos, como `fork()`, `wait()`, `getpid()`, e `getppid()`.

# wait()  

`#include <sys/wait.h>`

Assinatura: `pid_t wait(int *status);`

A funcao `wait()` em C e usada para fazer com que um processo pai aguarde a finalizacao de um ou mais processos filhos.
Se houver algum processo filho que não tenha terminado a sua execução ele fica a aguardar.

### Parametros:
- status: E um ponteiro para um inteiro onde o status de termino do processo filho sera armazenado. Se nao estivermos interessados no status de saida podemos passar NULL. O statuss pode ser analizado com macros como: `WIFEXITED()`, `WEXITSTATUS()`, `WIFSIGNALED()` entre outras.

`WIFEXITED(status)`: Retorna verdadeiro se o processo filho terminou normalmente (ou seja, usou exit() ou retornou da main()).

`WEXITSTATUS(status)`: Retorna o código de saída do processo filho se ele terminou normalmente (o valor passado para exit()).

`WIFSIGNALED(status)`: Retorna verdadeiro se o processo filho foi encerrado por um sinal.

`WTERMSIG(status)`: Retorna o número do sinal que causou a finalização do processo filho.

`WIFSTOPPED(status)`: Retorna verdadeiro se o processo filho foi parado por um sinal (mas não terminado).

### Valores de retorno:
- Retorna o PID do processolho filho que terminou
- Retorna -1 em caso de erro

# waitpid()
`#include <sys/wait.h>`

Pode especificar o PID de um processo específico para esperar, ou outras opções como -1 (esperar por qualquer filho).
options: Pode incluir opções como WNOHANG (não espera, retorna imediatamente se nenhum filho tiver terminado) e WUNTRACED (retorna se um processo filho tiver sido parado, mas não terminado).

Assinatura: `pid_t waitpid(pid_t pid, int *status, int options);`

### Parâmetros
- pid: Especifica qual processo filho esperar. Existem alguns valores especiais que você pode usar:
     - pid > 0: Espera pelo processo filho cujo PID é exatamente igual a pid.
     - pid == 0: Espera por qualquer processo filho que esteja no mesmo grupo de processos que o chamador.
     - pid < -1: Espera por qualquer processo filho cujo grupo de processos seja igual a -pid.
     - pid == -1: Comportamento padrão de wait(), ou seja, espera por qualquer processo filho.
- status: Um ponteiro para um inteiro onde o status de término do processo será armazenado. O valor pode ser verificado usando macros como:
     - WIFEXITED(status): Retorna true se o processo filho terminou normalmente (via exit ou _exit).
     - WEXITSTATUS(status): Retorna o código de saída do filho se WIFEXITED for verdadeiro.
     - WIFSIGNALED(status): Retorna true se o filho foi encerrado por um sinal.
     - WTERMSIG(status): Retorna o número do sinal que encerrou o filho, se WIFSIGNALED for verdadeiro.
     - WIFSTOPPED(status): Retorna true se o processo filho foi interrompido por um sinal (SIGSTOP ou similar).
     - WSTOPSIG(status): Retorna o número do sinal que parou o processo, se WIFSTOPPED for verdadeiro.
- options: Permite especificar opções adicionais. Algumas opções comuns são:
     - WNOHANG: Faz com que waitpid() não bloqueie se nenhum filho tiver terminado ainda. Se nenhum processo filho terminou, a função retorna imediatamente com 0.
     - WUNTRACED: Faz com que waitpid() retorne se um processo filho foi parado, mas não terminado (por exemplo, após um sinal SIGSTOP).
     - WCONTINUED: Faz com que waitpid() retorne se um processo filho que estava parado foi reiniciado (após um SIGCONT).


### Principais opções:
`WNOHANG`: Esta opção faz com que waitpid() não bloqueie se o filho ainda não tiver terminado. Em vez disso, ele retorna imediatamente e você pode continuar executando outras tarefas.
`WUNTRACED`: Faz com que waitpid() retorne também se um filho for parado (não apenas terminado) por um sinal (como um Ctrl + Z no terminal). Normalmente, waitpid() só retornaria se o processo filho terminasse de fato, mas com WUNTRACED, você é notificado mesmo que o filho apenas suspenda (não termine).
   Útil para detectar quando um filho é temporariamente interrompido e está apenas em estado "parado".
   
 `WCONTINUED`: Retorna se um filho que estava parado (suspendido) é continuado (retoma a execução) após receber o sinal SIGCONT.
   Essa opção permite que você monitore quando um processo filho que foi interrompido (exemplo: Ctrl + Z) volta a rodar depois de ser "despausado".
   
 `WEXITED`: Com waitid() (outra função relacionada), essa opção espera apenas processos que terminaram normalmente. É como WIFEXITED() no waitpid(), mas você passa como opção.
   
 `WSTOPPED`: Similar a WUNTRACED, mas usado com waitid(). Faz com que waitid() retorne informações sobre processos que foram parados por sinais como SIGSTOP.
   
 `WNOWAIT`: Se usado com waitid(), não remove o status de término do processo filho quando ele termina, ou seja, deixa o status "pendente". Isso permite que você consulte o status de término várias vezes sem "limpar" a informação.
   
 `__WALL`: Retorna o status de todos os processos filhos, mesmo que estejam em grupos de processos diferentes. Normalmente, waitpid() só retorna informações sobre filhos do mesmo grupo.
   Não é muito usado, mas pode ser útil em contextos específicos.
   
  `__WCLONE`: Monitora apenas processos que não compartilham o mesmo grupo de processos. Essa é uma opção avançada para contextos que envolvem threads e processos criados com clone().

### Como usar essas opções?
   
Essas opções são passadas como um argumento adicional na chamada à função waitpid(). Elas podem ser combinadas usando o operador bitwise OR (|) para que você use mais de uma opção ao mesmo tempo. Por exemplo:

`waitpid(pid, &status, WNOHANG | WUNTRACED);`

### Retorno
- Retorna o PID do processo filho que mudou de estado (terminou, foi interrompido, ou continuou).
- Retorna 0 se a opção `WNOHANG` foi usada e nenhum processo filho mudou de estado.
- Retorna -1 se ocorrer um erro (por exemplo, se o processo filho não existir ou não houver processos filhos). A variável global errno é configurada para indicar o erro.

*wait3, wait4 sao funcoes parecidas com a wait e waitpid mas que permitem recolher mais dados dos processos filhos terminados atraves de uma estrutura (struct rusage) // not necessary for minishell id say*

# Processos Zumbis
Um **processo zumbi** é um processo que já foi terminado, mas ainda tem uma entrada na tabela de processos. Isso ocorre porque o processo pai ainda não chamou wait() para recuperar o estado de saída do filho.
Os processos zumbis estão em um estado de "terminado" (exited), mas ainda ocupam uma entrada na tabela de processos do sistema, pois o sistema precisa manter informações sobre o processo terminado até que o pai as recupere.
Um processo se torna zumbi quando o processo filho termina sua execução ou se o processo pai não chama wait() para obter o status de saída do filho.
O processo zumbi é removido da tabela de processos quando o pai chama wait() e recupera o status de saída do filho.

# Processos Órfãos
Um **processo órfão** é um processo cujo processo pai terminou antes dele. Em outras palavras, o processo órfão ainda está em execução, mas não tem um pai vivo.
Os processos órfãos são processos que estão em execução, mas não têm um pai ativo. Quando um processo pai termina, o sistema operacional adota automaticamente seus filhos, tornando-os órfãos.
Um processo se torna órfão quando o processo pai termina sua execução ou um ou mais de seus filhos continuam a ser executados.
O sistema operacional adota processos órfãos, geralmente atribuindo o processo init (PID 1) como seu novo pai. O processo init é responsável por gerenciar todos os processos órfãos e garantir que eles sejam limpos adequadamente.

Se muitos processos zumbis acumularem, podem levar ao esgotamento da tabela de processos, impedindo que novos processos sejam criados
O gerenciamento automático de processos órfãos pelo sistema operacional evita que esses processos fiquem perdidos e sem controle, garantindo que continuem a ser monitorados e finalizados adequadamente.


# access()

`#include <unistd.h>`

A função `access()` é usada em C para verificar os permissões de acesso a arquivos ou diretórios. Ela permite que o programa teste se um arquivo ou diretório pode ser lido, gravado ou executado, sem tentar abrir o arquivo diretamente.

Assinatura: `int access(const char *pathname, int mode);`

### Parâmetros:
- pathname: O caminho do arquivo ou diretório que você deseja testar.
- mode: Especifica o tipo de verificação de permissão que você deseja realizar. Esse parâmetro pode ser uma combinação de vários valores (com operadores lógicos OR), entre eles:
    - F_OK: Verifica se o arquivo ou diretório existe.
    - R_OK: Verifica se o arquivo pode ser lido.
    - W_OK: Verifica se o arquivo pode ser gravado.
    - X_OK: Verifica se o arquivo pode ser executado (aplicável a arquivos executáveis).
### Retorno:
- 0: Se o arquivo ou diretório tem as permissões solicitadas.
- -1: Se o arquivo ou diretório não tem as permissões solicitadas, ou se ocorreu um erro. Nesse caso, errno é configurado para indicar o erro específico.

Podemos usar diretamente o modo X_OK ja que ele verifica tambem o mesmo que F_OK

### Variáveis de ambiente
As variáveis de ambiente são pares chave-valor que armazenam informações sobre o ambiente do sistema, como o diretório atual, o shell, o caminho de busca de comandos (PATH), entre outras configurações do sistema. Elas são usadas por programas para obter informações sobre o ambiente em que estão sendo executados.
São acessíveis para todos os processos e são herdadas por processos filhos. Por exemplo, um programa pode verificar a variável HOME para saber o diretório home do usuário ou PATH para localizar executáveis.
Em C, você pode manipular variáveis de ambiente através de várias funções e também acessá-las diretamente no vetor envp[], passado para a função main().

// vais ter de recriar uma get e setenv porque o setenv nao e allowed
# getenv()

`#include <stdlib.h>`

A função `getenv()` é usada para recuperar o valor de uma variável de ambiente.

Assinatura: `char *getenv(const char *name);`

### Parametros
- name: O nome da variável de ambiente que você deseja obter.
### Retorno:
- Retorna um ponteiro para o valor da variável de ambiente correspondente ou NULL se a variável não estiver definida.

### envp[]
O vetor `envp[]` (environment pointer) contém todas as variáveis de ambiente disponíveis no momento da execução do programa. Ele pode ser passado como o terceiro argumento da função main(). Se envp[] for passado, você pode iterar sobre ele para acessar todas as variáveis de ambiente.
int main(int argc, char *argv[], char *envp[]);
Podemos iterar pelos key=values com um loop normal e o formato e sempre KEY=value
PS: vais ter de copiar o envp para poder adicionar com um custom export que pede e para ler vais ter de criar um custom getenv ja que estamos agora a armazenar envp dinamicamente num array dinamico

### File descriptors
Descritores de arquivo (**fds**) são inteiros não negativos que representam aberturas de arquivos ou recursos manipuláveis em sistemas Unix/Linux. Eles permitem acesso uniforme a arquivos, sockets e pipes, e são obtidos através de chamadas de sistema como `open()`. Cada descritor deve ser fechado com close() após o uso para liberar os recursos associados.
- 0: stdin (entrada padrão).
- 1: stdout (saída padrão).
- 2: stderr (saída de erro padrão).
- 3: file.txt (aberta pelo open pe)

# open()

`#include <fcntl.h>`

A função `open()` é usada para abrir um arquivo e retornar um descritor de arquivo

Assinatura: `int open(const char *pathname, int flags, mode_t mode);`

### Parâmetros:
- pathname: O caminho do arquivo a ser aberto.
- flags: Um conjunto de opções que determina o modo como o arquivo será aberto. Alguns dos flags comuns incluem:
     - O_RDONLY: Abre o arquivo apenas para leitura.
     - O_WRONLY: Abre o arquivo apenas para escrita.
     - O_RDWR: Abre o arquivo para leitura e escrita.
     - O_CREAT: Cria o arquivo se ele não existir (normalmente usado em conjunto com O_WRONLY ou O_RDWR).
     - O_TRUNC: Se o arquivo já existir e estiver sendo aberto para escrita, seu conteúdo será truncado a zero.
     - O_APPEND: Escreve dados no final do arquivo.
- mode: Usado apenas se O_CREAT for especificado. Define as permissões do arquivo (ex: S_IRUSR | S_IWUSR, que dá permissão de leitura e escrita ao proprietário).
### Retorno:
- Retorna um descritor de arquivo (um inteiro) se a operação for bem-sucedida.
- Retorna -1 em caso de erro, e errno é configurado para indicar o erro.

# close()

`#include <unistd.h>`

A função `close()` é usada para fechar um descritor de arquivo que foi aberto anteriormente com `open()`. Isso libera os recursos associados ao descritor de arquivo.    

Assinatura: `int close(int fd);`

### Parametros:
- fd: O descritor de arquivo a ser fechado.
### Retorno:
- Retorna 0 se a operação for bem-sucedida.
- Retorna -1 em caso de erro, e errno é configurado para indicar o erro.

#### Exemplo de uso:
```
// o terceiro parametro so precisa de ser usado no caso de usarmos a flag O_CREATE
int fd = open(./teste.txt, W_RDONLY);
if (fd < 0)
    error_handle();
...
if (close(fd) < 0)
    error_handle();
```
# execve()

`#include <unistd.h>`

A função `execve()` é uma das chamadas de sistema em C usadas para executar um novo programa, substituindo o processo atual pelo novo programa especificado. É uma das várias funções exec disponíveis, e é considerada a forma mais básica e poderosa, pois permite passar os argumentos e variáveis de ambiente diretamente.

Assinatura: `int execve(const char *filename, char *const argv[], char *const envp[]);`

### Parametros:
- filename: O caminho para o arquivo executável que você deseja executar. Este arquivo deve ter permissões executáveis.
- argv: Um vetor de strings que contém os argumentos passados para o programa. O primeiro argumento (argv[0]) deve ser o nome do programa, seguido pelos argumentos reais. O vetor deve ser terminado por um ponteiro nulo (NULL)
- envp: Um vetor de strings que contém as variáveis de ambiente a serem passadas para o novo programa. Assim como argv, deve ser terminado por um ponteiro nulo (NULL).
### Retorno
- Em caso de sucesso, `execve()` não retorna; o processo atual é substituído pelo novo programa.
- Se ocorrer um erro, retorna -1 e errno é configurado para indicar o tipo de erro.

#### Exemplo de uso:
```
#include <stdio.h>
#include <unistd.h>

int main() 
{
    // Argumentos para o comando
    char *argv[] = { "ls", "-l", NULL };  
    char *envp[] = { NULL };
    // Executa o comando 'ls -l'
    if (execve("/bin/ls", argv, envp) == -1) // se nao quiser mandar envp meto NULL
        return 1;
    return 0;  // Este ponto nunca será alcançado se execve for bem-sucedido
}
```

# errno

`#include <errno.h>`

A variável `errno` é uma variável global em C que é utilizada para indicar se ocorreu um erro durante a execução de uma função do sistema ou da biblioteca. Quando uma função que pode falhar é chamada, se ocorrer um erro, errno é definido com um código de erro específico que pode ser usado para determinar o que deu errado.

Se uma função falhar, errno é definido como um valor diferente de zero. Se a função for bem-sucedida, errno pode manter o valor anterior ou ser zero. Por isso, é importante verificar errno apenas após uma falha de função.
é definido por várias funções do sistema e da biblioteca C.

Cada função que pode falhar tem seus próprios códigos de erro que podem ser atribuídos a errno.

# strerror()

`#include <string.h>` 

A função `strerror()` converte um código de erro em uma string descritiva. É útil quando você tem um código de erro (geralmente retornado por funções do sistema) e deseja obter uma descrição legível.

Assinatura: `char *strerror(int errnum);`

### Parâmetros
- errnum: O número do erro, que geralmente é obtido de errno.
### Retorno
- Retorna um ponteiro para uma string estática que descreve o erro correspondente ao código fornecido.
    
# perror()

`#include <stdio.h>`

A função `perror()` é uma maneira conveniente de imprimir uma mensagem de erro para a saída padrão (normalmente o terminal) precedida por uma string especificada pelo usuário. Ela utiliza o valor de errno para imprimir a mensagem de erro correspondente.

Assinatura: `void perror(const char *s);`

### Parâmetros
- s: Uma string que será impressa antes da mensagem de erro. Se s for NULL, apenas a mensagem de erro será impressa.
### Retorno
- Não retorna valor (tipo void).

# signal()
`#include <signal.h>`
A função `signal()` é usada em C para capturar ou lidar com sinais (interrupts ou eventos) enviados para um processo. Sinais são um mecanismo que o sistema operacional usa para notificar um processo sobre eventos assíncronos, como a terminação de um processo filho, uma interrupção de teclado (como Ctrl+C), ou erros de execução.

Assinatura: `void (*signal(int signum, void (*handler)(int)))(int);`

### Parâmetros
- signum: O número do sinal que você quer capturar ou ignorar. Alguns sinais comuns incluem:
    - `SIGINT`: Interrupção de terminal (geralmente Ctrl+C).
    - `SIGTERM`: Solicitação de terminação.
    - `SIGKILL`: Sinal de matar um processo (não pode ser capturado ou ignorado).
    - `SIGCHLD`: Indica que um processo filho terminou.
    - `SIGSEGV`: Erro de segmentação (tentativa de acessar memória inválida).
- handler: Um ponteiro para a função que será chamada quando o sinal for recebido. Pode ser:
    - `Signal handler`: Uma função que será chamada quando o sinal for capturado.
    - `SIG_IGN`: Para ignorar o sinal.
    - `SIG_DFL`: Para restaurar o comportamento padrão para esse sinal.
### Retorno
- Retorna o antigo handler de sinal se for bem-sucedido.
- Se ocorrer um erro, retorna SIG_ERR.

#### Exemplo de uso:
```
void handle_sigint(int sig) {
        printf("Recebi o sinal %d (SIGINT). Ignorando Ctrl+C...\n", sig);
}           

int main() {
    // Define o handler para SIGINT (Ctrl+C)
    signal(SIGINT, handle_sigint);
    ...
}
```

# sigaction()

`#include <signal.h>`

A função `sigaction()` é uma alternativa mais robusta e flexível à função signal() para capturar e manipular sinais em C. Enquanto signal() tem algumas limitações de portabilidade e confiabilidade, `sigaction()` oferece um controle mais preciso sobre o comportamento dos sinais, permitindo especificar várias opções, como máscaras de sinal e flags que afetam o comportamento da função.

Assinatura: `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

### Parâmetros
- signum: O número do sinal que queremos capturar ou manipular (como SIGINT, SIGTERM, etc.).
- act: Um ponteiro para uma estrutura do tipo struct sigaction, que especifica o novo comportamento para o sinal signum.
- oldact: Um ponteiro para uma estrutura do tipo struct sigaction, onde o comportamento anterior do sinal (antes da modificação) será armazenado. Se não for necessário recuperar o comportamento anterior, esse valor pode ser passado como NULL.
### Retorno: 
- Retorna 0 em caso de sucesso. Se houver erro, retorna -1 e define errno com o código de erro apropriado.
    
#### Estrutura sigaction
```
struct sigaction {
    void     (*sa_handler)(int);   // Ponteiro para a função de tratamento do sinal
    void     (*sa_sigaction)(int, siginfo_t *, void *); // Alternativa para o handler
    sigset_t sa_mask;              // Máscara de sinais bloqueados durante a execução do handler
    int      sa_flags;             // Flags que controlam o comportamento do sinal
};
```
- sa_handler: Um ponteiro para a função que será chamada quando o sinal for capturado. Pode ser SIG_IGN (ignorar o sinal) ou SIG_DFL (comportamento padrão).
- sa_mask: Especifica outros sinais que devem ser bloqueados (temporariamente ignorados) enquanto o handler de sinal está sendo executado. Isso evita que um sinal interrompa o tratamento de outro.
- sa_flags: Flags que modificam o comportamento de captura de sinal. Algumas flags comuns incluem:
    - `SA_RESTART`: Faz com que chamadas de sistema interrompidas por sinais sejam reiniciadas automaticamente.
    - `SA_NOCLDSTOP`: Evita que SIGCHLD seja enviado quando um processo filho parar.
    - `SA_SIGINFO`: Usa a função sa_sigaction em vez de sa_handler para manipular sinais, fornecendo informações adicionais.
#### Exemplo de uso:
```
void handle_sigint(int sig) {
    printf("Recebi o sinal SIGINT (%d), ignorando Ctrl+C...\n", sig);
}

int main() {
    struct sigaction sa;
    
    // Configura o handler de sinal
    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART;  // Reinicia chamadas interrompidas
    sigemptyset(&sa.sa_mask);  // Nenhum sinal será bloqueado

    // Define o tratamento para SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erro ao definir sigaction");
        return 1;
    }
    ...
}
```

# sigemptyset() 

A função `sigemptyset()` é usada para inicializar um conjunto de sinais (sigset_t), que é uma estrutura usada para representar um grupo de sinais no sistema. Quando você chama sigemptyset(), ela limpa todos os sinais do conjunto, ou seja, garante que nenhum sinal está inicialmente incluído no grupo.
Usada para inicializar um set, basicamente

# sigaddset()

A função `sigaddset()` é usada para adicionar um sinal a um conjunto de sinais para serem bloqueados

Assinatura: `int sigaddset(sigset_t *set, int signum);`

#### Exemplo:

```
sigemptyset(&sa.sa_mask);         // Inicializa o conjunto de sinais vazio
sigaddset(&sa.sa_mask, SIGTERM);  // Adiciona SIGTERM ao conjunto, bloqueando-o
```

# kill()

A função `kill()` em C é usada para enviar sinais a um processo ou grupo de processos.

Assinatura: `int kill(pid_t pid, int sig);`

### Parâmetros:
- pid: Identifica o processo ou grupo de processos que receberá o sinal.
    - pid > 0: Envia o sinal ao processo cujo ID é igual a pid.
    - pid == 0: Envia o sinal a todos os processos no mesmo grupo de processos do chamador.
    - pid <    -1: Envia o sinal a todos os processos cujo ID de grupo de processos é igual a |pid| (o valor absoluto de pid).
    - pid == -1: Envia o sinal a todos os processos para os quais o chamador tem permissão de enviar sinais (exceto a si próprio e o processo init).
- sig: O número do sinal que será enviado, como SIGKILL, SIGTERM, SIGINT, etc. Se o valor for 0, a função não envia um sinal real, mas faz uma verificação se o processo ainda existe e se há permissão para enviar sinais a ele.
### Retorno:
- 0 em caso de sucesso.
- -1 em caso de erro e errno será definido com o código de erro apropriado (como ESRCH se o processo não existir ou EPERM se não houver permissão).
#### Exemplos de Sinais Comuns:
`SIGKILL`: Termina um processo imediatamente, sem dar chance para o processo tratar ou ignorar o sinal.
`SIGTERM`: Solicita a terminação de um processo de forma amigável. O processo pode capturar e tratar o sinal, o que permite que ele se encerre graciosamente.
`SIGINT`: Interrompe um processo, semelhante ao que acontece quando o usuário pressiona Ctrl+C no terminal.
`SIGSTOP`: Suspende um processo (não pode ser ignorado ou capturado).
`SIGCONT`: Continua a execução de um processo suspenso.

# dup()

`#include <fcntl.h>`

A função `dup()` em C é usada para duplicar um descritor de arquivo existente. O novo descritor de arquivo criado compartilha a mesma tabela de arquivos abertos que o descritor original, o que significa que ambos referenciam o mesmo arquivo ou recurso e compartilham a mesma posição de leitura/escrita e flags.

Assinatura: `int dup(int oldfd);`

### Parâmetros:
- oldfd: O descritor de arquivo que você deseja duplicar. Este descritor deve ser válido, ou seja, o arquivo deve estar aberto.
### Retorno:
- Retorna o número do novo descritor de arquivo em caso de sucesso.
- Retorna -1 em caso de erro e define errno com o código de erro apropriado.

#### Exemplo de uso
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1, fd2;
    
    // Abre um arquivo para escrita
    fd1 = open("exemplo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    // Duplica o descritor de arquivo
    fd2 = dup(fd1);
    if (fd2 < 0) {
        perror("Erro ao duplicar o descritor de arquivo");
        return 1;
    }

    // Escreve no arquivo usando os dois descritores
    write(fd1, "Texto pelo fd1\n", 15);
    write(fd2, "Texto pelo fd2\n", 15);

    // Fecha ambos os descritores
    close(fd1);
    close(fd2);
    return 0;
}
```

# dup2()

`#include <fcntl.h>`

A função `dup2()` é uma versão da função `dup()` que permite que você duplique um descritor de arquivo para um descritor específico. Essa função é especialmente útil para redirecionar a entrada ou saída de um programa.

Assinatura: `int dup2(int oldfd, int newfd);`

### Parâmetros:
- oldfd: O descritor de arquivo que você deseja duplicar.
- newfd: O descritor de arquivo onde oldfd deve ser duplicado. Se newfd já estiver aberto, ele será fechado antes de ser duplicado.
### Retorno:
- Retorna o valor de newfd em caso de sucesso.
- Retorna -1 em caso de erro e define errno com o código de erro apropriado.

#### Exemplo de uso:
```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    int saved_stdout;  // Para guardar o descritor original de stdout

    // Guarda o descritor original de stdout
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout < 0) {
        perror("Erro ao guardar stdout");
        return 1;
    }
    // Abre um arquivo para escrita
    fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    // Duplica o descritor de arquivo para redirecionar stdout
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Erro ao redirecionar stdout");
        return 1;
    }
    // Agora, printf enviará a saída para o arquivo saida.txt
    printf("Esta mensagem será redirecionada para o arquivo saida.txt\n");

    // Restaura stdout para seu estado original
    if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
        perror("Erro ao restaurar stdout");
        return 1;
    }
    // Agora, printf enviará a saída de volta para a tela
    printf("Esta mensagem será enviada de volta para a saída padrão (tela)\n");

    // Fecha o descritor do arquivo
    close(fd);
    close(saved_stdout); // Fecha o descritor salvo, se não for mais necessário
    return 0;
}
```
# pipe()

`#include <unistd.h>`

A função `pipe()` é usada em C para criar um canal de comunicação entre processos. Ela permite que um processo escreva dados que podem ser lidos por outro processo, estabelecendo uma comunicação unidirecional. Esse mecanismo é muito útil para interprocess communication (IPC).

Assinatura: `int pipe(int pipefd[2]);`

### Parâmetros:
- pipefd: É um array de dois inteiros. O primeiro elemento (pipefd[0]) será o descritor de leitura, e o segundo elemento (pipefd[1]) será o descritor de escrita.
### Retorno:
- Retorna 0 em caso de sucesso.
- Retorna -1 em caso de erro e define errno com o código de erro apropriado.

#### Funcionamento:
Quando você cria um pipe, ele é composto por um buffer na memória. Os dados escritos no descritor de escrita (pipefd[1]) podem ser lidos do descritor de leitura (pipefd[0]).
A comunicação é unidirecional: se você escrever em pipefd[1], não poderá ler a partir desse descritor. Para ler, você deve usar pipefd[0].

_**TLDR:**_

`pipe[0]` => **READING**

`pipe[1]` => **WRITING**

Quando um processo é forked, o filho herda os mesmos fds entao podemos fechar o lado do pipe que não queremos usar. 
Usar um pipe por via de comunicacao.  
Não esquecer de fechar os fds que não vamos usar no inicio e depois de os usar no fim.

#### Exemplo de uso
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];

    // Cria o pipe
    if (pipe(pipefd) == -1) {
        perror("Erro ao criar pipe");
        return 1;
    }

    // Cria um processo filho
    pid = fork();
    if (pid == -1) {
        perror("Erro ao criar processo filho");
        return 1;
    }

    if (pid == 0) { // Processo filho
        // Fecha o descritor de leitura
        close(pipefd[0]); 

        // Escreve uma mensagem no pipe
        const char *msg = "Olá do filho!";
        write(pipefd[1], msg, strlen(msg) + 1); // +1 para incluir o terminador nulo
        close(pipefd[1]); // Fecha o descritor de escrita
    } else { // Processo pai
        // Fecha o descritor de escrita
        close(pipefd[1]); 

        // Lê a mensagem do pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Mensagem do filho: %s\n", buffer);
        close(pipefd[0]); // Fecha o descritor de leitura
    }

    return 0;
}
```

# getcwd() 

`#include <unistd.h>`

A função `getcwd()` em C é usada para obter o caminho absoluto (diretório de trabalho atual) do processo em execução. Ela preenche um buffer fornecido pelo usuário com o caminho completo do diretório onde o programa está sendo executado no momento. 

Assinatura: `char *getcwd(char *buf, size_t size);`

### Parâmetros:
- buf: Um ponteiro para um buffer onde o caminho será armazenado.
- size: O tamanho do buffer em bytes.
- Ao passar NULL como o primeiro argumento e 0 como o segundo, o sistema automaticamente aloca um buffer suficientemente grande para armazenar o caminho completo. Neste caso, você deve liberar a memória com free() após usá-la para evitar vazamentos de memória.
`cwd = getcwd(NULL, 0);`
### Retorno:
- Retorna um ponteiro para o buffer contendo o caminho absoluto em caso de sucesso.
- Retorna NULL em caso de erro, e errno é definido com o código de erro apropriado.

####  Exemplo de uso:
```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // Aloca dinamicamente memória para o caminho
    char *cwd = getcwd(NULL, 0);
    if (cwd) {
        printf("Diretório de trabalho atual: %s\n", cwd);
        free(cwd); // Não se esqueça de liberar a memória alocada
    } 
    else {
        perror("Erro ao obter o diretório de trabalho atual");
        return 1;
    }
    return 0;
}
```

# chdir() 

`#include <unistd.h>`

A função `chdir()` é utilizada para mudar o diretório de trabalho atual de um processo. Ela permite que você altere o diretório em que o processo está operando, o que pode ser útil em várias situações, como ao trabalhar com arquivos em diferentes diretórios.

Assinatura: `int chdir(const char *path);`

### Parâmetros:
- path: Um ponteiro para uma string que representa o caminho do diretório que você deseja definir como o novo diretório de trabalho. Pode ser um caminho absoluto (exemplo: /home/- user/diretorio) ou um caminho relativo (exemplo: ./diretorio).
### Retorno:
- Retorna 0 em caso de sucesso.
- Retorna -1 em caso de erro, e errno é definido para indicar o tipo de erro.
Se tentarmos mudar para um diretório que não existe ou para um diretório para o qual não tem permissões, chdir() falhará e errno será definido para indicar o erro (por exemplo, ENOENT para "No such file or directory" ou EACCES para "Permission denied").

# unlink() 

`#include <unistd.h>`

A função `unlink()` é usada para remover um link para um arquivo no sistema de arquivos, o que, na prática, significa excluir o arquivo (desde que não haja mais links para ele). Se o arquivo tiver vários links, a função apenas remove o link especificado, e o arquivo só será realmente excluído quando o último link for removido e não houver mais processos com o arquivo aberto.

Assinatura: `int unlink(const char *pathname);`

### Parâmetros
- pathname: O caminho do arquivo que você deseja remover.
### Retorno
- Retorna 0 em caso de sucesso.
- Retorna -1 em caso de erro, e errno é ajustado para indicar o erro.

#### Exemplo de uso:
```
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "example.txt";

    // Tenta remover o arquivo
    if (unlink(filename) == -1) {
        if (errno == EACCES) {
            perror("Erro: Permissão negada para remover o arquivo");
        } else if (errno == EPERM) {
            perror("Erro: Operação não permitida");
        } else {
            perror("Erro ao remover o arquivo");
        }
        return 1; // Retorna com erro
    }

    printf("Arquivo %s removido com sucesso.\n", filename);
    return 0; // Retorna com sucesso
}
```

# opendir()   

```
#include <sys/types.h>
#include <dirent.h>
```

A função `opendir()` é usada para abrir um diretório no sistema de arquivos e retornar um ponteiro para uma estrutura DIR, que será usada para ler o conteúdo do diretório (como os arquivos e subdiretórios nele). Ela é normalmente utilizada em conjunto com outras funções de manipulação de diretórios, como readdir(), closedir(), entre outras.

Assinatura: `DIR *opendir(const char *name);`

### Parâmetros:
- name: O caminho para o diretório que você deseja abrir.
### Retorno:        
- Um ponteiro para uma estrutura do tipo DIR que representa o diretório aberto.
- NULL em caso de erro, e errno é definido para indicar o motivo do erro.
  
__É preciso usar a closedir(DIR*)__

# Definitions

`DIR *dir`: This is a pointer to a DIR structure, which represents a directory stream. You will use this pointer to access the directory entries.

`struct dirent *entry`: This is a pointer to a struct dirent, which holds information about a directory entry, such as the name of the file or directory.

```
struct dirent {
    ino_t   d_ino;       // Número do inode
    char    d_name[];    // Nome da entrada (arquivo ou subdiretório)
};
```

# closedir():
Fecha o diretório após a leitura.
Assinatura: int closedir(DIR *dirp);
### Parâmetros:
- `DIR *dirp`: A pointer to a DIR structure representing the directory stream to be closed.
### Retorno:
- Returns 0 on success.
- Returns -1 on failure and sets errno to indicate the error.


#### Exemplo de uso
```
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // Required for DIR, dirent, opendir, readdir, closedir

int main() {
    const char *dir_path = "."; // Path to the directory (current directory)
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Failed to open directory");
        return EXIT_FAILURE;
    }

    // Read entries from the directory
    while ((entry = readdir(dir)) != NULL) {
        // Print the name of the file/directory
        printf("Found: %s\n", entry->d_name);
    }

    // Close the directory stream
    closedir(dir);

    return EXIT_SUCCESS;
}
```






























