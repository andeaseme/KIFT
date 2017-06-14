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

int		cmd_googlesearch(struct s_con *temp)
{
	char	*query;
	char	*cmd;

	query = strstr(temp->speech, "search ");
	if (query)
		query += 7;
	printf("search query: %s\n", query);
	asprintf(&cmd, "open https://www.google.com/search?q=%s", query);
	system(cmd);
	return (0);
}