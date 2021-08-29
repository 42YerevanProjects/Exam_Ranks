#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_zone
{
	int		width;
	int		height;
	char	background;
}				t_zone;

typedef struct s_shape
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}			t_shape;

// Util functions

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

int	get_zone(FILE *fp, t_zone *zone)
{
	int scan_ret;

	if ((scan_ret = fscanf(fp, "%d %d %c\n", &zone->width, &zone->height, &zone->background)) != 3)
		return (0);
	if (!((zone->width > 0 && zone->width <= 300) && (zone->height > 0 && zone->height <= 300)))
		return (0);
	if (scan_ret == -1)
		return (0);
	return (1);
}

int	in_rectangle(float x, float y, t_shape *shape)
{
	if (((x < shape->x || (shape->x + shape->width < x))
		|| (y < shape->y)) || (shape->y + shape->height < y))
		return (0);
	if (((x - shape->x < 1.00000000) || ((shape->x + shape->width) - x < 1.00000000)) ||
	((y - shape->y < 1.00000000 || ((shape->y + shape->height) - y < 1.00000000))))
		return (2);
	return (1);
}

int	ft_clear(FILE *fp, char *matrix)
{
	fclose(fp);
	if (matrix)
		free(matrix);
	return(0);
}

int	check_shape(t_shape *shape)
{
	return (shape->width > 0.00000000 && shape->height > 0.00000000
			&& (shape->type == 'r' || shape->type == 'R'));
}

// Source functions

void	get_shape(char **matrix, t_shape *shape, t_zone *zone)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (i < zone->height)
	{
		j = 0;
		while (j< zone->width)
		{
			ret = in_rectangle(j, i, shape);
			if ((shape->type == 'r' && ret == 2)
				|| (shape->type == 'R' && ret))
				(*matrix)[(i * zone->width) + j] = shape->color;
			j++;
		}
		i++;
	}
}

char	*init_background(t_zone *zone, FILE *fp)
{
	char	*matrix;
	int		i;
 
	if (!get_zone(fp, zone))
		return (NULL);
	if (!(matrix = (char*)malloc(sizeof(*matrix) * (zone->width * zone->height))))
		return (NULL);
	i = 0;
	while (i < zone->width * zone->height)
		matrix[i++] = zone->background;
	return (matrix);
}

int	init_shapes(FILE *fp, char **matrix, t_zone *zone)
{
	t_shape	tmp;
	int		scan_ret;
	
	scan_ret = fscanf(fp, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color);
	while (scan_ret == 6)
	{
		if (!check_shape(&tmp))
			return (0);
		get_shape(matrix, &tmp, zone);
		scan_ret = fscanf(fp, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color);
	}
	if (scan_ret != -1)
		return (0);
	return (1);
}

void	print_matrix(char *matrix, t_zone *zone)
{
	int	i;

	i = 0;
	while (i < zone->height)
	{
		write(1, matrix + (i * zone->width), zone->width);
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char** argv)
{
	FILE 	*fp;
	char	*matrix;
	t_zone	zone;

	if (argc != 2)
		return (ft_error("Error: argument"));
	if (!(fp = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted"));
	if (!(matrix = init_background(&zone, fp)))
	{
		ft_clear(fp, matrix);
		return (ft_error("Error: Operation file corrupted"));
	}
	if (!init_shapes(fp, &matrix, &zone))
	{
		ft_clear(fp, matrix);
		return (ft_error("Error: Operation file corrupted"));
	}
	print_matrix(matrix, &zone);
	ft_clear(fp, matrix);
	return (0);
}
