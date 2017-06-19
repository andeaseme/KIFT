/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:00:37 by aphan             #+#    #+#             */
/*   Updated: 2017/06/18 16:32:36 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KIFT_H
# define KIFT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netdb.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <stdbool.h>
# include <pocketsphinx.h>
# include "libft.h"

# define SERVER_PORT	22005
# define HMMDIR			"lang_model"
# define LANGDIR		"lang_model/2823.lm"
# define DICTDIR		"lang_model/2823.dic"
# define READ_SIZE		2048
# define RESET			write(1, "\x1b[0m", 4)
# define GREEN			write(1, "\x1b[32m", 5)
# define RED			write(1, "\x1b[31m", 5)
# define INVERSE		write(1, "\x1b[7m", 4)
# define BOLD			write(1, "\x1b[1m", 4)
# define HISTORY_KEY	"history"

struct					s_con
{
	int					i;
	int					port_num;
	int					sock_fd;
	struct sockaddr_in	servaddr;
	char				*speech;
};

typedef	struct			s_wavtoa
{
	ps_decoder_t		*ps;
	cmd_ln_t			*config;
	FILE				*fh;
	int					rv;
	size_t				nsamp;
	int16				buf[READ_SIZE];
	char const			*hyp;
	int32				score;
}						t_wavtoa;

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
void					send_history(int comm_fd);

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
int						cmd_lights(void *cmd);
int						cmd_history(void *cmd);
int						cmd_weather(void *cmd);

#endif
