/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/14 19:54:33 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void 	 send_file(char *filename, struct s_con *conn)
{
	int fd;
	char buff[4096];
	int bytes_read;
	struct stat st;

	fd = open(filename, O_RDONLY);
	fstat(fd, &st);
	long size = st.st_size;
	printf("%li\n", size);
	write(conn->sock_fd, &size, sizeof(size));
	bzero(buff, 4096);
	while ((bytes_read = read(fd, &buff, 4096)))
			write(conn->sock_fd, buff, bytes_read);
	close(fd);
}

void 	send_voice(struct s_con *conn, int port_num)
{
	printf("sending voice through port: %i\n", port_num);
	conn->sock_fd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&conn->servaddr,sizeof (conn->servaddr));
	conn->servaddr.sin_family=AF_INET;
	conn->servaddr.sin_port=htons(port_num);
	inet_pton(AF_INET,"127.0.0.1",&(conn->servaddr.sin_addr));
	connect(conn->sock_fd,(struct sockaddr *)&conn->servaddr,sizeof(conn->servaddr));
	system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%");
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

int main(int argc, char **argv)
{
	struct s_con 	*conn;
	int				correct;
	char			buff;

	conn = (struct s_con*)malloc(sizeof(struct s_con));
	conn->speech = NULL;
	system("rm -rf *.wav");
	send_voice(conn, argc > 1 ? atoi(argv[1]) : SERVER_PORT);
	printf("%s\n", conn->speech = receive_string(conn));
	ft_putstr("correct? [y/n]");
	read(0, &buff, sizeof(char));
	correct = (buff == 'y') ? 1 : 0;
	write(conn->sock_fd, &correct, sizeof(int));
	command(conn->speech, conn);
	free(conn->speech);
	return (0);
}
