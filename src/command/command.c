/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:49:45 by aphan             #+#    #+#             */
/*   Updated: 2017/06/17 17:40:01 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

/*
**	Set keywords
*/

static char const	*g_cmd_name[] = {
	"unknown command",
	"SET EGG TIMER",
	"SHOW ME TEMPS",
	"SHOW ME TEMPERATURES",
	"OPEN GOOGLE",
	"OPEN GOOGLE MUSIC",
	"OPEN MUSIC PLAYER",
	"SEND E-MAIL",
	NULL
};

/*
**	Set command functions
*/

static int			(*g_cmd_func[])(void *cmd) = {
	&cmd_unknown,
	&cmd_seteggtimer,
	&cmd_showmetemps,
	&cmd_showmetemps,
	&cmd_googlesearch,
	&cmd_googlemusic,
	&cmd_googlemusic,
	&cmd_sendemail,
};

static int			find_string(char *speech, char const *targets[])
{
	int		i;

	i = 0;
	while (g_cmd_name[i])
	{
		if (ft_strequ(targets[i], speech))
			return (i);
		i++;
	}
	return (0);
}

/*
**	Search for a command string within the speech string
**	and returns corresponding cmd_code then runs command in a fork
*/

int					command(char *speech, struct s_con *temp)
{
	int		cmd_code;
	pid_t	f;

	cmd_code = find_string(speech, g_cmd_name);
	f = fork();
	printf("Forking for: %s\n", g_cmd_name[cmd_code]);
	if (0 == f)
		exit(g_cmd_func[cmd_code](temp));
	else if (-1 == f)
		fprintf(stderr, "Failed to create fork for command: %s\n",
			g_cmd_name[cmd_code]);
	return (cmd_code);
}
