/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:00:37 by aphan             #+#    #+#             */
/*   Updated: 2017/06/13 21:04:00 by rmatos           ###   ########.fr       */
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
#include "get_next_line.h"

#define BW			"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/bw"
#define MLLR		"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/mllr_solve"
#define MAP 		"~/.brew/Cellar/cmu-sphinxtrain/HEAD-eb8bfba/libexec/sphinxtrain/map_adapt"

#define HMMDIR      "ROB"
#define LANGDIR     "ROB/en-us.lm.bin"
#define DICTDIR     "ROB/cmudict-en-us.dict"
#define READ_SIZE   2048

# define RESET write(1, "\x1b[0m", 4)
# define GREEN write(1, "\x1b[32m", 5)
# define RED write(1, "\x1b[31m", 5)
# define INVERSE write(1, "\x1b[7m", 4)
# define BOLD write(1, "\x1b[1m", 4)

struct s_con
{
	int					sock_fd;
	struct sockaddr_in	servaddr;
	char				*speech;
};

/*
** src/speech_recognition
*/
const char		*audiotostr(char *audiopath);

/*
** src/client
*/
char			*receive_string(struct s_con *temp);
void 			send_voice(struct s_con *temp);

/*
** src/server
*/

/*
** src/command
*/
int				command(char *speech, struct s_con *temp);
int				find_string(char *speech, char const *targets[]);
int				cmd_unknown(struct s_con *temp);
int				cmd_seteggtimer(struct s_con *temp);
int				cmd_showmetemps(struct s_con *temp);
int				cmd_toggletraining(struct s_con *temp);
<<<<<<< HEAD
int				cmd_opengoogle(struct s_con *temp);

=======
int				cmd_googlesearch(struct s_con *temp);
void 			train(void);
>>>>>>> 1eab412fb446f33e9e19d0d9e43d4538daf3f541
