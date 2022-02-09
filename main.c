#include "minirt.h"

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

int	key_control(int key, t_data *img)
{
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

void	animation(t_data *img)
{
	int to_right = 1;
	int to_bottom = 0;
	int to_left = 0;
	int to_up = 0;
	while(img->x_position < 902)
	{
		draw(img);
		if(img->x_position == 850)
		{
			to_right = 0;
			to_bottom = 1;
		}
		if(img->y_position == 850)
		{
			to_bottom = 0;
			to_left = 1;
		}
		if(img->x_position == 50)
		{
			to_left = 0;
			to_up = 1;
		}
		if(img->y_position == 50 && img->x_position == 50)
		{
			to_up = 0;
			to_right = 1;
		}
		if(to_right)
			img->x_position += 1;
		else if (to_bottom)
			img->y_position += 1;
		else if (to_left)
			img->x_position -= 1;
		else if (to_up)
			img->y_position -= 1;
	}
}

void	set_img(t_data *img)
{
	img->radius = 50;
	img->x_position = 0;
	img->y_position = 50;
	img->div = 900;
}

int	main(void)
{
	t_data	img;

	set_img(&img);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 900, 900, "2dMinirt");
	img.img = mlx_new_image(img.mlx, 900, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	animation(&img);
	//draw(&img);
	mlx_key_hook(img.mlx_win, key_control, &img);
	mlx_loop(img.mlx);
}
