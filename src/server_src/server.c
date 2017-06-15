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

static void		handle_signal(int status)
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
		fprintf(stderr, "Server fork exited with unknown signal code: %d\n", status);
	}
	RESET;
}

void 	send_string(char *str, int comm_fd)
{
	uint32_t len;

	len = strlen(str);
	write(comm_fd, &len, sizeof(uint32_t));
	write(comm_fd, str, sizeof(char) * len);
}

int		init_server_save(void)
{
	int		i;
	FILE *fp;

	i = 0;
	if (lstat("./Train_src/serv_save/", NULL) == -1)
	{
		printf("make server save dir\n");
		mkdir("./Train_src/serv_save/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	else if (lstat("./Train_src/serv_save/NUM", NULL) != -1)
	{
		fp = fopen ("./Train_src/serv_save/NUM", "r");
		fscanf (fp, "%d", &i);
		fclose(fp);
	}
	printf("audio count: %i\n", i);
	return (i);
}

struct s_con		*init_server(void)
{
	struct s_con	*conn;

	conn = calloc(1, sizeof(*conn));
	conn->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	conn->servaddr.sin_family = AF_INET;
	conn->servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	conn->servaddr.sin_port = htons(SERVER_PORT);
    bind(conn->sock_fd,
		(struct sockaddr *)&conn->servaddr, sizeof(conn->servaddr));
	printf("server initialized\n");
	return (conn);
}

void	server_save_command_data(char *command, int audio_count)
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
}

int main()
{
	int					comm_fd = -1;
	int i;
	FILE *fp;
	void *data;
	int wav_fd;
	long size;
	pid_t		f;
	int			fstatus;
	int			correct;
	struct s_con	*conn;

	i = init_server_save();
	conn = init_server();
	while (1)
	{
		f = fork();
		if (0 == f)
		{
			printf("listen: %d\n",listen(conn->sock_fd, 10));
			comm_fd = accept(conn->sock_fd, (struct sockaddr*) NULL, NULL);
			read(comm_fd, &size, sizeof(long));
			printf("read size: %li\n", size);
			wav_fd = open("new_wav.wav", O_RDWR|O_CREAT);
			data = malloc(size);
			read(comm_fd, data, size);
			write(wav_fd, data, size);
			system("chmod 777 new_wav.wav");
			conn->speech = audiotostr("new_wav.wav");
			send_string(conn->speech ? conn->speech : "ERROR", comm_fd);
			read(comm_fd, &correct, sizeof(int));
			if (conn->speech && *conn->speech && correct)
			{
				server_save_command_data(conn->speech, i);
				exit(0);
			}
			exit(1);
		}
		else if (-1 == f)
		{
			RED;
			fprintf(stderr, "Server failed to fork.\n");
			RESET;
		}
		else
		{
			wait(&fstatus);
			if (WIFSIGNALED(fstatus))
				handle_signal(fstatus);
			else if (WIFEXITED(fstatus) && 0 == fstatus)
			{
				i++;
				fp = fopen ("./Train_src/serv_save/NUM", "w");
				fprintf(fp, "%d", i);
				fclose(fp);
				printf("audio count: %i\n", i);
			}
			close(comm_fd);
		}
	}
}
