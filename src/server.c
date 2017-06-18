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

static void		send_string(char *str, int comm_fd)
{
	uint32_t len;

	printf("sending string: %s\n", str);
	len = strlen(str);
	write(comm_fd, &len, sizeof(uint32_t));
	write(comm_fd, str, sizeof(char) * len);
}

static void		server_save_command_data(char *command, int audio_count)
{
	char	*str;
	FILE	*fp;

	asprintf(&str, "cp new_wav.wav ./Train_src/serv_save/audio_%i.wav",
		audio_count);
	system(str);
	fp = fopen("./Train_src/serv_save/commands.transcription", "ab+");
	fprintf(fp, "<s> %s </s> (audio_%i)\n", command, audio_count);
	fclose(fp);
	fp = fopen("./Train_src/serv_save/commands.fileids", "ab+");
	fprintf(fp, "audio_%i\n", audio_count);
	fclose(fp);
	free(str);
}

static void		receive_file(int comm_fd)
{
	long	size;
	void	*data;
	int		wav_fd;

	read(comm_fd, &size, sizeof(long));
	printf("read size: %li\n", size);
	wav_fd = open("new_wav.wav", O_RDWR | O_CREAT);
	data = malloc(size);
	read(comm_fd, data, size);
	write(wav_fd, data, size);
	system("chmod 777 new_wav.wav");
	free(data);
}

static void		server_fork(struct s_con *conn, int audio_count)
{
	int		comm_fd;
	int		ret;

	printf("listen: %d\n", listen(conn->sock_fd, 10));
	comm_fd = accept(conn->sock_fd, (struct sockaddr*)NULL, NULL);
	receive_file(comm_fd);
	conn->speech = audiotostr("new_wav.wav");
	send_string(conn->speech && *conn->speech
		? conn->speech : "ERROR", comm_fd);
	read(comm_fd, &ret, sizeof(int));
	close(comm_fd);
	if (conn->speech && *conn->speech && 0 == ret)
	{
		server_save_command_data(conn->speech, audio_count);
		exit(0);
	}
	exit(1);
}

int				main(int argc, char **argv)
{
	int				i;
	pid_t			f;
	int				fstatus;
	struct s_con	*conn;

	i = init_server_save();
	conn = init_server(argc > 1 ? atoi(argv[1]) : SERVER_PORT);
	while (1)
	{
		f = fork();
		if (0 == f)
			server_fork(conn, i);
		else if (-1 == f && RED && fprintf(stderr, "Server failed to fork.\n"))
			RESET;
		else
		{
			wait(&fstatus);
			if (WIFSIGNALED(fstatus))
				handle_signal(fstatus);
			else if (WIFEXITED(fstatus) && 0 == fstatus)
				i = increment_audio_count(i);
		}
	}
	return (0);
}
