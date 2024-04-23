/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:06:23 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/22 13:35:33 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum			e_colours
{
	R,
	G,
	B
};

/**
 * @param *mlx 			graphics library initialized
 * @param *img 			image thats on my screen
 * @param fractal 		1 - Mandelbrot, 2 - Julia
 * @param iter 			max iterations
 * @param x[2] 			projected / scaled x
 * @param y[2] 			projected / scaled y
 * @param julia[2] 		XY location for fixed julia point
 * @param colour[3] 		[0][1][2] = [R][G][B]
 * @param mouse[2] 		XY of mouse[]
 **/
typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			fractal;
	long		iter;
	float		x[2];
	float		y[2];
	float		julia[2];
	int			colour[3];
	int32_t		mouse[2];
}				t_data;

int				validate_coords(char *str);
float			ft_atof(char *str);
void			initialize(t_data *data, int argc, char **argv);
void			initialize_mlx(t_data *data);
void			initialize_burning_ship(t_data *data);
unsigned int	calculate_color(t_data *data, float iter);
void			zoom(double x_change, double y_change, void *context);
void			print_error(char *str, int exit_code);
void			event_dispatcher(void *context);
void			handle_key_press_events(t_data *data);
void			handle_arrow_keys(t_data *data);
void			julia(t_data *d);
int				check_julia(t_data *data, float x, float y);
void			mandelbrot(t_data *d);
float			check_mandelbrot(int max_iter, float orig_x, float orig_y);
void			burning_ship(t_data *d);
float			check_burning_ship(t_data *data, float orig_x, float orig_y);

#endif
