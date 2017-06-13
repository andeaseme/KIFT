/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:49:45 by aphan             #+#    #+#             */
/*   Updated: 2017/06/12 21:55:57 by rpassafa         ###   ########.fr       */
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
	"show me temps",
	NULL
};

/*
**	Set command functions
*/

int					cmd_showmetemps(struct s_con *temp)
{
	system("osx-cpu-temp");
	return (temp->sock_fd);
}

static int			(*g_cmd_func[])(struct s_con *temp) = {
	&cmd_unknown,
	&cmd_seteggtimer,
	&cmd_seteggtimer,
	&cmd_showmetemps
};

int		find_string(char *speech, char const *targets[])
{
	int		i;

	i = 0;
	while (g_cmd_name[i])
	{
		if (NULL != strstr(speech, targets[i]))
			return (i);
		i++;
	}
	return (0);
}

/*
**	Search for a command string within the speech string
**	and returns corresponding cmd_code then runs command in a fork
*/

int				command(char *speech, struct s_con *temp)
{
	int		cmd_code;
	pid_t	f;

	cmd_code = find_string(speech, g_cmd_name);
	f = fork();
	if (0 == f)
		exit(g_cmd_func[cmd_code](temp));
	else if (-1 == f)
		fprintf(stderr, "Failed to create fork for command: %s\n",
			g_cmd_name[cmd_code]);
	return (0);
}
