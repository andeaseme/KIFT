/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 00:22:58 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/13 21:42:04 by rmatos           ###   ########.fr       */
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

int main()
{
	int listen_fd, comm_fd = -1;
	struct sockaddr_in servaddr;
	int i;
	FILE *fp;
	void *data;
	int wav_fd;
	long size;
	pid_t			f;
	int				fstatus;
	int				correct;
	struct s_con	*temp = calloc(1, sizeof(struct s_con));

	i = 0;
	if (lstat("./Train_src/serv_save/", NULL) == -1)
		mkdir("./Train_src/serv_save/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (lstat("./Train_src/serv_save/NUM", NULL) != -1)
	{
		fp = fopen ("./Train_src/serv_save/NUM", "r");
		fscanf (fp, "%d", &i);
		fclose(fp);
	}
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero( &servaddr, sizeof(servaddr));
	temp->servaddr.sin_family = AF_INET;
	temp->servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	temp->servaddr.sin_port = htons(22000);
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	while (1)
	{
		f = fork();
		if (0 == f)
		{
			printf("listen: %d\n",listen(listen_fd, 10));
			comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
			read(comm_fd, &size, sizeof(long));
			printf("read size: %li\n", size);
			wav_fd = open("new_wav.wav", O_RDWR|O_CREAT);
			data = malloc(size);
			read(comm_fd, data, size);
			write(wav_fd, data, size);
			system("chmod 777 new_wav.wav");
			temp->speech = audiotostr("new_wav.wav");
			send_string(temp->speech ? temp->speech : "ERROR", comm_fd);
			read(comm_fd, &correct, sizeof(int));
			if (!correct)
			{
				ft_putendl("HERE SETTING!");
				printf("setting server info...\n");				
				temp->sock_fd = comm_fd;
				temp->servaddr = servaddr;
				ft_putendl("HERE RECEIVING!");
				printf("receiving corrected string...\n");
				temp->speech = receive_string(temp);
				ft_putendl("HERE RECEIVED!");
				printf("received string: %s\n", temp->speech);
				
			}
			if (temp->speech && *temp->speech)
			{
				ft_putendl("HERE SAVING!");
				printf("saving training audio...\n");
				char *str;
				asprintf(&str, "cp new_wav.wav ./Train_src/serv_save/audio_%i.wav", i);
				system(str);
				fp = fopen("./Train_src/serv_save/commands.transcription", "ab+");
				fprintf(fp, "<s> %s </s> (audio_%i)\n", temp->speech, i);
				fclose(fp);
				fp = fopen("./Train_src/serv_save/commands.fileids", "ab+");
				fprintf(fp, "audio_%i\n", i);
				fclose(fp);
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
			}
			close(comm_fd);
		}
	}
}
