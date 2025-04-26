CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	gnl/get_next_line.c gnl/get_next_line_utils.c \
			mandatory/libc/ft_arraylen.c mandatory/libc/ft_free_array.c mandatory/libc/ft_put.c mandatory/libc/ft_split.c mandatory/libc/ft_strtrim.c\
			mandatory/libc/ft_substr.c mandatory/libc/ft_strchr.c mandatory/libc/_strlen.c mandatory/libc/_strjoin.c mandatory/libc/ft_atoi.c mandatory/libc/ft_strcmp.c\
			mandatory/parsing/parsing1.c mandatory/parsing/parsing5.c mandatory/parsing/parsing2.c mandatory/parsing/parsing3.c mandatory/parsing/parsing0.c mandatory/parsing/move_player.c \
			mandatory/parsing/check/check_map.c mandatory/parsing/check/che_map_utils.c mandatory/parsing/check/check_utils.c\
			mandatory/parsing/draw_map.c\
			mandatory/raycasting/raycasting_utils.c mandatory/raycasting/raycasting.c mandatory/raycasting/utils.c\
			mandatory/texturing.c \
			mandatory/main.c


MLX 	    = 	MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
HEADER_M	= 	gnl/get_next_line.h mandatory/include/types.h mandatory/include/cub3d.h  
OBJS	    =	$(SRCS:.c=.o)
NAME        =   cub3d

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_M)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re