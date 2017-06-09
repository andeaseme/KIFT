/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:00:37 by aphan             #+#    #+#             */
/*   Updated: 2017/06/07 16:01:04 by aphan            ###   ########.fr       */
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
#include <pocketsphinx.h>

#define HMMDIR      MODELDIR "/en-us/en-us"
#define LANGDIR     MODELDIR "/en-us/en-us.lm.bin"
#define DICTDIR     MODELDIR "/en-us/cmudict-en-us.dict"
#define READ_SIZE   2048

/*
** src/speech_recognition
*/
const char		*audiotostr(char *audiopath);

/*
** src/client
*/

/*
** src/server
*/

/*
** src/command
*/
int				command(char *speech, int sockfd);
int				cmd_unknown(int sockfd);
int				cmd_seteggtimer(int sockfd);