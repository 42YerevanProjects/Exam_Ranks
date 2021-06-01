#include <unistd.h>

int	ft_repeated(int c, char *str, int i)
{
	int j;

	j = 0;
	while (j < i && str[j])
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

void ft_inter(char **argv)
{
	int i;
	int j;

	i = 0;
	while (argv[1][i])
	{
		j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j] && !ft_repeated(argv[1][i], argv[1], i))
			{
				write (1, &argv[1][i], 1);
				break;
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
}

int	main (int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	else 
		ft_inter(argv);
	return(1);
}
