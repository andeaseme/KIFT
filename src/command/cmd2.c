/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:50:22 by aphan             #+#    #+#             */
/*   Updated: 2017/06/17 23:24:19 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int			cmd_seteggtimer(void *cmd)
{
	clock_t		time;
	clock_t		start;

	(void)cmd;
	start = clock();
	time = 8 * 60 * CLOCKS_PER_SEC;
	printf("eight minute timer set\n");
	system("./SAM/sam 'Eight min-ut timer set'");
	while (time > clock() - start)
		;
	printf("your egg is ready!\n");
	system("./SAM/sam 'your egg is ready'");
	exit(0);
	return (0);
}

int			cmd_showsysteminfo(void *cmd)
{
	(void)cmd;
	system("./neofetch/neofetch");
	return (0);
}

int			cmd_whoami(void *cmd)
{
	(void)cmd;
	system("whoami");
	system("whoami | say");
	return (0);
}

int			cmd_whereami(void *cmd)
{
	(void)cmd;
	system("hostname");
	return (0);
}

int			cmd_lights(void *cmd)
{
	FILE *fp;
	int	on;

	(void)cmd;
	if ((fp = fopen("lights", "r+")) == NULL)
	{
		system("echo 1 > lights");
		system("say lights are on");
		return (0);
	}
	fscanf(fp, "%i", &on);
	fclose(fp);
	system("rm -rf lights");
	if (on)
	{
		system("echo 0 > lights");
		system("say lights are off");
	}
	else
	{
		system("echo 1 > lights");
		system("say lights are on");
	}
	return (0);

}
