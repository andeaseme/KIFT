/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/15 19:19:17 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	send_file(char *filename, struct s_con *conn)
{
	int			fd;
	char		buff[4096];
	int			bytes_read;
	struct stat	st;
	long		size;

	fd = open(filename, O_RDONLY);
	fstat(fd, &st);
	size = st.st_size;
	printf("%li\n", size);
	write(conn->sock_fd, &size, sizeof(size));
	bzero(buff, 4096);
	while ((bytes_read = read(fd, &buff, 4096)))
		write(conn->sock_fd, buff, bytes_read);
	close(fd);
}

void	send_voice(struct s_con *conn)
{
	connect(conn->sock_fd, (struct sockaddr *)&conn->servaddr,
		sizeof(conn->servaddr));
	system("rec -c 1 -r 16000 -b 16 recording.wav \
		gain +5 silence 1 0.1 3% 1 2.0 3%");
	send_file("recording.wav", conn);
}

char	*receive_string(struct s_con *conn)
{
	char		buff[4096];
	int			bytes_read;
	uint32_t	len;

	read(conn->sock_fd, &len, sizeof(uint32_t));
	bytes_read = read(conn->sock_fd, &buff, len * (sizeof(char)));
	buff[bytes_read] = '\0';
	printf("received string: %s\n", buff);
	return (ft_strdup(buff));
}

int		main(int argc, char **argv)
{
	int				ret;
	struct s_con	*conn;

	conn = (struct s_con*)calloc(1, sizeof(struct s_con));
	conn->address = argc > 1 ? argv[1] : SERVER_ADDRESS;
	conn->port_num = argc > 2 ? atoi(argv[2]) : SERVER_PORT;
	ret = 0;
	while (0 == ret && 5 > conn->i)
	{
		conn->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
		bzero(&conn->servaddr, sizeof(conn->servaddr));
		conn->servaddr.sin_family = AF_INET;
		conn->servaddr.sin_port = htons(conn->port_num);
		inet_pton(AF_INET, conn->address, &(conn->servaddr.sin_addr));
		system("rm -rf *.wav");
		printf("sending voice through port: %i\n", conn->port_num);
		send_voice(conn);
		printf("%s\n", conn->speech = receive_string(conn));
		ret = command(conn->speech, conn);
		write(conn->sock_fd, &ret, sizeof(int));
		free(conn->speech);
		conn->speech = NULL;
		conn->i++;
	}
	return (0);
}
