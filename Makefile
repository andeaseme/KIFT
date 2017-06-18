# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aphan <aphan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 17:12:26 by aphan             #+#    #+#              #
#    Updated: 2017/06/18 15:30:30 by rmatos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
NAME = $(SERVER) $(CLIENT)

LDIR =	libft
IDIR =	includes
ODIR :=	obj
SDIR =	src
PS_IDIR = ~/.brew/Cellar/cmu-pocketsphinx/HEAD-05b866c/include/pocketsphinx
S_IDIR = ~/.brew/Cellar/cmu-sphinxbase/HEAD-27a98f9/include

vpath %.c	$(SDIR) $(SDIR)/command

HEADERS = -I $(IDIR) -I $(LDIR)/includes -I $(PS_IDIR) -I $(S_IDIR) -I $(S_IDIR)/sphinxbase
CC = gcc
CFLAGS = $(HEADERS) -g -Wall -Wextra -Werror
SPHINXFLAGS =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
				`pkg-config --cflags --libs pocketsphinx sphinxbase`

LIBFT =	-L $(LDIR) -lft
DEPS =	$(IDIR)/kift.h

_OBJ =	command.o cmd3.o cmd2.o cmd1.o \
		audiotostr.o \
		client.o server.o utility.o history.o
OBJ :=	$(addprefix $(ODIR)/,$(_OBJ))


_C_OBJ =	client.o command.o cmd3.o cmd2.o cmd1.o utility.o history.o
C_OBJ :=	$(addprefix $(ODIR)/,$(_C_OBJ))

_S_OBJ =	server.o audiotostr.o utility.o
S_OBJ :=	$(addprefix $(ODIR)/,$(_S_OBJ))

all: $(NAME)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ): | $(ODIR)

$(ODIR):
		mkdir -p $@
		@echo 'make directory $@'

FORCE:

$(NAME): $(LIBFT)

$(LIBFT): FORCE
		$(MAKE) -C $(LDIR)
		$(MAKE) -C SAM
		$(MAKE) -C osx-cpu-temp

$(CLIENT): $(C_OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

$(SERVER): $(S_OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

clean:
		/bin/rm -rfv $(ODIR)
		@echo '$@ $(NAME) $(ODIR)'
		$(MAKE) -C $(LDIR) $@
		rm -rf Train_src/serv_save

fclean: clean
		/bin/rm -f $(NAME)
		@echo '$< $(NAME)'
		$(MAKE) -C $(LDIR) $@

re: fclean all

wav: all
	/bin/rm -rfv Train_src/serv_save

.PHONY: all clean fclean re
