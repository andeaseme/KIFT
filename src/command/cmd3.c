#include "kift.h"

int		cmd_weather(void *cmd)
{
	(void)cmd;
	system("curl wttr.in");
	return (0);
}
