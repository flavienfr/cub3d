SRCS_cub3d = srcs/cub3d.c srcs/error.c srcs/file_check.c srcs/file_read.c srcs/file_read2.c srcs/structure.c \
srcs/print_all.c srcs/keys_set.c srcs/cast.c srcs/buffer_color.c srcs/3d_wall.c \
srcs/maths_utils.c srcs/player.c
SRCS_gnl = get_next_line/get_next_line.c
SRCS_libft = libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c \
libft/ft_strlen.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_strlcpy.c \
libft/ft_strlcat.c libft/ft_strnstr.c libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_memmove.c \
libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_strclen.c \

SRCS = ${SRCS_cub3d} ${SRCS_libft} ${SRCS_gnl}

INCL = -Iincludes/

OBJS = ${SRCS:.c=.o}

NAME = Cub3D

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${OBJS}
		#gcc ${FLAGS} -o$(NAME) ${OBJS} ./libmlx.dylib
		gcc ${FLAGS} -I/usr/local/include -o$(NAME) ${OBJS} -L/usr/local/lib -lmlx -framework Opengl -framework APPKIT
		
.c.o : ${SRCS}
		gcc ${FLAGS} -c ${INCL} $< -o ${<:.c=.o}
clean :
		rm -f ${OBJS}

fclean : clean
		rm -f $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
