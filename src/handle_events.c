/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:54:48 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 15:04:17 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	handle_arrow_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->x[0] += 0.1;
		data->x[1] += 0.1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->x[0] -= 0.1;
		data->x[1] -= 0.1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->y[0] += 0.1;
		data->y[1] += 0.1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->y[0] -= 0.1;
		data->y[1] -= 0.1;
	}
}

void	handle_key_press_events(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
	{
		data->x[0] = -3;
		data->x[1] = 2;
		data->y[0] = 1.5;
		data->y[1] = -1.5;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
		data->iter += 25;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
	{
		if (data->iter > 25)
			data->iter -= 25;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_C))
	{
		data->colour[R] = (data->colour[R] + 5) % 256;
		data->colour[G] = (data->colour[G] + 3) % 256;
		data->colour[B] = (data->colour[B] + 7) % 256;
	}
}

void	event_dispatcher(void *context)
{
	t_data	*data;

	data = (t_data *)context;
	handle_arrow_keys(data);
	handle_key_press_events(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (data->fractal == 1)
		mandelbrot(data);
	else if (data->fractal == 2)
		julia(data);
}
