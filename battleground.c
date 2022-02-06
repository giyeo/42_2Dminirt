#include "minirt.h"

int		this_point_is_in_a_circle(int i, int j, int x_position, int y_position, int radius)
{
	if(((i - x_position) * (i - x_position)) + ((j - y_position) * (j - y_position)) < (radius * radius))
		return 1;
	return 0; 
}

int line_line(int i, int j, t_data *img, t_cord cord1, t_cord cord2)
{
    t_cord cord3;
    t_cord cord4;

    cord3.x = (double)i;
    cord3.y = (double)j;

    cord4.x = img->x_position;
    cord4.y = img->y_position;

    double uA = ( (cord4.x - cord3.x) * (cord1.y - cord3.y) - (cord4.y - cord3.y) * (cord1.x - cord3.x) )
              / ( (cord4.y - cord3.y) * (cord2.x - cord1.x) - (cord4.x - cord3.x) * (cord2.y - cord1.y) );

    double uB = ( (cord2.x - cord1.x) * (cord1.y - cord3.y) - (cord2.y - cord1.y) * (cord1.x - cord3.x) )
              / ( (cord4.y - cord3.y) * (cord2.x - cord1.x) - (cord4.x - cord3.x) * (cord2.y - cord1.y) );

    if(uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
        return 1;
    return 0;
}

t_cord  *assign_cord_line_values(void)
{
    t_cord *cord = (t_cord *)malloc(sizeof(t_cord) * 8);
    cord[0].x = 400;cord[0].y = 500;
    cord[1].x = 400;cord[1].y = 400;

    cord[2].x = 400;cord[2].y = 400;
    cord[3].x = 500;cord[3].y = 400;

    cord[4].x = 500;cord[4].y = 400;
    cord[5].x = 500;cord[5].y = 500;

    cord[6].x = 400;cord[6].y = 500;
    cord[7].x = 500;cord[7].y = 500;
    return cord;
}

void	draw(t_data *img)
{
	int i = 0;
	int j = 0;
	int color = 0;
    t_cord *cord;

    cord = assign_cord_line_values();
	while(j < 900)
	{
		while(i < 900)
		{	
            if(i >= 400 && i <= 500 && j >= 400 && j <= 500)
                color = mlx_get_hex_trgb(0, 255, 0);
            else if(this_point_is_in_a_circle(i, j, img->x_position, img->y_position, 5))
                color = mlx_get_hex_trgb(255, 255, 0);
            else if(line_line(i, j, img, cord[0], cord[1]))
                color = mlx_get_hex_trgb(0, 0, 0);
            else if(line_line(i, j, img, cord[2], cord[3]))
                color = mlx_get_hex_trgb(0, 0, 0);
            else if(line_line(i, j, img, cord[4], cord[5]))
                color = mlx_get_hex_trgb(0, 0, 0);
            else if(line_line(i, j, img, cord[5], cord[6]))
                color = mlx_get_hex_trgb(0, 0, 0);
			else
                color = mlx_get_hex_trgb(200, 200, 200);
			my_mlx_pixel_put(img, i, j, color);
			i++;
		}
		i = 0;
		j++;
	}
    free(cord);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
