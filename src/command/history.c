/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 22:11:56 by aphan             #+#    #+#             */
/*   Updated: 2017/06/17 22:11:59 by aphan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

static void		request_history(struct s_con *conn)
{
	char		*key;
	long		size;

	connect(conn->sock_fd, (struct sockaddr *)&conn->servaddr,
		sizeof(conn->servaddr));
	key = HISTORY_KEY;
	size = strlen(key);
	write(conn->sock_fd, &size, sizeof(size));
	write(conn->sock_fd, key, size);
}

static void		receive_history(struct s_con *conn)
{
	char		*history;
	char		buf;
	uint32_t	len;
	uint32_t	i;
	uint32_t	j;

	printf("receiving history\n");
	i = 0;
	j = 0;
	read(conn->sock_fd, &len, sizeof(uint32_t));
	history = calloc(len, sizeof(char));
	history[len] = 0;
	printf("history size: %u\n", len);
	sleep(1);
	while (i < len)
	{
		read(conn->sock_fd, &buf, 1);
		if (0 == i && 0 == buf && j++ < len)
			continue ;
		history[i] = buf;
		i++;
	}
	printf("received history:\n%s\n", history);
	free(history);
}

static void		finish_command(int sock_fd)
{
	int		ret;

	ret = 1;
	write(sock_fd, &ret, sizeof(int));
}

int				cmd_history(void *cmd)
{
	int				port_num;
	struct s_con	*conn;

	conn = (struct s_con*)cmd;
	finish_command(conn->sock_fd);
	port_num = conn->port_num;
	conn->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&conn->servaddr, sizeof(conn->servaddr));
	conn->servaddr.sin_family = AF_INET;
	conn->servaddr.sin_port = htons(port_num);
	inet_pton(AF_INET, "127.0.0.1", &(conn->servaddr.sin_addr));
	printf("sending history request through port: %i\n", port_num);
	request_history(conn);
	receive_history(conn);
	return (0);
}
