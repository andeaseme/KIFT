/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 00:22:58 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/14 19:54:40 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void				handle_signal(int status)
{
	RED;
	if (status == SIGSEGV)
	{
		INVERSE;
		fprintf(stderr, "Fork exited with SEGV\n");
	}
	else if (status == SIGBUS)
	{
		BOLD;
		fprintf(stderr, "Fork exited with BUSE\n");
	}
	else
	{
		fprintf(stderr, "Fork exited with signal code: %d\n", status);
	}
	RESET;
}

int					init_server_save(void)
{
	int				i;
	FILE			*fp;
	struct stat		buf;

	i = 0;
	if (lstat("./server_history/", &buf) == -1)
	{
		printf("make server save dir\n");
		mkdir("./server_history/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	if (lstat("./server_history/NUM", &buf) != -1)
	{
		fp = fopen("./server_history/NUM", "r");
		fscanf(fp, "%d", &i);
		fclose(fp);
	}
	printf("audio count: %i\n", i);
	return (i);
}

struct s_con		*init_server(int port_num)
{
	struct s_con	*conn;

	conn = calloc(1, sizeof(*conn));
	conn->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	conn->servaddr.sin_family = AF_INET;
	conn->servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	conn->servaddr.sin_port = htons(port_num);
	bind(conn->sock_fd,
		(struct sockaddr *)&conn->servaddr, sizeof(conn->servaddr));
	printf("server initialized to port: %i\n", port_num);
	return (conn);
}

int					increment_audio_count(int ac)
{
	FILE *fp;

	ac++;
	fp = fopen("./server_history/NUM", "w");
	fprintf(fp, "%d", ac);
	fclose(fp);
	printf("audio count: %i\n", ac);
	return (ac);
}

void				send_history(int comm_fd)
{
	int				fd;
	char			buff[4096];
	int				bytes_read;
	struct stat		st;
	long			size;

	printf("sending history...");
	fd = open("./server_history/commands.transcription", O_RDONLY);
	bzero(&st, sizeof(st));
	fstat(fd, &st);
	size = st.st_size;
	write(comm_fd, &size, sizeof(size));
	bzero(buff, 4096);
	printf("size: %li\n", size);
	while ((bytes_read = read(fd, &buff, 4096)))
	{
		write(comm_fd, buff, bytes_read);
		printf("%s", buff);
	}
	close(fd);
	exit(1);
}
