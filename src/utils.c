/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:55:46 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 14:18:40 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_error(char *str, int exit_code)
{
	if (exit_code == 2)
		ft_putstr_fd("Usage: ", 2);
	else
		ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

void	zoom(double x_change, double y_change, void *context)
{
	t_data	*d;
	double	scale;
	int32_t	x_cursor;
	int32_t	y_cursor;

	d = (t_data *)context;
	if (y_change > 0)
		scale = 0.95;
	else
		scale = 1.05;
	mlx_get_mouse_pos(d->mlx, &x_cursor, &y_cursor);
	(void)x_change;
	d->x[0] = (d->x[0] + d->x[1]) / 2 + (d->x[0] - (d->x[0] + d->x[1]) / 2)
		* scale + ((d->x[0] + (x_cursor / 1080.0) * (d->x[1] - d->x[0]))
			- (d->x[0] + d->x[1]) / 2) * (1 - scale);
	d->x[1] = (d->x[0] + d->x[1]) / 2 + (d->x[1] - (d->x[0] + d->x[1]) / 2)
		* scale + ((d->x[0] + (x_cursor / 1080.0) * (d->x[1] - d->x[0]))
			- (d->x[0] + d->x[1]) / 2) * (1 - scale);
	d->y[0] = (d->y[0] + d->y[1]) / 2 + (d->y[0] - (d->y[0] + d->y[1]) / 2)
		* scale + ((d->y[0] + (y_cursor / 720.0) * (d->y[1] - d->y[0]))
			- (d->y[0] + d->y[1]) / 2) * (1 - scale);
	d->y[1] = (d->y[0] + d->y[1]) / 2 + (d->y[1] - (d->y[0] + d->y[1]) / 2)
		* scale + ((d->y[0] + (y_cursor / 720.0) * (d->y[1] - d->y[0]))
			- (d->y[0] + d->y[1]) / 2) * (1 - scale);
}

unsigned int	calculate_color(t_data *data, float iter)
{
	const int	r = (data->colour[R] * iter);
	const int	g = (data->colour[G] * iter);
	const int	b = (data->colour[B] * iter);
	const int	a = 255;

	return ((r << 24) | (g << 16) | (b << 8) | a);
}

float	ft_atof(char *str)
{
	float	r;
	float	a;
	int		i;
	int		d;

	i = 0;
	r = 0;
	a = 0;
	d = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		a = a * 10 + str[i] - '0';
		i++;
		d++;
	}
	return ((r + a / pow(10, d)) + (r + a / pow(10, d)) * -2 * (*str == '-'));
}

int	validate_coords(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}
