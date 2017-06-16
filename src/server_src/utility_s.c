/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
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
		fprintf(stderr, "Server fork exited with SEGV\n");
	}
	else if (status == SIGBUS)
	{
		BOLD;
		fprintf(stderr, "Server fork exited with BUSE\n");
	}
	else
	{
		fprintf(stderr, "Server fork exited signal code: %d\n", status);
	}
}

int					init_server_save(void)
{
	int		i;
	FILE	*fp;

	i = 0;
	if (lstat("./Train_src/serv_save/", NULL) == -1)
	{
		printf("make server save dir\n");
		mkdir("./Train_src/serv_save/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	else if (lstat("./Train_src/serv_save/NUM", NULL) != -1)
	{
		fp = fopen("./Train_src/serv_save/NUM", "r");
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
	fp = fopen("./Train_src/serv_save/NUM", "w");
	fprintf(fp, "%d", ac);
	fclose(fp);
	printf("audio count: %i\n", ac);
	return (ac);
}
