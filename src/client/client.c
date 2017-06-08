/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/07 17:20:14 by rmatos           ###   ########.fr       */
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

int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);

    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    send_file(argv[1], sockfd);
	send_voice(sockfd);

}
