#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("texto.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Erro ao abrir o arquivo\n");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("[%s]", line);
		free(line);
	}
	close(fd);
	return (0);
}
