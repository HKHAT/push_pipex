# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elchakir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:24:40 by elchakir          #+#    #+#              #
#    Updated: 2024/01/14 16:56:43 by elchakir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONE = pipex_bonus
AR = ar rcs
FLAGS = -Wall -Wextra -Werror 
RM = rm -rf

SRC =  pipex.c utils.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strjoin.c \
       libft/ft_split.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c 

SRCB = pipex_bonus.c utils_bonus.c here_doc.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strjoin.c \
       libft/ft_split.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c

OBJS = $(libft_utils:.c=.o)

OBJB = $(libft_utils_bonus:.c=.o)

DELOBJS =  pipex.o utils.o ft_strlen.o ft_strncmp.o ft_strnstr.o ft_strjoin.o ft_split.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o

DELOBJB =  pipex_bonus.o utils_bonus.o here_doc.o ft_strlen.o ft_strncmp.o ft_strnstr.o ft_strjoin.o ft_split.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o

all:$(NAME)

$(NAME):$(OBJS)
	$(CC)  $(FLAGS)  -c $(SRC)
	$(CC) -g3  $(FLAGS)  $(DELOBJS) -o $(NAME)

bonus:$(BONE)

$(BONE):
	$(CC) $(FLAGS) -c $(SRCB)
	$(CC) -g3  $(FLAGS) $(DELOBJB) -o $(BONE)

clean:
	$(RM) $(DELOBJS) $(DELOBJB)

fclean:clean
	$(RM) $(NAME) $(BONE)

re:fclean all
