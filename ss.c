/* NeoStats - IRC Statistical Services Copyright (c) 1999-2004 NeoStats Group Inc.
** Copyright (c) 1999-2004 Adam Rutter, Justin Hammond, Mark Hetherington
** http://www.neostats.net/
**
**  Portions Copyright (c) 2000-2001 ^Enigma^
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
**  USA
**
** NeoStats CVS Identification
** $Id: ss.c,v 1.4 2003/05/22 14:05:09 fishwaldo Exp $
*/

#include <stdio.h>
#ifndef WIN32
#include "modconfig.h"
#endif
#include "neostats.h"
#include "ss.h"
#include "talkfilters.h"

/** Bot pointer */
static Bot *ss_bot;

struct ss_cfg { 
	char user[MAXUSER];
	char host[MAXHOST];
	char realname[MAXREALNAME];
} ss_cfg;

/*
 * Local declarations
 */
static int s_send (CmdParams* cmdparams);
static int s_convert (CmdParams* cmdparams);
static int s_list (CmdParams* cmdparams);

static bot_cmd ss_commands[]=
{
	{"SEND",	s_send,		3, 	0,	s_help_send, 	s_help_send_oneline },
	{"CONVERT", s_convert,	2, 	0,	s_help_convert,	s_help_convert_oneline },
	{"LIST",	s_list,		0, 	0,	s_help_list, 	s_help_list_oneline },
	{NULL,		NULL,		0, 	0,					NULL, 			NULL}
};							

/** Copyright info */
const char *ss_copyright[] = {
	"Copyright (c) 1999-2004, NeoStats",
	"http://www.neostats.net/",
	NULL
};

/** Module info */
ModuleInfo module_info = {
	"StupidServ",
	"A Language Translator",
	ss_copyright,
	s_about,
	NEOSTATS_VERSION,
	"3,0",
	__DATE__,
	__TIME__,
	0,
	0,
};

/** BotInfo */
static BotInfo ss_botinfo = 
{
	"StupidServ", 
	"StupidServ1", 
	"SS", 
	BOT_COMMON_HOST, 
	"A Language Translator", 	
	BOT_FLAG_SERVICEBOT|BOT_FLAG_DEAF, 
	ss_commands, 
	NULL,
};

/*
 * Introduce the StupidServ bot onto the network
 */
int ModSynch (void)
{
	ss_bot = AddBot (&ss_botinfo);
	if (!ss_bot) {
		return NS_FAILURE;
	}
	return NS_SUCCESS;
};

/*
 * 
 */
int ModInit( Module *mod_ptr )
{
	return NS_SUCCESS;
}

/*
 * 
 */
void ModFini( void ) 
{
};

/*
 * Routine for convert
 */
static int s_convert (CmdParams* cmdparams) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();

	/* now find the language they want */
	fp = gtf_filter_lookup(cmdparams->av[0]);
	if (!fp) {
		irc_prefmsg (ss_bot, cmdparams->source, "Can not find that Language. /msg %s list for language list", ss_bot->name);
		return NS_SUCCESS;
	}
	inbuf = joinbuf(cmdparams->av, cmdparams->ac, 1);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		irc_prefmsg (ss_bot, cmdparams->source, "Translated Text was too Long. Sending shortened text only");
	}
	irc_prefmsg (ss_bot, cmdparams->source, "%s", outbuf);
	free(inbuf);
	return NS_SUCCESS;
}

/*
 * Routine for list
 */
static int s_list (CmdParams* cmdparams) 
{
	const gtf_filter_t *fp, *fp1;
	int i;

	irc_prefmsg (ss_bot, cmdparams->source, "There are %d available Languages", gtf_filter_count());
	fp1 = gtf_filter_list();
	for (i = 0, fp = fp1; i < gtf_filter_count(); i++, fp++) {
		irc_prefmsg (ss_bot, cmdparams->source, "Language: %s, Description: %s", fp->name, fp->desc);
	}
	irc_prefmsg (ss_bot, cmdparams->source, "End of List.");
	return NS_SUCCESS;
}

/*
 * Routine for send
 */
static int s_send (CmdParams* cmdparams) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();
	if (FindChannel(cmdparams->av[1])) {
		if (UserLevel(cmdparams->source) < NS_ULEVEL_OPER) {
		    irc_prefmsg (ss_bot, cmdparams->source, "Only Operators can send to channels.");
	    	return NS_SUCCESS;
    	}
    } else if (!FindUser(cmdparams->av[1])) {
        irc_prefmsg (ss_bot, cmdparams->source, "That user cannot be found on IRC. As a result, your message was not sent. Please check the spelling and try again!");
       	return NS_SUCCESS;
    }
    /* The user has passed the minimum requirements for input */

	/* now find the language they want */
	fp = gtf_filter_lookup(cmdparams->av[0]);
	if (!fp) {
		irc_prefmsg (ss_bot, cmdparams->source, "Can not find that Language. /msg %s list for language list", ss_bot->name);
		return NS_SUCCESS;
	}
	inbuf = joinbuf(cmdparams->av, cmdparams->ac, 2);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		irc_prefmsg (ss_bot, cmdparams->source, "Translated Text was too Long. Sending shortened text only");
	}
	irc_prefmsg (ss_bot, FindUser(cmdparams->av[1]), "%s is talking %s, and sent this:", cmdparams->source->name, cmdparams->av[0]);
	irc_prefmsg (ss_bot, FindUser(cmdparams->av[1]), "%s", outbuf);
	irc_prefmsg (ss_bot, cmdparams->source, "Your Message was sent to %s", cmdparams->av[1]);
	free(inbuf);
	return NS_SUCCESS;
}
