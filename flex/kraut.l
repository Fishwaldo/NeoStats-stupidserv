/* GNU Talkfilters
   Copyright (C) 1998-2003 Free Software Foundation, Inc.

   This file is part of GNU Talkfilters

   GNU Talkfilters is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This software is distributed in the hope that it will be amusing, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this software; see the file COPYING.  If not, write to the
   Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/

%option prefix="kraut_yy"
%option outfile="lex.yy.c"
%option noyywrap

%e 2000
%p 5000
%n 1000
%k 500
%a 4000
%o 2000

%{

#include "common.h"

#define YY_DECL int yylex(gtf_databuf_t *buf)

%}

BW	[ \t]
EW	[ \t.,;!?]
EOT	\4

%%

"Why "		gtf_printf("Warum ");
"damn"		gtf_printf("verdamt");
"dammit"	gtf_printf("Gott verdamt");
ing		gtf_printf("ingkt");
"Chevy"		gtf_printf("Volkswagen");
" not "		gtf_printf(" nicht ");
" not."		gtf_printf("nicht.");
" not?"		gtf_printf("nicht?");
" not!"		gtf_printf("nicht!");
" the "		gtf_printf(" ze ");
"The "		gtf_printf("Ze ");
" with "	gtf_printf(" mitt ");
"With "		gtf_printf("Mitt ");
wr		gtf_printf("w-r-r");
Wr		gtf_printf("W-r-r");
R		gtf_printf("R-r-r");
"Yes "		gtf_printf("Jawohl ");
" r"		gtf_printf(" r-r-r");
"Yes."		gtf_printf("Jawohl.");
"Yes!"		gtf_printf("Jawohl!");
"YES!"		gtf_printf("JAWOHL!");
" yes "		gtf_printf(" ja ");
" yes."		gtf_printf(" ja.");
" yes!"		gtf_printf(" yes!");
"No "		gtf_printf("Nein ");
"No!"		gtf_printf("Nein!");
"No?"		gtf_printf("Nein?");
" no "		gtf_printf(" nein ");
" no."		gtf_printf(" nein.");
" no!"		gtf_printf(" nein!");
" no?"		gtf_printf(" nein?");
[Mm]"r."	gtf_printf("Herr");
[Mm]"rs."	gtf_printf("Frau");
Miss		gtf_printf("Fraulein");
" of "		gtf_printf(" uff ");
"Of "		gtf_printf("Uff ");
my		gtf_printf("mein");
My		gtf_printf("Mein");
" and "		gtf_printf(" undt ");
"And "		gtf_printf("Undt ");
"One "		gtf_printf("Ein ");
" one"		gtf_printf(" ein");
"Is "		gtf_printf("Ist ");
" is "		gtf_printf(" ist ");
"ow "		gtf_printf("ow ");
"w "		gtf_printf("w ");
sh		gtf_printf("sch");
Sh		gtf_printf("Sch");
ch		gtf_printf("ch");
Ch		gtf_printf("Ch");
" c"		gtf_printf(" k");
" C"		gtf_printf(" K");
v		gtf_printf("f");
V		gtf_printf("F");
" w"		gtf_printf(" v");
W		gtf_printf("V");
[Tt]h		gtf_puts_case("d");
[Jj]ohn		gtf_printf("Johann");
[Ww]illiam|[Bb]ill|[Bb]rad	gtf_printf("Wilhelm");
[Gg]ary		gtf_printf("Gerhardt");
[Jj]o(h)?n	gtf_printf("Hansel");
[Ss]mith	gtf_printf("Schultz");
[a-f]"!"	gtf_printf("%s Naturlich!", yytext);
[p-z]"!"	gtf_printf("%s Seig Heil!", yytext);

{EOT}		/* ignore trailing EOT character */
.		gtf_echo();
\n		gtf_printf("\n");

%%

#ifdef LIBRARY_MODE

int gtf_filter_kraut(const char *input, char *buf, size_t bufsz)
  {
  gtf_databuf_t buffer;
  YY_BUFFER_STATE _yybuf;

  gtf_strbuf_init(&buffer, buf, bufsz);
  _yybuf = yy_scan_string(input);
  yylex(&buffer);
  yy_delete_buffer(_yybuf);
  gtf_reset();

  return(buffer.overflow);
  }

#else /* LIBRARY_MODE */

int main(int argc, char **argv)
  {
  gtf_parse_args();

  yylex(NULL);

  return(EXIT_SUCCESS);
  }

#endif /* LIBRARY_MODE */

/* end of source file */
