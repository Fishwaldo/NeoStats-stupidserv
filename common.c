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

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

#include "common.h"

/*
 */


/*
 */

/*
 */

void gtf_strbuf_init(gtf_databuf_t *sbuf, char *buf, size_t bufsz)
  {
  sbuf->buf = buf;
  sbuf->bufsz = bufsz;
  sbuf->left = bufsz - 1;
  sbuf->pos = sbuf->buf;
  sbuf->overflow = 0;
  }

/*
 */

int gtf_strbuf_vprintf(gtf_databuf_t *buf, const char *fmt, ...)
  {
  va_list vp;
  int l;

  va_start(vp, fmt);
  l = vsnprintf(buf->pos, buf->left, fmt, vp);
  va_end(vp);

  if(l > buf->left)
    {
    buf->pos += buf->left;
    buf->left = 0;
    buf->overflow = 1;
    }
  else
    {
    buf->left -= l;
    buf->pos += l;
    *(buf->pos) = 0;
    }
  }

/*
 */

int gtf_strbuf_puts(gtf_databuf_t *buf, const char *s)
  {
  int l = strlen(s);

  if(l > buf->left)
    {
    buf->overflow = 1;
    l = buf->left;
    }

  strncpy(buf->pos, s, l);
  buf->pos += l;
  buf->left -= l;

  *(buf->pos) = 0;

  return(l);
  }

/*
 */

int gtf_strbuf_putc(gtf_databuf_t *buf, char c)
  {
  if(buf->left < 1)
    {
    buf->overflow = 1;
    return(0);
    }

  *(buf->pos) = c;
  buf->pos++;
  *(buf->pos) = 0;

  buf->left--;
  
  return(1);
  }

/*
 */

void gtf_random_seed(void)
  {
  srand(time(NULL) | getpid());
  }

/* end of source file */
