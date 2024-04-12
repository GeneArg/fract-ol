/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:21 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/12 16:42:27 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_error(char *str, int exit_code)
{
	ft_putstr_fd(str, 2);
	exit(exit_code);
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
	(void)argc;
	(void)argv;
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
	}
	else
	{
		ft_putstr_fd("Usage: ./fractol mandelbrot\n", 2);
		ft_putstr_fd("Usage: ./fractol julia [real] [imaginary]\n", 2);
		return (0);
	}
}