/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:50:38 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/13 17:27:26 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

bool	g_training = 0;

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
	temp->servaddr.sin_port=htons(22000);
	inet_pton(AF_INET,"127.0.0.1",&(temp->servaddr.sin_addr));
	connect(temp->sock_fd,(struct sockaddr *)&temp->servaddr,sizeof(temp->servaddr));
	system("rec -c 1 -r 16000 -b 16 recording.wav gain +5 silence 1 0.1 3% 1 2.0 3%");
	send_file("recording.wav", temp);
}

int main(int argc, char **argv)
{
	struct s_con 	*temp;
	int				correct;
	char			buff;
	char			cmd[1024];

	if (1 < argc && 0 == strcmp(argv[1], "-t"))
	{
		g_training = 1;
	}
	temp = (struct s_con*)malloc(sizeof(struct s_con));
	temp->speech = NULL;
	system("rm -rf *.wav");
	send_voice(temp);
	printf("%s\n", temp->speech = receive_string(temp));
	ft_putstr("correct? [y/n]");
	read(0, &buff, sizeof(char));
	correct = (buff == 'y') ? 1 : 0;
	read(1, &buff, sizeof(char)); //won't fgets below without this
	if (!correct)
	{
		free(temp->speech);
		ft_putstr("Type what you said: ");
		fgets(cmd, 1024, stdin);
		temp->speech = ft_strdup(cmd);
		printf("New command: %s\n", temp->speech);
	}
	write(temp->sock_fd, &correct, sizeof(int));
	if (!correct)
	{
		send_string(temp->speech, temp->sock_fd);
	}
	command(temp->speech, temp);
	free(temp->speech);
	return (0);
}
