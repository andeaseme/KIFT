/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/12 18:46:15 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	error(char *msg)
{
	perror(msg);
	exit(0);
}

void 	 send_file(char *filename, int sock_fd)
{
	int fd;
	char buff[4096];
	int bytes_read;
	struct stat st;

	fd = open(filename, O_RDONLY);
	fstat(fd, &st);
	long size = st.st_size;
	printf("%li\n", size);
	write(sock_fd, &size, sizeof(size));
	bzero(buff, 4096);
	while ((bytes_read = read(fd, &buff, 4096)))
			write(sock_fd, buff, bytes_read);
	close(fd);
}

void 	send_voice(int sock_fd)
{
	system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%");
	send_file("recording.wav", sock_fd);
}

char	*receive_string(int sock_fd)
{
	char		buff[4096];
	int			bytes_read;
	uint32_t	len;

	read(sock_fd, &len, sizeof(uint32_t));
	bytes_read = read(sock_fd, &buff, len * (sizeof(char)));
	buff[bytes_read] = '\0';
	printf("%s\n", "test");
	printf("%s\n", buff);
	printf("%s\n", "test");
	return (ft_strdup(buff));
}

int main(void)
{
    int sockfd;
    struct sockaddr_in servaddr;
	char	*speech = NULL;

	system("rm -rf *.wav");
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22002);

    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	send_voice(sockfd);
	printf("%s\n", speech = receive_string(sockfd));
	command(speech, sockfd);
	free(speech);
	return (0);
}
