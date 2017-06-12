/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschroed <bschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 00:22:58 by bschroed          #+#    #+#             */
/*   Updated: 2017/06/11 22:10:55 by rpassafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void 	send_string(char *str, int comm_fd)
{
	uint32_t len;

	len = strlen(str);
	write(comm_fd, &len, sizeof(uint32_t));
	write(comm_fd, str, sizeof(char) * len);
}

int main()
{

	char str[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	int i;
	FILE *fp;

	i = 0;
	if (lstat("./Train_src/serv_save/", NULL) == -1)
	{
		mkdir("./Train_src/serv_save/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	if (lstat("./Train_src/serv_save/NUM", NULL) != -1)
	{
		fp = fopen ("./Train_src/serv_save/NUM.txt", "r");
		fscanf (fp, "%d", &i);
		fclose(fp);
	}
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero( &servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(22002);
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	while (1)
	{
		listen(listen_fd, 10);
		comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
		long size;
		read(comm_fd, &size, sizeof(long));
		printf("%li\n", (long)size);
		int wav_fd = open("new_wav.wav", O_RDWR|O_CREAT);
		void *data;
		data = malloc(size);
		read(comm_fd, data, size);
		write(wav_fd, data, size);
		system("chmod 777 new_wav.wav");
		const char *command = audiotostr("new_wav.wav");
		send_string(command ? command : "ERROR", comm_fd);
		system(ft_strjoin("cp new_wav.wav ./Train_src/serv_save/audio_", ft_itoa(i)));
		i++;
		fp = fopen ("./Train_src/serv_save/NUM.txt", "w");
		// system("rm -rf *.wav");
	}
	fprintf(fp, "%d", i);
}
