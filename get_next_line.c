#include "get_next_line.h"

#include <fcntl.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	index_buffer;
	static int	bytes_read;
	int			index;
	char		*line;

	index = 0;
	line = malloc(10000);
	while (1)
	{
		if (bytes_read <= index_buffer)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			index_buffer = 0;
		}
		line[index++] = buffer[index_buffer++];
		if (line[index - 1] == '\n')
			break ;
	}
	line[index] = '\0';
	if (index == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
