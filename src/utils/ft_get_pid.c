/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:29:42 by artuda-s          #+#    #+#             */
/*   Updated: 2024/12/11 10:19:36 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
/proc/self é um link simbólico que aponta sempre para o diretório do
processo que está acessando esse caminho.
/proc/[pid]/stat é um arquivo que contém informações detalhadas sobre
o processo com o identificador [pid].

Conteúdo de /proc/self/stat:
O arquivo /proc/self/stat contém uma única linha de texto com vários
campos, separados por espaços. Esses campos fornecem informações sobre
o processo, como seu estado, prioridade, uso de CPU, memória, etc.
A linha geralmente tem mais de 50 campos, mas os principais são:

Índice | Campo        | Descrição
-------|--------------|-------------------------------------------------------
  1    | pid          | ID do processo
  2    | comm         | Nome do processo entre parênteses
  3    | state        | Estado do processo (R: Executando, S: Suspenso,
       |              | D: Em espera ininterrupta, Z: Zumbi, T: Parado)
  4    | ppid         | ID do processo pai
  5    | pgrp         | ID do grupo de processos
  6    | session      | ID da sessão
  7    | tty_nr       | Terminal de controle do processo
  8    | tpgid        | ID do grupo de processos em primeiro plano
  9    | flags        | Flags do processo (variam de acordo com o kernel)
 14    | utime        | Tempo de CPU em modo usuário (em ticks)
 15    | stime        | Tempo de CPU em modo kernel (em ticks)
 22    | starttime    | Tempo (em ticks) desde o início do sistema até
       |              | o início do processo
 24    | rss          | Tamanho da memória residente (em páginas)
 39    | processor    | Número da CPU em que o processo foi executado
       |              | pela última vez
 43    | guest_time   | Tempo de CPU gasto em execução de processos
       |              | convidados (virtualização)

Nota:
- Os tempos `utime`, `stime` e `starttime` são dados em "ticks".
- O número de ticks por segundo pode ser obtido com a função sysconf(_SC_CLK_TCK).
- O campo `rss` representa o uso de memória, onde cada página geralmente tem 4 KB.
*/

// returns pid or a < 0 number on error
int	ft_get_pid(void)
{
	int	pid;
	int	fd;
	int bytes_read;
	char buffer[50];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
		return (-2);
	buffer[bytes_read] = '\0';
	pid = ft_atoi(buffer);
      close(fd);
	return (pid);
}