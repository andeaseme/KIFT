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
	(void)temp->sock_fd;
	return (0);
}

int		cmd_googlesearch(struct s_con *temp)
{
	system("open https://google.com");
	(void)temp;
	return (0);
}
