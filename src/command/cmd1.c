/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:02:30 by aphan             #+#    #+#             */
/*   Updated: 2017/06/14 19:53:56 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int		cmd_unknown(struct s_con *temp)
{
	static int		i = 0;

	(void)temp;
	i = i % 5;
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
	printf("Unknown command: %s\n", temp->speech);
	i++;
	return (1);
}

int		cmd_googlesearch(struct s_con *temp)
{
	system("open https://google.com");
	(void)temp;
	return (0);
}
