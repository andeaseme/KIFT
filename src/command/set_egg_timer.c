/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_egg_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:50:22 by aphan             #+#    #+#             */
/*   Updated: 2017/06/08 14:50:32 by aphan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int			cmd_seteggtimer(int sockfd)
{
	char 		*targets[] = {"hard", "soft", NULL};
	char		*speech;
	clock_t		time;
	clock_t		start;

	start = clock();
	printf("Setting egg timer...\n");
	//system("./SAM/sam 'Setting egg timer. hard or soft boil.'");
	// send_voice(sockfd);
	// speech = receive_string(sockfd);
	// if (find_string(speech, targets))
	// {
	// 	time = 24000;
	// 	printf("four minute timer set\n");
	// 	system("./SAM/sam 'four minute timer set'");
	// }
	// else
	// {
		time = 5000000;
		printf("eight minute timer set\n");
		system("./SAM/sam 'Eight minute timer set'");
	// }
	while (time > clock() - start)
	;
	printf("your egg is ready!\n");
	system("./SAM/sam 'your egg is ready'");
	exit(0);
	return (0);
}