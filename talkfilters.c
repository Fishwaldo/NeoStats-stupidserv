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

#include "config.h"

#include <stddef.h>

#include "talkfilters.h"

static const char *__gtf_version = "GNU Talkfilters v2.0";

static gtf_filter_t __gtf_filters[] =
{
  { "b1ff",       "B1FF",           gtf_filter_b1ff       },
  { "brooklyn",   "Brooklyn",       gtf_filter_brooklyn   },
  { "chef",       "Swedish Chef",   gtf_filter_chef       },
  { "cockney",    "London Cockney", gtf_filter_cockney    },
  { "drawl",      "Southern Drawl", gtf_filter_drawl      },
  { "fudd",       "Elmer Fudd",     gtf_filter_fudd       },
  { "funetak",    "Funetak",        gtf_filter_funetak    },
  { "jethro",     "Jethro",         gtf_filter_jethro     },
  { "jive",       "Jive",           gtf_filter_jive       },
  { "kraut",      "Kraut",          gtf_filter_kraut      },
  { "pansy",      "Pansy",          gtf_filter_pansy      },
  { "postmodern", "Postmodernist",  gtf_filter_postmodern },
  { "redneck",    "Redneck",        gtf_filter_redneck    },
  { "valspeak",   "Valley Speak",   gtf_filter_valspeak   },
  { "warez",      "Warez (H4x0r)",  gtf_filter_warez      },
};

static int __gtf_filter_count = sizeof(__gtf_filters) / sizeof(gtf_filter_t);

/*
 */

int gtf_filter_count(void)
  {
  return(__gtf_filter_count);
  }

/*
 */

const gtf_filter_t *gtf_filter_list(void)
  {
  return(__gtf_filters);
  }

/*
 */

const gtf_filter_t *gtf_filter_lookup(const char *name)
  {
  int i;
  gtf_filter_t *f;

  for(i = 0, f = __gtf_filters; i < __gtf_filter_count; i++, f++)
    {
    if(!strcasecmp(f->name, name))
      return(f);
    }

  return(NULL);
  }

/* end of source file */
