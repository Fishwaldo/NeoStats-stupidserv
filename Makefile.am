AUTOMAKE_OPTIONS        = foreign
ACLOCAL_AMFLAGS         = -I autotools
AM_MAKEFLAGS            = -s

pkglib_LTLIBRARIES	= stupidserv.la
stupidserv_la_SOURCES	= ss.c s_help.c flex/b1ff.l flex/chef.l common.c flex/fudd.l flex/jethro.l flex/kraut.l flex/postmodern.l talkfilters.c \
			  flex/warez.l flex/brooklyn.l flex/cockney.l flex/drawl.l flex/funetak.l flex/jive.l flex/pansy.l flex/redneck.l flex/valspeak.l \
			  flex/austro.l flex/dubya.l flex/pirate.l
noinst_HEADERS		= common.h ss.h talkfilters.h

stupidserv_la_LDFLAGS	= -module -avoid-version -noundefined

EXTRA_DIST		= autotools/ccdv.c autotools/shtool RELNOTES

dist_doc_DATA		= README.StupidServ


include $(top_srcdir)/autotools/rules.mk
