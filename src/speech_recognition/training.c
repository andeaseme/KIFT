/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphan <aphan@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 16:38:57 by aphan             #+#    #+#             */
/*   Updated: 2017/06/11 16:39:09 by aphan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	training(char *speech, char *audiopath)
{
	 char	buf[2048]
	 
	 ft_strcat_multi(buf, BW,
		" -hmmdir ", HHMDIR,
		" -moddeffn ", HHMDIR, "/mdef.txt",
		" -ts2cbfn .ptm.",
		" -feat 1s_c_d_dd",
		" -svspec 0-12/13-25/26-38",
		" -cmn current",
		" -agc none",
		" -dictfn cmudict-en-us.dict",
		" -ctlfn arctic20.fileids",
		" -lsnfn arctic20.transcription",
		" -accumdir .",
		NULL);
}