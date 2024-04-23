/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:52:09 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 14:32:15 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

float	check_mandelbrot(int max_iter, float orig_x, float orig_y)
{
	float	x;
	float	y;
	float	temp;
	float	iter;

	y = orig_y;
	x = orig_x;
	iter = 0;
	while ((x * x + y * y) <= 4 && iter < max_iter)
	{
		temp = (x * x) - (y * y) + orig_x;
		y = 2 * (x * y) + orig_y;
		x = temp;
		iter++;
	}
	return (iter);
}

void	mandelbrot(t_data *d)
{
	float	x;
	float	y;
	float	scaled_coord[2];
	float	iter;
	int		color;

	x = 0;
	y = 0;
	while (x < 1080)
	{
		scaled_coord[0] = d->x[0] + (x / 1080) * (d->x[1] - d->x[0]);
		while (y < 720)
		{
			scaled_coord[1] = d->y[0] + (y / 720) * (d->y[1] - d->y[0]);
			iter = check_mandelbrot(d->iter, scaled_coord[0], scaled_coord[1]);
			if (iter == d->iter)
				color = 0xFF;
			else
				color = calculate_color(d, iter);
			mlx_put_pixel(d->img, x, y, color);
			y++;
		}
		x++;
		y = 0;
	}
}

int	check_julia(t_data *data, float x, float y)
{
	float	temp;
	int		iter;

	iter = 0;
	while ((x * x + y * y) < 4 && iter < data->iter)
	{
		temp = x * x - y * y + data->julia[0];
		y = 2 * x * y + data->julia[1];
		x = temp;
		iter++;
	}
	return (iter);
}

void	julia(t_data *d)
{
	float	x;
	float	y;
	float	scaled_coords[2];
	int		color;
	float	iter;

	x = 0;
	y = 0;
	while (x < 1080)
	{
		scaled_coords[0] = d->x[0] + (x / 1080) * (d->x[1] - d->x[0]);
		while (y < 720)
		{
			scaled_coords[1] = d->y[0] + (y / 720) * (d->y[1] - d->y[0]);
			iter = check_julia(d, scaled_coords[0], scaled_coords[1]);
			if (iter == d->iter)
				color = 0xFF;
			else
				color = calculate_color(d, iter);
			mlx_put_pixel(d->img, x, y, color);
			y++;
		}
		x++;
		y = 0;
	}
}

