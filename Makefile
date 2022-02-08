NAME := minirt

SRC := main.c battleground.c

OBJS := $(SRC:.c=.o)

FLAG := -lm -lbsd -lXext -lX11 \
	-fsanitize=address

CFLAG := -Wall -O3

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(SRC)
	make --no-print-directory -C ../minilibx-linux
	gcc $(OBJS) -o $(NAME) $(CFLAG) ../minilibx-linux/libmlx_Linux.a $(FLAG)

%.o: %.c
	gcc $(CFLAG) -c $< -o $@

.PHONY: clean fclean minilibx_clean re all

clean:
	rm -f $(OBJS)

fclean: clean minilibx_clean
	rm -f $(NAME)

minilibx_clean:
	make clean -C ../minilibx-linux

re: fclean all