#include "get_next_line.h"

int get_next_line(char **line)
{
	int		i;
	int		r;
	char	c;
	char	*buffer;

	i = 0;
	if (!(buffer = (char *)malloc(10000)))
		return (-1);
	while ((r = read(0, &c, 1)) && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	*line = buffer;
	return (r);
}
