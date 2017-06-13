/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:49:45 by aphan             #+#    #+#             */
/*   Updated: 2017/06/08 14:49:49 by aphan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

/*
**	Set keywords
*/

static char const	*g_cmd_name[] = {
	"unknown command",
	"set egg timer",
	"set a timer",
	NULL
};

/*
**	Set command functions
*/

static int			(*g_cmd_func[])(int sockfd) = {
	&cmd_unknown,
	&cmd_seteggtimer,
	&cmd_seteggtimer	
};

int		find_string(char *speech, char const *targets[])
{
	int		i;

	i = 0;
	while (g_cmd_name[i])
	{
		if (NULL != strstr(speech, g_cmd_name[i]))
			return (i);
		i++;
	}
	return (0);
}

/*
**	Search for a command string within the speech string
**	and returns corresponding cmd_code then runs command in a fork
*/

int				command(char *speech, int sockfd)
{
	int		cmd_code;
	int		status;
	pid_t	f;

	cmd_code = find_string(speech, g_cmd_name);
	f = fork();
	if (0 == f)
		exit(g_cmd_func[cmd_code](sockfd));
	else if (-1 == f)
		fprintf(stderr, "Failed to create fork for command: %s\n",
			g_cmd_name[cmd_code]);
	return (0);
}
