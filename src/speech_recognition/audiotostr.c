/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audiotostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:45:49 by aphan             #+#    #+#             */
/*   Updated: 2017/06/14 16:40:19 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"
#include <pocketsphinx.h>

char    *audiotostr(char *audiopath)
{
    ps_decoder_t    *ps;
    cmd_ln_t        *config;
    FILE            *fh;
    int             rv;
    size_t          nsamp;
    int16           buf[READ_SIZE];
    char const      *hyp;
    int32           score;


	system("play new_wav.wav");
    if (NULL == (config = cmd_ln_init(NULL, ps_args(), TRUE,
            "-hmm", HMMDIR,
            "-lm", LANGDIR,
            "-dict", DICTDIR,
            NULL)))
    {
		fprintf(stderr, "Failed to create config object, see log for  details\n");
		return (NULL);
    }
    if (NULL == (ps = ps_init(config)))
    {
		fprintf(stderr, "Failed to create recognizer, see log for  details\n");
        cmd_ln_free_r(config);
		return (NULL);
	}
    if (NULL == audiopath || NULL == (fh = fopen(audiopath, "rb")))
    {
        fprintf(stderr, "Unable to open input file %s\n", audiopath);
        cmd_ln_free_r(config);
       	ps_free(ps);
		return (NULL);
    }
    rv = ps_start_utt(ps);
    while (0 == feof(fh))
    {
        nsamp = fread(buf, sizeof(int16), READ_SIZE, fh);
        rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
    }
    fflush(stdout);
    rv = ps_end_utt(ps);
    hyp = ps_get_hyp(ps, &score);
    fclose(fh);
    cmd_ln_free_r(config);
    ps_free(ps);
    printf("audiotostr returning: '%s'\n", hyp);
    return(ft_strdup(hyp));
}
