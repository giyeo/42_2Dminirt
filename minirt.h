#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data {
	int		div;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int 	radius;
	int 	x_position;
	int 	y_position;
}			t_data;

typedef	struct s_xy
{
	double x;
	double y;
}	t_cord;

void	draw(t_data *img);
int     mlx_get_hex_trgb(int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
