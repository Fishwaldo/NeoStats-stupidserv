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
#include "s_help.c"
#include "talkfilters.h"

/*
 * StupidServ name
 */
static char s_StupidServ[MAXNICK];

/*
 * Local declarations
 */
static void s_send(User *u, char **cmd, int ac);
static void s_convert(User *u, char **cmd, int ac);
static void s_list(User *u);
static void s_version(User *u);

/*
 * Module info descriptor
 */
ModuleInfo __module_info = {
    "StupidServ",
    "A Language Translator",
    "1.1",
	__DATE__,
	__TIME__
};

/*
 * Message processor for StupidServ
 */
int __BotMessage(char *origin, char **av, int ac)
{
    User *u;
    u = finduser(origin);
	if (!u) /* User not found */
		return 1;

    if (!strcasecmp(av[1], "HELP")) {
		if (ac <= 2) {
			privmsg_list(u->nick, s_StupidServ, s_help);
			privmsg_list(u->nick, s_StupidServ, s_help_on_help);
			return 1;
		} else if (!strcasecmp(av[2], "SEND")) {
			privmsg_list(u->nick, s_StupidServ, s_help_send);
			return 1;
		} else if (!strcasecmp(av[2], "CONVERT")) {
			privmsg_list(u->nick, s_StupidServ, s_help_convert);
			return 1;
		} else if (!strcasecmp(av[2], "LIST")) {
			privmsg_list(u->nick, s_StupidServ, s_help_list);
			return 1;
		} else if (!strcasecmp(av[2], "ABOUT")) {
			privmsg_list(u->nick, s_StupidServ, s_help_about);
			return 1;
		} else if (!strcasecmp(av[2], "VERSION")) {
			privmsg_list(u->nick, s_StupidServ, s_help_version);
			return 1;
		} else {
			prefmsg(u->nick, s_StupidServ,
				"Unknown Help Topic: \2%s\2", av[2]);
		}
        return 1;
    } else if (!strcasecmp(av[1], "SEND")) {
         if (ac < 5) {
             prefmsg(u->nick, s_StupidServ, "Syntax: /msg %s SEND <lang> <nick|channel> <text>", s_StupidServ);
             prefmsg(u->nick, s_StupidServ, "For additional help: /msg %s HELP", s_StupidServ);
             return -1;
         }
         s_send(u, av, ac);
    } else if (!strcasecmp(av[1], "CONVERT")) {
        if (ac < 3) {
        	prefmsg(u->nick, s_StupidServ, "Syntax: /msg %s CONVERT <text>", s_StupidServ);
            prefmsg(u->nick, s_StupidServ, "For additional help: /msg %s HELP", s_StupidServ);
            return -1;
        }
    	s_convert(u, av, ac);
    } else if (!strcasecmp(av[1], "LIST")) {
        s_list(u);
    } else if (!strcasecmp(av[1], "VERSION")) {
        chanalert(s_Services,"%s Wanted to know the current version information for %s",u->nick,s_StupidServ);
        s_version(u);
    } else if (!strcasecmp(av[1], "ABOUT") || !strcasecmp(av[1], "CREDITS")) {
        privmsg_list(u->nick, s_StupidServ, s_about);
    } else {
        chanalert(s_Services, "%s requested the unknown command of: %s", u->nick, av[1]);
        prefmsg(u->nick, s_StupidServ, "Unknown Command: \2%s\2, perhaps you need some HELP?", av[1]);
    }
    return 1;
}

/*
 * Introduce the StupidServ bot onto the network
 */
static int Online(char **av, int ac) 
{
    if (init_bot(s_StupidServ,"SS",me.name,"A Network Morale Service", "+oS", __module_info.module_name) == -1 ) {
        /* Nick was in use */
        strlcat(s_StupidServ, "_", MAXNICK);
        init_bot(s_StupidServ,"SS",me.name,"A Network Morale Service", "+oS", __module_info.module_name);
    }
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
static void s_version(User *u)
{
	SET_SEGV_LOCATION();
	prefmsg(u->nick, s_StupidServ, "\2%s Version Information\2", s_StupidServ);
	prefmsg(u->nick, s_StupidServ, "%s Version: %s Compiled %s at %s", s_StupidServ, 
		__module_info.module_version, __module_info.module_build_date, __module_info.module_build_time);
	prefmsg(u->nick, s_StupidServ, "%s Author Fish <fish@neostats.net>", s_StupidServ);
	prefmsg(u->nick, s_StupidServ, "http://www.neostats.net");
}

/*
 * Routine for convert
 */
static void s_convert(User *u, char **cmd, int ac) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();

	/* now find the language they want */
	fp = gtf_filter_lookup(cmd[2]);
	if (!fp) {
		prefmsg(u->nick, s_StupidServ, "Can not find that Language. /msg %s list for language list", s_StupidServ);
		return;
	}
	inbuf = joinbuf(cmd, ac, 3);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		prefmsg(u->nick, s_StupidServ, "Translated Text was too Long. Sending shortened text only");
	}
	prefmsg(u->nick, s_StupidServ, "%s", outbuf);
	free(inbuf);
}

/*
 * Routine for list
 */
static void s_list(User *u) 
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
static void s_send(User *u, char **cmd, int ac) 
{
	const gtf_filter_t *fp;
	char *inbuf;
	char outbuf[450];
        
	SET_SEGV_LOCATION();

	if (findchan(cmd[3])) {
		if (UserLevel(u) < NS_ULEVEL_OPER) {
		    prefmsg(u->nick, s_StupidServ, "Only Operators can send to channels.");
	    	}
        } else if (!finduser(cmd[3])) {
            prefmsg(u->nick, s_StupidServ, "That user cannot be found on IRC. As a result, your message was not sent. Please check the spelling and try again!");
            return;
        }
        /* The user has passed the minimum requirements for input */

	/* now find the language they want */
	fp = gtf_filter_lookup(cmd[2]);
	if (!fp) {
		prefmsg(u->nick, s_StupidServ, "Can not find that Language. /msg %s list for language list", s_StupidServ);
		return;
	}
	inbuf = joinbuf(cmd, ac, 4);
	if (fp->filter(inbuf, outbuf, 450) > 0) {
		prefmsg(u->nick, s_StupidServ, "Translated Text was too Long. Sending shortened text only");
	}
	prefmsg(cmd[3], s_StupidServ, "%s is talking %s, and sent this:", u->nick, cmd[2]);
	prefmsg(cmd[3], s_StupidServ, "%s", outbuf);
	prefmsg(u->nick, s_StupidServ, "Your Message was sent to %s", cmd[3]);
	free(inbuf);
}
