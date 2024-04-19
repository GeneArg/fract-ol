/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:21 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/19 17:55:15 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_error(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

void	zoom(double x_change, double y_change, void *context)
{
	t_data	*data;
	float	scale;

	data = (t_data *)context;
	(void)x_change;
	if (y_change > 0)
		scale = 0.9;
	else
		scale = 1.1;
	data->x[0] *= scale;
	data->x[1] *= scale;
	data->y[0] *= scale;
	data->y[1] *= scale;
}

unsigned int	calculate_color(t_data *data, float iter)
{
	const int	r = (data->colour[R] * iter);
	const int	g = (data->colour[G] * iter);
	const int	b = (data->colour[B] * iter);
	const int	a = 255;

	return ((r << 24) | (g << 16) | (b << 8) | a);
}

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
		data->colour[R] += 5;
		data->colour[G] += 7;
		data->colour[B] += 2;
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
	data->iter = 50;
	data->x[0] = -3;
	data->x[1] = 2;
	data->y[0] = 1.5;
	data->y[1] = -1.5;
	data->colour[R] = 2;
	data->colour[G] = 4;
	data->colour[B] = 6;
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10)
				&& ft_strlen(argv[1]) == 10)) || (argc == 4
			&& !ft_strncmp(argv[1], "julia", 5) && ft_strlen(argv[1]) == 5))
	{
		if (argc == 4)
		{
			if (validate_coords(argv[2]) || validate_coords(argv[3]))
				print_error("Invalid coordinates\n", 1);
			data.fractal = 2;
		}
		if (argc == 2)
			data.fractal = 1;
		initialize(&data, argc, argv);
		mlx_loop_hook(data.mlx, &event_dispatcher, (void *)&data);
		mlx_scroll_hook(data.mlx, &zoom, (void *)&data);
		mlx_loop(data.mlx);
		mlx_terminate(data.mlx);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol mandelbrot\n", 2);
		print_error("Usage: ./fractol julia [real] [imaginary]\n", 1);
	}
}
