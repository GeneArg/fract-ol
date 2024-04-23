/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:49:17 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 15:22:53 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

void	initialize_burning_ship(t_data *data)
{
	data->iter = 50;
	data->x[0] = -2;
	data->x[1] = 2;
	data->y[0] = -2;
	data->y[1] = 2;
}

void	initialize_mlx(t_data *data)
{
	data->mlx = mlx_init(1080, 720, "fractol", true);
	if (!data->mlx)
		print_error("Failed to initialize MLX\n", 1);
	data->img = mlx_new_image(data->mlx, 1080, 720);
	if (!data->img)
		print_error("Failed to create new image\n", 1);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
		print_error("Failed to put image to window\n", 1);
}

void	initialize(t_data *data, int argc, char **argv)
{
	initialize_mlx(data);
	if (data->fractal == 3)
		initialize_burning_ship(data);
	else
	{
		data->iter = 50;
		data->x[0] = -3;
		data->x[1] = 2;
		data->y[0] = 1.5;
		data->y[1] = -1.5;
	}
	data->colour[R] = 128;
	data->colour[G] = 128;
	data->colour[B] = 128;
	if (argc == 4)
	{
		data->julia[0] = ft_atof(argv[2]);
		data->julia[1] = ft_atof(argv[3]);
	}
	else
	{
		data->julia[0] = 0;
		data->julia[1] = 0.8;
	}
}
