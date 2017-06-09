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
	printf("Setting egg timer...\n");
	system("./SAM/sam 'hard or soft'");
	send_voice(sockfd);
	//receive_string(sockfd);
}