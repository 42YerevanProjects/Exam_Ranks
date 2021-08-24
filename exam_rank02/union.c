#include <unistd.h>

int	ft_contains(int c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

void	ft_union(char **argv)
{
	int i;

	i = 0;
	while (argv[1][i])
	{
		if (!ft_repeated(argv[1][i], argv[1], i))
				write(1, &argv[1][i], 1);
		i++;		
	}
	i = 0;
	while (argv[2][i])
	{
		if (!ft_repeated(argv[2][i], argv[2], i) && !ft_contains(argv[2][i], argv[1]))
			write(1, &argv[2][i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv) 
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	else
		ft_union(argv);
	return (0);
}
