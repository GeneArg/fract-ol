/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:53:49 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 15:22:23 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

float	check_burning_ship(t_data *data, float orig_x, float orig_y)
{
	float	x;
	float	y;
	float	temp;
	float	iter;

	x = 0;
	y = 0;
	iter = 0;
	while ((x * x + y * y) <= 4 && iter < data->iter)
	{
		temp = (x * x) - (y * y) + orig_x;
		y = fabs(2 * x * y) + orig_y;
		x = fabs(temp);
		iter++;
	}
	return (iter);
}

void	burning_ship(t_data *d)
{
	float	iter;
	int		color;
	int		pixel[2];
	float	x_scaled;
	float	y_scaled;

	pixel[0] = 0;
	pixel[1] = 0;
	while (pixel[0] < 1080)
	{
		pixel[1] = 0;
		while (pixel[1] < 720)
		{
			x_scaled = d->x[0] + (pixel[0] / 1080.0) * (d->x[1] - d->x[0]);
			y_scaled = d->y[0] + (pixel[1] / 720.0) * (d->y[1] - d->y[0]);
			iter = check_burning_ship(d, x_scaled, y_scaled);
			if (iter == d->iter)
				color = 0xFF;
			else
				color = calculate_color(d, iter);
			mlx_put_pixel(d->img, pixel[0], pixel[1], color);
			pixel[1]++;
		}
		pixel[0]++;
	}
}
