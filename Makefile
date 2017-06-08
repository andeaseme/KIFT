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

IDIR =	includes
ODIR :=	obj
SDIR =	src

vpath %.c	$(SDIR) $(SDIR)/client $(SDIR)/server $(SDIR)/speech_recognition \
			$(SDIR)/command

HEADERS = -I $(IDIR)
CC = gcc
CFLAGS = $(HEADERS) #-Wall -Wextra -Werror -g
SPHINXFLAGS =	-DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
				`pkg-config --cflags --libs pocketsphinx sphinxbase`

DEPS =	$(IDIR)/kift.h

_OBJ =	audiotostr.o client.o server.o
OBJ :=	$(addprefix $(ODIR)/,$(_OBJ))

_C_OBJ =	client.o
C_OBJ :=	$(addprefix $(ODIR)/,$(_C_OBJ))

_S_OBJ =	server.o audiotostr.o
S_OBJ :=	$(addprefix $(ODIR)/,$(_S_OBJ))

all: $(CLIENT) $(SERVER)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SPHINXFLAGS)

$(OBJ): | $(ODIR)

$(ODIR):
		mkdir -p $@
		@echo 'make directory $@'

$(CLIENT): $(C_OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

$(SERVER): $(S_OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(SPHINXFLAGS)
		@echo 'compile $@'

clean:
		/bin/rm -rfv $(ODIR)
		@echo '$@ $(NAME) $(ODIR)'

fclean: clean
		/bin/rm -f $(NAME)
		@echo '$< $(NAME)'

re: fclean all

.PHONY: all clean fclean re
