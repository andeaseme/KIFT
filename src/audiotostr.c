/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audiotostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:45:49 by aphan             #+#    #+#             */
/*   Updated: 2017/06/18 16:32:31 by rmatos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

char  	*audiotostr_util(char *audiopath, t_wavtoa *vars)
{
	if (NULL == audiopath || NULL == (vars->fh = fopen(audiopath, "rb")))
	{
		fprintf(stderr, "Unable to open input file %s\n", audiopath);
		cmd_ln_free_r(vars->config);
		ps_free(vars->ps);
		return (NULL);
	}
	vars->rv = ps_start_utt(vars->ps);
	while (0 == feof(vars->fh))
	{
		vars->nsamp = fread(vars->buf, sizeof(int16), READ_SIZE, vars->fh);
		vars->rv = ps_process_raw(vars->ps,
			vars->buf, vars->nsamp, FALSE, FALSE);
	}
	fflush(stdout);
	vars->rv = ps_end_utt(vars->ps);
	vars->hyp = ps_get_hyp(vars->ps, &vars->score);
	fclose(vars->fh);
	cmd_ln_free_r(vars->config);
	ps_free(vars->ps);
	printf("audiotostr returning: '%s'\n", vars->hyp);
	return (vars->hyp ? ft_strdup(vars->hyp) : 0);
}

char	*audiotostr(char *audiopath)
{
	t_wavtoa vars;

	system("play new_wav.wav");
	if (NULL == (vars.config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", HMMDIR,
			"-lm", LANGDIR,
			"-dict", DICTDIR,
			NULL)))
	{
		fprintf(stderr,
			"Failed to create config object, see log for  details\n");
		return (NULL);
	}
	if (NULL == (vars.ps = ps_init(vars.config)))
	{
		fprintf(stderr, "Failed to create recognizer, see log for  details\n");
		cmd_ln_free_r(vars.config);
		return (NULL);
	}
	return (audiotostr_util(audiopath, &vars));
}
