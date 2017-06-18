/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:50:22 by aphan             #+#    #+#             */
/*   Updated: 2017/06/17 18:27:41 by rmatos           ###   ########.fr       */
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
