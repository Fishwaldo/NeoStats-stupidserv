/* NeoStats - IRC Statistical Services Copyright (c) 1999-2004 NeoStats Group Inc.
** Copyright (c) 1999-2004 Adam Rutter, Justin Hammond
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
#include "dl.h"
#include "stats.h"
#include "ss.h"
#include "talkfilters.h"

/*
 * StupidServ name
 */
static char s_StupidServ[MAXNICK];
static ModUser *ss_bot;

/*
 * Local declarations
 */
static int s_send(User *u, char **av, int ac);
static int s_convert(User *u, char **av, int ac);
static int s_list(User *u, char **av, int ac);
static int s_version(User *u, char **av, int ac);
static int s_about(User *u, char **av, int ac);

static bot_cmd ss_commands[]=
{
	{"SEND",	s_send,		3, 	0,	s_help_send, 	s_help_send_oneline },
	{"CONVERT", s_convert,	1, 	0,	s_help_convert,	s_help_convert_oneline },
	{"LIST",	s_list,		0, 	0,	s_help_list, 	s_help_list_oneline },
	{"VERSION", s_version,	0, 	0,	s_help_version,	s_help_version_oneline },
	{"ABOUT",	s_about,	0, 	0,	s_help_about,	s_help_about_oneline },
	{NULL,		NULL,		0, 	0,					NULL, 			NULL}
};							
/*
 * Module info descriptor
 */
ModuleInfo __module_info = {
    "StupidServ",
    "A Language Translator",
    "1.3",
	__DATE__,
	__TIME__
};

/*
 * Introduce the StupidServ bot onto the network
 */
static int Online(char **av, int ac) 
{
	ss_bot = init_mod_bot(s_StupidServ, "SS", me.name, "A Network Morale Service", 
		services_bot_modes, BOT_FLAG_DEAF, ss_commands, NULL, __module_info.module_name);
    return 1;
};

/*
 * IRC events that StupidServ responds to 
 */
EventFnList __module_events[] = {
    { EVENT_ONLINE,     Online},
    { NULL,     NULL}
};

/*
 * 
 */
int __ModInit(int modnum, int apiver)
{
    strlcpy(s_StupidServ ,"StupidServ" ,MAXNICK);
	return 1;
}

/*
 * 
 */
void __ModFini()
{
};

/*
 * Routine for VERSION 
 */
static int s_version(User *u, char **av, int ac)
{
	SET_SEGV_LOCATION();
	prefmsg(u->nick, s_StupidServ, "\2%s Version Information\2", s_StupidServ);
	prefmsg(u->nick, s_StupidServ, "%s Version: %s Compiled %s at %s", s_StupidServ, 
		__module_info.module_version, __module_info.module_build_date, __module_info.module_build_time);
	prefmsg(u->nick, s_StupidServ, "%s Author Fish <fish@neostats.net>", s_StupidServ);
	prefmsg(u->nick, s_StupidServ, "http://www.neostats.net");
}

/*
 * Routine for VERSION 
 */
static int s_about(User *u, char **av, int ac)
{
	SET_SEGV_LOCATION();
    privmsg_list(u->nick, s_StupidServ, s_help_about);
}

/*
 * Routine for convert
 */
static int s_convert(User *u, char **av, int ac) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();

	/* now find the language they want */
	fp = gtf_filter_lookup(av[2]);
	if (!fp) {
		prefmsg(u->nick, s_StupidServ, "Can not find that Language. /msg %s list for language list", s_StupidServ);
		return;
	}
	inbuf = joinbuf(av, ac, 3);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		prefmsg(u->nick, s_StupidServ, "Translated Text was too Long. Sending shortened text only");
	}
	prefmsg(u->nick, s_StupidServ, "%s", outbuf);
	free(inbuf);
}

/*
 * Routine for list
 */
static int s_list(User *u, char **av, int ac) 
{
	const gtf_filter_t *fp, *fp1;
	int i;

	prefmsg(u->nick, s_StupidServ, "There are %d available Languages", gtf_filter_count());
	fp1 = gtf_filter_list();
	for (i = 0, fp = fp1; i < gtf_filter_count(); i++, fp++) {
		prefmsg(u->nick, s_StupidServ, "Language: %s, Description: %s", fp->name, fp->desc);
	}
	prefmsg(u->nick, s_StupidServ, "End of List.");
}

/*
 * Routine for send
 */
static int s_send(User *u, char **av, int ac) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();
	if (findchan(av[3])) {
		if (UserLevel(u) < NS_ULEVEL_OPER) {
		    prefmsg(u->nick, s_StupidServ, "Only Operators can send to channels.");
	    	}
        } else if (!finduser(av[3])) {
            prefmsg(u->nick, s_StupidServ, "That user cannot be found on IRC. As a result, your message was not sent. Please check the spelling and try again!");
            return;
        }
        /* The user has passed the minimum requirements for input */

	/* now find the language they want */
	fp = gtf_filter_lookup(av[2]);
	if (!fp) {
		prefmsg(u->nick, s_StupidServ, "Can not find that Language. /msg %s list for language list", s_StupidServ);
		return;
	}
	inbuf = joinbuf(av, ac, 4);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		prefmsg(u->nick, s_StupidServ, "Translated Text was too Long. Sending shortened text only");
	}
	prefmsg(av[3], s_StupidServ, "%s is talking %s, and sent this:", u->nick, av[2]);
	prefmsg(av[3], s_StupidServ, "%s", outbuf);
	prefmsg(u->nick, s_StupidServ, "Your Message was sent to %s", av[3]);
	free(inbuf);
}
