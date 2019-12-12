SRCS_cub3d = srcs/cub3d.c srcs/error.c srcs/file_check.c srcs/file_read.c \
srcs/file_read2.c srcs/structure.c srcs/mini_map.c srcs/keys_set.c srcs/cast.c \
srcs/wall.c srcs/utils.c srcs/player.c srcs/texture.c srcs/sprite.c \
srcs/screenshot.c srcs/free_all.c srcs/collision.c \

SRCS_libft = libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strlcpy.c \
libft/ft_isdigit.c libft/ft_putchar_fd.c libft/ft_strnstr.c libft/ft_atoi.c \
libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_putstr_fd.c \
libft/get_next_line.c libft/ft_strjoin_free.c \

SRCS = ${SRCS_cub3d} ${SRCS_libft}

INCL = -Iincludes/

OBJS = ${SRCS:.c=.o}

NAME = Cub3D

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${OBJS}
		gcc  ${FLAGS} -I/usr/local/include -o$(NAME) ${OBJS} -L/usr/local/lib -lmlx -framework Opengl -framework APPKIT

.c.o : ${SRCS}
		gcc ${FLAGS} -c ${INCL} $< -o ${<:.c=.o}
clean :
		rm -f ${OBJS}

fclean : clean
		rm -f $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
