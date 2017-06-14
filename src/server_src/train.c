#include "kift.h"

void 	train(void)
{
	char *str;

	system("mv ROB Train_src/serv_save/en-us");
	chdir("Train_src/serv_save");
	system("sphinx_fe -argfile en-us/feat.params -samprate 16000 -c commands.fileids -di . -do . -ei wav -eo mfc -mswav yes");
	system("pocketsphinx_mdef_convert -text en-us/mdef en-us/mdef.txt");
	asprintf(&str, "%s -hmmdir en-us -moddeffn en-us/mdef.txt -ts2cbfn .ptm. -feat 1s_c_d_dd -svspec 0-12/13-25/26-38 -cmn current -agc none -dictfn cmudict-en-us.dict -ctlfn commands.fileids -lsnfn commands.transcription -accumdir .", BW);
	system(str);
	asprintf(&str, "%s -meanfn en-us/means -varfn en-us/variances -outmllrfn mllr_matrix -accumdir .", MLLR);
	system(str);
	system("cp -a en-us en-us-adapt");
	asprintf(&str, "%s -moddeffn en-us/mdef.txt -ts2cbfn .ptm. -meanfn en-us/means -varfn en-us/variances -mixwfn en-us/mixture_weights -tmatfn en-us/transition_matrices -accumdir . -mapmeanfn en-us-adapt/means -mapvarfn en-us-adapt/variances -mapmixwfn en-us-adapt/mixture_weights -maptmatfn en-us-adapt/transition_matrices", MAP);
	system(str);
	system("mv en-us-adapt ../../ROB");
	system("rm -rf en-us");
}
