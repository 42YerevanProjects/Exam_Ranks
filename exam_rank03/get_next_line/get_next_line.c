#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int 	i;
	int 	r;
	char	c;
	char	*buffer;

	i = 0;
	if (!(buffer = (char *)malloc(10000)))
		return (NULL);
	while ((r = read(fd, &c, 1)) > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
	}
	if ((!buffer[i - 1] && !r) || r == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return (buffer);
}
