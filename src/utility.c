/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 22:26:16 by aphan             #+#    #+#             */
/*   Updated: 2017/06/13 22:26:32 by aphan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void 	send_string(char *str, int comm_fd)
{
	uint32_t len;

	len = strlen(str);
	write(comm_fd, &len, sizeof(uint32_t));
	write(comm_fd, str, sizeof(char) * len);
}

char	*receive_string(struct s_con *temp)
{
	char		buff[4096];
	int			bytes_read;
	uint32_t	len;

	read(temp->sock_fd, &len, sizeof(uint32_t));
	bytes_read = read(temp->sock_fd, &buff, len * (sizeof(char)));
	buff[bytes_read] = '\0';
	printf("received string: %s\n", buff);
	return (ft_strdup(buff));
}
