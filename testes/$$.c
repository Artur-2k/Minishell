#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!1
// TODO TESTAR NO PC DA ESCOLA SE ESTE FICHEIRO ESTA NO MESMO SITIO!!!!!
int main()
{
	int	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (perror("pirilau\n"), -1);

	char buffer[16];
	int bytes_read;
	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0)
		return (perror("pipipopu\n"), -2);

	buffer[bytes_read] = '\0';

	int pid = atoi(buffer); // stops at the first non number;
	int pid2 = getpid();
	printf("Real: %d\nMeu: %d\n", pid2, pid);

	return 0;
}