/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:02:30 by aphan             #+#    #+#             */
/*   Updated: 2017/06/12 21:56:11 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

int		cmd_unknown(struct s_con *temp)
{
	(void)temp->sock_fd;
	return (0);
}

int		cmd_opengoogle(struct s_con *temp)
{
	(void)temp;
	system("./SAM/sam 'open-ing google'");
	system("open https://www.google.com/");
	return (0);
}