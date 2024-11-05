CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
CLIENT = client
COMMON = main action args maker util ft_isdigit ft_atoi mutex
NAME = philo

#COMOBJ = $(addprefix $(COMDIR)/, $(addsuffix .o, $(COMMON)))
OBJ = $(addsuffix .o, $(COMMON))
AR = ar -rcs

all : $(NAME)

# -I means that headerfile is located at current directory
%.o : %.c philosopher.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

# Make lib
# @ : target
# < : first dependency
# -L : lib file is located at current DIR here0930
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re