/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:02:30 by aphan             #+#    #+#             */
/*   Updated: 2017/06/18 14:38:53 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int		cmd_unknown(void *cmd)
{
	int		i;

	i = *((int*)cmd);
	if (0 == i)
		system("play resources/cantdo.wav");
	else if (1 == i)
		system("play resources/quite_like_this.wav");
	else if (2 == i)
		system("play resources/human_error.wav");
	else if (3 == i)
		system("play resources/stop2.wav");
	else if (4 == i)
		system("play resources/goodbye.wav");
	return (1);
}

int		cmd_googlesearch(void *cmd)
{
	(void)cmd;
	system("say opening google");
	system("open https://google.com");
	return (0);
}

int		cmd_sendemail(void *cmd)
{
	(void)cmd;
	system("say opening gee-mail");
	system("open https://gmail.com");
	return (0);
}

int		cmd_showmetemps(void *cmd)
{
	(void)cmd;
	system("say here is the c-p-u temperature");
	system("./osx-cpu-temp/osx-cpu-temp");
	return (0);
}

int		cmd_googlemusic(void *cmd)
{
	(void)cmd;
	system("say opening google music");
	system("open https://music.google.com/");
	return (0);
}
