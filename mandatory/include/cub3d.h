/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:40:50 by med-dahr          #+#    #+#             */
/*   Updated: 2025/04/27 08:40:52 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../gnl/get_next_line.h"
# include "types.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

/*				libft				*/
void		safe_free(void **ptr);
int			array_length(char **array);
void		free_array_2d(char **array);
void		print_str_fd(char *s, int fd);
char		**ft_split(char *s, char *c);
char		*ft_substr(char const *s, size_t start, size_t len);
char		*ft_strchr(char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
char		*_strjoin(char *s1, char *s2);
int			_strlen(char *str);

/*                    parsing                      */
int			parse_color(int *data_color, char *str, char *name);
int			process_line(char *c, char **ptr_line, int *find);
int			 load_map(char *line, int fd, t_data *data_struct, char *ptr_line);
int			 parse_path(char **str, int i, char *name, char **path);
int			 load_file(int fd, t_helper *helper, int x);
int			 initialize_data(t_data *data_struct, t_helper *helper, int fd);
int			 validate_inputs(int ac, t_data *data_struct, int fd);
int			 validate_path(char *str, int len, int index);

/*					texturing					*/

void		 draw_floor_ceiling(t_data *data);
uint32_t	 sample_texture(t_data *data, t_rays rays, double tex_y,
				int texture_index);
int			 get_texture_index(t_dis_h dis_h, t_dis_v dis_v, double rayangle);

/*                      utils                   */
void		validate_map(t_data *s_map);
char		**duplicate_array(char **array);
void		error_exit(char *str, t_data *s_map);
void		 cleanup(t_data *data_struct, int i);

/*				check_utils						*/
int			validate_map_char(char **arr, t_data *s_map);
int			find_zero_position(char **arr, t_data *s_map);
int			is_valid_path(char **data, int y, int x);
void		handle_input(t_data *data);
void		init_input_handler(void *param);

/*					raycasting					*/
void		cast_rays(t_data *data, int i, double y);
int			is_ray_blocked(t_data *data, double y, double x);
double		ft_calculate_distance(double xp, double yp, double x, double y);
int			is_valid_position(t_data *data, double py, double px, double num_pix);
void		render_wall(t_data *data, double line_height, double i, t_rays rays);
void		render_scene(void *ptr);
double		normalize_angle(double angle);

#endif
