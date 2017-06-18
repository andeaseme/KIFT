/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:50:22 by aphan             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/06/17 22:24:21 by rmatos           ###   ########.fr       */
=======
/*   Updated: 2017/06/17 22:07:56 by rpassafa         ###   ########.fr       */
>>>>>>> 7c1992c052db7fe3501e68045eb52b9f5c9ac1fc
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
}
