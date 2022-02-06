#include "minirt.h"
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	mlx_get_hex_trgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b));
}

int		this_point_is_in_a_circle(int i, int j, int x_position, int y_position, int radius)
{
	if(pow(i - x_position, 2) + pow(j - y_position, 2) < pow(radius, 2))
		return 1;
	return 0; 
}

int	is_prime(int number)
{
	if(number == 0)
		return 0;
	if(number == 1)
		return 0;
	if(number == 2)
		return 1;

	int i = 3;
	double sqrt_n = sqrt(number);
	while(i < (sqrt_n + 1))
	{
		if((number % i) == 0)
			return 0;
		i += 2;
	}
	return 1;
}

int		this_point_is_in_a_square(int i, int j, t_data *img)
{
	if((abs((i - 150) + (j - 150)) + abs((i - 100)- (j - 100))) < 50)
		return 1;
	return 0;
}

int	is_an_object(int i, int j, t_data *img, double *slope)
{
	if(this_point_is_in_a_circle(i, j, img->x_position, img->y_position, img->radius))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(252, 150 , 1));
		return 1;
	}
	if(this_point_is_in_a_square(i, j, img))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(0, 150 , 1));
		return 1;
	}
	if(this_point_is_in_a_line(i, j, img, slope))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(0, 0 , 0));
		return 1;
	}
	return 0;
}

double	*calc_slopes(){
	double *slopes = (double *)malloc(sizeof(double)*1800);
	double i = 0;
	double j = 0;
	while(j < 900)
	{
		if(j != 450 && i != 450)
			slopes[(int)j] = (j - 450) / (i - 450);
		j++;
	}
	while(i < 900)
	{
		if(j != 450 && i != 450)
			slopes[(int)j+(int)i] = (j - 450) / (i - 450);
		i++;
	}
	printf("%f\n", i + j);
	return slopes;
}

int		this_point_is_in_a_line(int i, int j, t_data *img, double *slope)
{
	double di = i;
	double dj = j;
	int counter = 0;
	while(counter < 1800)
	{
		if((dj - 450) == (slope[counter] * (di - 450)))
			return 1;
		counter++;
	}
	return 0;
}

void	draw(t_data *img)
{
	int i = 0;
	int j = 0;
	double *slope;
	slope = calc_slopes();
	while(j < 900)
	{
		while(i < 900)
		{	
			if(!is_an_object(i, j, img, slope))
				my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(255,228,132));
			i++;
		}
		i = 0;
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

int	key_control(int key, t_data *img)
{
	//printf("%d\n", key);
	if (key == 65363)
		img->x_position += 50;
	if (key == 65361)
		img->x_position -= 50;
	if (key == 65362)
		img->y_position -= 50;
	if (key == 65364)
		img->y_position += 50;
	if (key == 113)
		img->radius -= 50;
	if (key == 101)
		img->radius += 50;
	if (key == 119)
		img->div += 100;
	if (key == 115 && img->div > 900)
		img->div -= 100;
	draw(img);
	return (0);
}

int	main(void)
{
	t_data	img;

	img.radius = 50;
	img.x_position = 450;
	img.y_position = 450;
	img.div = 900;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 900, 900, "Minirt");
	img.img = mlx_new_image(img.mlx, 900, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw(&img);
	mlx_key_hook(img.mlx_win, key_control, &img);
	mlx_loop(img.mlx);
}



/*
		while(i < 900)
		{	
			if(this_point_is_in_a_circle(i, j, img->x_position, img->y_position, img->radius) && !is_prime(j))
				my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(211 * i / img->div, 156 * i / img->div, 126 * i / img->div));
			else if (this_point_is_in_a_circle(i, j, img->x_position, img->y_position, img->radius))
				my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(114,97,77));
			else
				my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(0,0,0));
			i++;
		}
*/


int	is_prime(int number)
{
	if(number == 0)
		return 0;
	if(number == 1)
		return 0;
	if(number == 2)
		return 1;

	int i = 3;
	double sqrt_n = sqrt(number);
	while(i < (sqrt_n + 1))
	{
		if((number % i) == 0)
			return 0;
		i += 2;
	}
	return 1;
}

int		this_point_is_in_a_square(int i, int j, t_data *img)
{
	if((abs((i - 150) + (j - 150)) + abs((i - 100)- (j - 100))) < 50)
		return 1;
	return 0;
}

int	is_an_object(int i, int j, t_data *img, double *slope)
{
	if(this_point_is_in_a_circle(i, j, img->x_position, img->y_position, img->radius))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(252, 150 , 1));
		return 1;
	}
	if(this_point_is_in_a_square(i, j, img))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(0, 150 , 1));
		return 1;
	}
	if(this_point_is_in_a_line(i, j, img, slope))
	{
		my_mlx_pixel_put(img, i, j, mlx_get_hex_trgb(225, 6 , 0));
		return 1;
	}
	return 0;
}

double	*calc_slopes(t_data *img){
	double *slopes = (double *)malloc(sizeof(double)*1800);
	double i = 0;
	double j = 0;
	while(j < 900)
	{
		if(j != (double)img->y_position && i != (double)img->x_position)
			slopes[(int)j] = (j - (double)img->y_position) / (i - (double)img->x_position);
		j++;
	}
	while(i < 900)
	{
		if(j != (double)img->y_position && i != (double)img->x_position)
			slopes[(int)j+(int)i] = (j - (double)img->y_position) / (i - (double)img->x_position);
		i++;
	}
	return slopes;
}

int		this_point_is_in_a_line(int i, int j, t_data *img, double *slope)
{
	double di = i;
	double dj = j;
	int counter = 0;
	while(counter < 1800)
	{
		if((dj - (double)img->y_position) == (slope[counter] * (di - (double)img->x_position)))
			return 1;
		counter++;
	}
	return 0;
}

int	raytrace_from_pixel_to_light_source(int i, int j, t_data *img)
{
	double slope;

	slope = (j - (double)img->y_position) / (i - (double)img->x_position);

}

t_cord	*create_square(int xo, int yo, int side)
{
	int counter = 0;
	t_cord *cords = (t_cord *)malloc(((side) * (side)) * sizeof(t_cord) + 1);
	int i = xo;
	int j = yo;

	cords[counter].x = side;
	cords[counter].y = side;
	counter++;
	while(j < yo + side)
	{
		while(i < xo + side)
		{
			cords[counter].x = i;
			cords[counter].y = j;
			counter++;
			i++;
		}
		i = xo;
		j++;
	}
	return cords;
}

t_cord	*create_objects(t_data *img)
{
	return create_square(200, 200, 50);
}

int	belongs_to_a_object(int i, int j, t_cord *objects, t_data *img)
{
	double slope;

	slope = ((double)j - (double)img->y_position) / ((double)i - (double)img->x_position);
	
	int counter = 1;
	int size = objects[0].x * objects[0].y;

	while(counter < size + 1)
	{
		// if((i == objects[counter].x) && (j == objects[counter].y))
		if ((((double)objects[counter].y / (double)img->y_position) - (slope * ((double)objects[counter].x / (double)img->x_position))) == 1)
			return 1;
		counter++;
	}
	return 0;
}