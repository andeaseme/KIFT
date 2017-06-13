/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/12 22:34:43 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void 	 send_file(char *filename, struct s_con *temp)
{
	int fd;
	char buff[4096];
	int bytes_read;
	struct stat st;

	fd = open(filename, O_RDONLY);
	fstat(fd, &st);
	long size = st.st_size;
	printf("%li\n", size);
	write(temp->sock_fd, &size, sizeof(size));
	bzero(buff, 4096);
	while ((bytes_read = read(fd, &buff, 4096)))
			write(temp->sock_fd, buff, bytes_read);
	close(fd);
}

void 	send_voice(struct s_con *temp)
{
	temp->sock_fd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&temp->servaddr,sizeof (temp->servaddr));
	temp->servaddr.sin_family=AF_INET;
	temp->servaddr.sin_port=htons(22005);
	inet_pton(AF_INET,"127.0.0.1",&(temp->servaddr.sin_addr));
	connect(temp->sock_fd,(struct sockaddr *)&temp->servaddr,sizeof(temp->servaddr));
	system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%");
	send_file("recording.wav", temp);
}

char	*receive_string(struct s_con *temp)
{
	char		buff[4096];
	int			bytes_read;
	uint32_t	len;

	read(temp->sock_fd, &len, sizeof(uint32_t));
	bytes_read = read(temp->sock_fd, &buff, len * (sizeof(char)));
	buff[bytes_read] = '\0';
	// printf("%s\n", "test");
	// printf("%s\n", buff);
	// printf("%s\n", "test");
	return (ft_strdup(buff));
}

int main(void)
{
	char	*speech = NULL;
	struct s_con 	*temp;

	temp = (struct s_con*)malloc(sizeof(struct s_con));
	system("rm -rf *.wav");
	send_voice(temp);
	printf("%s\n", speech = receive_string(temp));
	command(speech, temp);
	free(speech);
	return (0);
}
