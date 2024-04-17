/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:21 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/17 18:24:17 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_error(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

void	control_hook(void *context)
{
	t_data	*data;

	data = (t_data *) context;
	(void) data;
	// mouse functionality here
}

void	initialize_mandelbrot(t_data *data)
{
	data->iter = 50;
	data->x[0] = -3;
	data->x[1] = 2;
	data->y[0] = 1.5;
	data->y[1] = -1.5;
	data->colour[R] = 2;
	data->colour[G] = 4;
	data->colour[B] = 6;
}

float	ft_atof(char *str)
{
	float	res;
	float	dec;
	int		i;
	int		sign;

	i = 0;
	res = 0;
	dec = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		dec = dec * 10 + str[i] - '0';
		i++;
	}
	dec /= pow(10, i);
	return ((res + dec) * sign);
}

void	initialize_julia(t_data *data, int argc, char **argv)
{
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
	initialize_mandelbrot(data);
	initialize_julia(data, argc, argv);
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


int main(int argc, char **argv)
{
	t_data	data;
	
    if (((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10) && ft_strlen(argv[1]) == 10))
	|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5) && ft_strlen(argv[1]) == 5))
	{
		if (argc == 4)
		{
			if (validate_coords(argv[2]) || validate_coords(argv[3]))
				print_error("Invalid coordinates\n", 1);
		}
		initialize(&data, argc, argv);
		mlx_loop_hook(data.mlx, &control_hook, (void *) &data);
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol mandelbrot\n", 2);
		ft_putstr_fd("Usage: ./fractol julia [real] [imaginary]\n", 2);
		return (0);
	}
}