/* NeoStats - IRC Statistical Services Copyright (c) 1999-2002 NeoStats Group Inc.
** Copyright (c) 1999-2002 Adam Rutter, Justin Hammond
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
** $Id: s_help.c,v 1.1 2003/02/18 13:53:03 fishwaldo Exp $
*/

const char *s_help[] = {
"\2StupidServ Help\2",
"",
"Commands:",
"     SEND     CONVERT     LIST     ABOUT     VERSION",
"",
"This bot translates your text to a \"Language\" and can optionally send it to a user",
"or Channel (if you are a operator)",
"",
"\2SEND\2",
"\2/msg StupidServ SEND <LANG> <NICK/CHAN> <TEXT...>\2",
"Converts your text to the language, and sends it to the nick or channel",
"",
"\2CONVERT\2",
"\2/msg StupidServ CONVERT <LANG> <TEXT...>\2",
"Converts the text and echo's it back to you",
"",
"\2LIST\2",
"\2/msg StupidServ LIST\2",
"Lists all available Languages",
"",
"\2ABOUT\2 and \2VERSION\2",
"\2/msg StupidServ ABOUT/VERSION\2",
"Gives information about StupidServ",
NULL
};

const char *s_about[] = {
"\2StupidServ Help\2",
"",
"This Module was created with the help of some software called TalkFilters",
"which is a collection of Translators created by a wide range of authors",
"",
"This module will take your text, and attempt to translate it to your language of choice",
"Optionally, sending the resultant text to a user or channel",
"",
"This module was coded in about 2 hours one night... I was amused by talkfilters",
"and thought it would be fun to have on IRC as well",
"The original Talkfilter maintainer and contributors are:",
"",
"TalkFilter: Mark Lindner (mark_a_lindner@yahoo.com)",
"",
"b1ff       - Matt Welsh, David Whitten",
"brooklyn   - Daniel V. Klein [originally named nyc]",
"chef       - John Hagerman",
"cockney    - Stephen K Mulrine, Edward Betts, (unknown) and Samuel Stoddard",
"drawl      - Adam Hudd",
"fudd       - (unknown)",
"funetak    - Eclipse Enterprises (unknown)",
"jethro     - Duane Paulson",
"jive       - Daniel V. Klein, Clement Cole, Samuel Stoddard",
"kraut      - (unknown)",
"pansy      - (unknown)",
"postmodern - (unknown) ",
"redneck    - Brand Hilton",
"valspeak   - (unknown)",
"warez      - Ian Johnston",
NULL
};

