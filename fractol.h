/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:06:23 by eagranat          #+#    #+#             */
/*   Updated: 2024/04/17 18:27:46 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "MLX42/include/MLX42/MLX42.h"

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>


enum e_colours
{
	R,
	G,
	B
};

/**
	* @param *mlx 			graphics library initialized
	* @param *img 			image thats on my screen
	* @param iter 			max iterations
	* @param x[2] 			projected / scaled x
	* @param y[2] 			projected / scaled y
	* @param julia[2] 		XY location for fixed julia point
	* @param colour[3] 		[0][1][2] = [R][G][B]
	* @param mouse[2] 		XY of mouse[]
**/
typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	long			iter;
	float			x[2];
	float			y[2];
	float			julia[2];
	int				colour[3];
	int32_t			mouse[2];
}	t_data;

#endif