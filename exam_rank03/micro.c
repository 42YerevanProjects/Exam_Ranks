#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_zone
{
	int		width;
	int		height;
	char	background;
}				t_zone;

typedef struct s_rectangle
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}			t_rectangle;

// Util functions
//
size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

int	ft_error(char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	return (1);
}

int	check_rec(t_rectangle rec)
{
	 float check = 1.00000000;
	if ((rec.height > 0.00000000 && rec.width > 0.00000000) && (rec.type == 'r' || rec.type == 'R'))
		return (-1);
    if ((x < rec.x) || (rec.x + rec.width < x) || (y < rec.y) || (rec.y + rec.height < y))
        return (-1);
	return 0;
}

// Source functions

char	**init_matrix(t_zone *zone, FILE *fp)
{
	char	**matrix;
	int		i;
	int		j;

	if (fscanf(fp, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
	{
		fclose(fp);
		return (NULL);
	}
	i = 0;
	matrix = (char **)malloc(zone->height *  sizeof(char *));
	while (i < zone->height)
		matrix[i++] = (char *)malloc(zone->width * sizeof(char));
	i = 0;
	while (i < zone->height)
	{
		j = 0;
		while (j < zone->width)
			matrix[i][j++] = zone->background;
		i++;
	}
	return (matrix);
}

int	init_rectangles(FILE *fp, char **matrix)
{
	t_rectangle tmp;
	int			count;
	
	count = fscanf(fp, "%c %f %f %f %f %c", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color);
	while (count == 6)
	{
		if (check_rec(tmp) == -1)
			return (-1);
		// get rectangles
		count = fscanf(fp, "%c %f %f %f %f %c", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color);
	}
}

void	print_matrix(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[j])
			write(1, matrix[j++], 1);
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char** argv)
{
	FILE 	*fp;
	char	**matrix;
	t_zone	zone;

	if (argc != 2)
		return (ft_error("Error: argument"));
	if (!(fp = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted"));
	if (!(matrix = init_matrix(&zone, fp)))
		return (ft_error("Error: matrix cannot be initialized"));
	// TODO Initialize rectangles
	print_matrix(matrix);
	return (0);
}
