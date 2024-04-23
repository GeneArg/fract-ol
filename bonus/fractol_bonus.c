/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:01:21 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 15:37:25 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 2 && (!ft_strncmp(argv[1], "mandelbrot", 10)
				|| !ft_strncmp(argv[1], "burning", 7))
			&& (ft_strlen(argv[1]) == 10 || ft_strlen(argv[1]) == 7))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		if (argc == 4)
		{
			if (validate_coords(argv[2]) || validate_coords(argv[3]))
				print_error("Invalid coordinates\n", 1);
			data.fractal = 2;
		}
		if (ft_strlen(argv[1]) == 10)
			data.fractal = 1;
		else if (ft_strlen(argv[1]) == 7)
			data.fractal = 3;
		initialize(&data, argc, argv);
		mlx_loop_hook(data.mlx, &event_dispatcher, (void *)&data);
		mlx_scroll_hook(data.mlx, &zoom, (void *)&data);
		mlx_loop(data.mlx);
		mlx_terminate(data.mlx);
	}
	else
		print_error("./fractol mandelbrot OR burning OR julia [r] [i]\n", 2);
}
