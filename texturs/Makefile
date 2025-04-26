CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	gnl/get_next_line.c gnl/get_next_line_utils.c \
			mandatory/libft_utils/ft_arraylen.c mandatory/libft_utils/ft_free_array.c mandatory/libft_utils/ft_put.c mandatory/libft_utils/ft_split.c mandatory/libft_utils/ft_strtrim.c\
			mandatory/libft_utils/ft_substr.c mandatory/libft_utils/ft_strchr.c mandatory/libft_utils/_strlen.c mandatory/libft_utils/_strjoin.c mandatory/libft_utils/ft_atoi.c mandatory/libft_utils/ft_strcmp.c\
			mandatory/parsing/parsing1.c mandatory/parsing/parsing5.c mandatory/parsing/parsing2.c mandatory/parsing/parsing3.c mandatory/parsing/parsing0.c mandatory/parsing/move_player.c \
			mandatory/parsing/check/check_map.c mandatory/parsing/check/che_map_utils.c mandatory/parsing/check/check_utils.c\
			mandatory/parsing/draw_map.c\
			mandatory/raycasting/raycasting_utils.c mandatory/raycasting/raycasting.c mandatory/raycasting/utils.c\
			mandatory/texturing.c \
			mandatory/main.c

BONUS_SRCS =   	gnl/get_next_line.c gnl/get_next_line_utils.c \
				bonus/libft_utils/ft_arraylen.c bonus/libft_utils/ft_free_array.c bonus/libft_utils/ft_put.c bonus/libft_utils/ft_split.c bonus/libft_utils/ft_strtrim.c\
				bonus/libft_utils/ft_substr.c bonus/libft_utils/ft_strchr.c bonus/libft_utils/_strlen.c bonus/libft_utils/_strjoin.c bonus/libft_utils/ft_atoi.c bonus/libft_utils/ft_strcmp.c\
				bonus/libft_utils/ft_lstadd_back_bonus.c bonus/libft_utils/ft_lstnew_bonus.c\
				bonus/parsing/parsing1.c bonus/parsing/parsing5.c bonus/parsing/parsing2.c bonus/parsing/parsing3.c bonus/parsing/parsing0.c bonus/parsing/move_player.c bonus/parsing/move_utils.c \
				bonus/parsing/check/check_map.c bonus/parsing/check/che_map_utils.c bonus/parsing/check/check_utils.c\
				bonus/parsing/draw/draw_map.c bonus/parsing/draw/draw_gun.c bonus/parsing/draw/draw_utils.c bonus/parsing/draw/draw_minimap.c bonus/parsing/draw/more_utils.c\
				bonus/raycasting/raycasting_utils.c bonus/raycasting/raycasting.c bonus/raycasting/utils.c\
				bonus/texturing.c \
				bonus/main.c\

MLX 	    = 	MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
HEADER_M	= 	gnl/get_next_line.h mandatory/include/types.h mandatory/include/cub3d.h  
HEADER_B	= 	gnl/get_next_line.h bonus/include/types.h bonus/include/cub3d.h 
OBJS	    =	$(SRCS:.c=.o)
BONUS_OBJS  =   $(BONUS_SRCS:.c=.o)
NAME        =   cub3d
BONUS_NAME  =   cub3d_bonus

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_M)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(HEADER_B)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(MLX)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus