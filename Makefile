# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 17:12:26 by aphan             #+#    #+#              #
#    Updated: 2017/06/07 15:56:21 by aphan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
NAME = $(SERVER) $(CLIENT)

LDIR =	libft
IDIR =	includes
ODIR :=	obj
SDIR =	src

vpath %.c	$(SDIR) $(SDIR)/client_src $(SDIR)/server_src \
			$(SDIR)/speech_recognition $(SDIR)/command

HEADERS = -I $(IDIR) -I $(LDIR)/includes
CC = gcc
CFLAGS = $(HEADERS) -g #-Wall -Wextra -Werror
SPHINXFLAGS =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
				`pkg-config --cflags --libs pocketsphinx sphinxbase`

LIBFT =	-L $(LDIR) -lft
DEPS =	$(IDIR)/kift.h

_OBJ =	command.o set_egg_timer.o unknown_command.o \
		audiotostr.o \
		client.o \
		server.o
OBJ :=	$(addprefix $(ODIR)/,$(_OBJ))

_C_OBJ =	client.o command.o set_egg_timer.o unknown_command.o
C_OBJ :=	$(addprefix $(ODIR)/,$(_C_OBJ))

_S_OBJ =	server.o audiotostr.o
S_OBJ :=	$(addprefix $(ODIR)/,$(_S_OBJ))

all: $(NAME)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SPHINXFLAGS)

$(OBJ): | $(ODIR)

$(ODIR):
		mkdir -p $@
		@echo 'make directory $@'

FORCE:

$(LIBFT): FORCE
		$(MAKE) -C $(LDIR)

$(CLIENT): $(C_OBJ) $(LIBFT)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

$(SERVER): $(S_OBJ) $(LIBFT)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

clean:
		/bin/rm -rfv $(ODIR)
		@echo '$@ $(NAME) $(ODIR)'
		$(MAKE) -C $(LDIR) $@

fclean: clean
		/bin/rm -f $(NAME)
		@echo '$< $(NAME)'
		$(MAKE) -C $(LDIR) $@

re: fclean all

.PHONY: all clean fclean re
