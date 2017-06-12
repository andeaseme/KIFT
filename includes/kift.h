/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:00:37 by aphan             #+#    #+#             */
/*   Updated: 2017/06/09 17:49:37 by aphan            ###   ########.fr       */
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
#include <pocketsphinx.h>
#include "libft.h"

#define HMMDIR      "ROB"
#define LANGDIR     "ROB/en-us.lm.bin"
#define DICTDIR     "ROB/cmudict-en-us.dict"
#define READ_SIZE   2048

/*
** src/speech_recognition
*/
const char		*audiotostr(char *audiopath);

/*
** src/client
*/
char			*recieve_string(int sock_fd);
void 			send_voice(int sock_fd);

/*
** src/server
*/

/*
** src/command
*/
int				command(char *speech, int sockfd);
int				find_string(char *speech, char *targets[]);
int				cmd_unknown(int sockfd);
int				cmd_seteggtimer(int sockfd);
