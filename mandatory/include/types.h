/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <eel-ansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:58:48 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/11/14 17:50:51 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "cub3d.h"

# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREY 0x808080FF
# define NEW 0xE0E0E0FF
# define FOV 1.047198
# define ROTATION_SPEED 0.1
# define MOVE_SPEED 5.0
# define SIZE 30
# define WIDTH 1650
# define HEIGHT 1050

typedef struct s_helper
{
	char			*line;
	int				find[6];
	int				res;
	char			*ptr_line;
	char			*trim_line;
}					t_helper;

typedef struct s_player
{
	int				x;
	int				y;
	double			px;
	double			py;
	double			angle;
	mlx_image_t		*image_player;
}					t_player;

typedef struct s_dis_h
{
	double			x_h;
	double			y_h;
	char			inter_type_h;
}					t_dis_h;

typedef struct s_dis_v
{
	double			x_v;
	double			y_v;
	char			inter_type_v;
}					t_dis_v;

typedef struct s_rays
{
	t_dis_h			dis_h;
	t_dis_v			dis_v;
	double			rayangle;
}					t_rays;

typedef struct s_map
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				f[3];
	int				c[3];
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*textur[4];
}					t_data;

#endif
