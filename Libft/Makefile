NAME = libft.a
LIBC = ar rcs
CC = cc
ARR_DIR = ./array
FDP_DIR = ./fdprintf
INCLUDES = ./includes
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I${INCLUDES}

ARR_SRCS =	${ARR_DIR}/inner_merge_arr.c ${ARR_DIR}/merge_arr.c ${ARR_DIR}/arr_utils.c ${ARR_DIR}/clear_arr.c \
			${ARR_DIR}/int_arr.c
FDP = ${FDP_DIR}/fdprintf.c ${FDP_DIR}/utils.c 

SRCS =	${ARR_SRCS} ${FDP}	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_realloc.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_strlcmp.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strtod.c \
		ft_isnumber.c ft_atol.c ft_printf.c ft_print_char.c \
		ft_print_str.c ft_print_ptr.c ft_print_nbr.c ft_print_hexa.c \
		ft_print_unsigned_nbr.c get_next_line.c get_next_line_utils.c \

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

%.o: %.c ${INCLUDES}/libft.h ${INCLUDES}/ft_printf.h ${INCLUDES}/get_next_line.h ${INCLUDES}/malloc.h ${INCLUDES}/t_bool.h ${INCLUDES}/array.h ${INCLUDES}/fdprintf.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
