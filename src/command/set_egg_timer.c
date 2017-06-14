/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_egg_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:50:22 by aphan             #+#    #+#             */
/*   Updated: 2017/06/13 20:03:56 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int			cmd_seteggtimer(struct s_con *temp)
{
	// char const	*targets[] = {"hard", "soft", NULL};
	// char		*speech;
	clock_t		time;
	clock_t		start;

	start = clock();
	time = 5000000;
	if (temp)
		;
	printf("eight minute timer set\n");
	system("./SAM/sam 'Eight minute timer set'");
	while (time > clock() - start)
	;
	printf("your egg is ready!\n");
	system("./SAM/sam 'your egg is ready'");
	exit(0);
	return (0);
}
