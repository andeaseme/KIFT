/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:00:37 by aphan             #+#    #+#             */
/*   Updated: 2017/06/17 22:50:09 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include "libft.h"

# define SERVER_PORT	22005

# define BW				"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/bw"
# define MLLR			"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/mllr_solve"
# define MAP 			"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/map_adapt"

# define HMMDIR			"ROB"
# define LANGDIR		"2823.lm"
# define DICTDIR		"2823.dic"
# define READ_SIZE		2048

# define RESET			write(1, "\x1b[0m", 4)
# define GREEN			write(1, "\x1b[32m", 5)
# define RED			write(1, "\x1b[31m", 5)
# define INVERSE		write(1, "\x1b[7m", 4)
# define BOLD			write(1, "\x1b[1m", 4)

struct s_con
{
	int					i;
	int					sock_fd;
	struct sockaddr_in	servaddr;
	char				*speech;
};

/*
** src/speech_recognition
*/
char					*audiotostr(char *audiopath);

/*
** src/
*/
void					handle_signal(int status);
int						init_server_save(void);
struct s_con			*init_server(int port_num);
int						increment_audio_count(int ac);

/*
** src/command
*/
int						command(char *speech, struct s_con *temp);
int						cmd_unknown(void *cmd);
int						cmd_seteggtimer(void *cmd);
int						cmd_showmetemps(void *cmd);
int						cmd_toggletraining(void *cmd);
int						cmd_googlesearch(void *cmd);
int						cmd_googlemusic(void *cmd);
int						cmd_sendemail(void *cmd);
int						cmd_showsysteminfo(void *cmd);
int						cmd_whoami(void *cmd);
int						cmd_whereami(void *cmd);
