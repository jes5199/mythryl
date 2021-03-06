#!/bin/sh
#
# gen-posix-names.sh
#
# COPYRIGHT (c) 1996 AT&T Research.
#
# Generate string-to-int tables for run-time POSIX values
# queried using sysconf and (f)pathconf.
#
# Usage: gen-posix-names.sh <prefix> <outfile>
#

# redefine PATH so that we get the right versions of the various tools
#
PATH=/bin:/usr/bin

# set locale variables so that sort works right
#
# export LC_CTYPE LC_COLLATE
# LC_CTYPE=C
# LC_COLLATE=C
#
#     From: Pippijn van Steenhoven <pip88nl@gmail.com>
#     Subject: Re: [Mythryl] compiler fails to compile
#     To: mythryl@mythryl.org
#     Date: Wed, 22 Jul 2009 15:13:44 +0200
#     Mail-Followup-To: mythryl@mythryl.org
#     
#     Fixed. My system needs LC_ALL, not LC_CTYPE and LC_COLLATE in
#     gen-posix-names.sh. To quote the manpage:
#     
#            ***  WARNING  ***  The locale specified by the environment affects sort
#            order.  Set LC_ALL=C to get the traditional sort order that uses native
#           byte values.
#
export LC_ALL
LC_ALL=C


CPP=${CPP:-/lib/cpp}

PFIX=$1      # prefix: _SC_ or _PC_
OUTF=$2      # name of output file

# linux uses enums for the _SC_ constants. 
# In this case, we cannot use the #ifdef check to avoid symbols
# that are not really defined in unistd.h.
case "$VERSION" in
  *linux*) USED_ENUMS=TRUE ;;
  *) USED_ENUMS="" ;;
esac

if [ "$USED_ENUMS" = "TRUE" ]; then
  INCLFILE=tmp$$
  SRCFILE=tmp$$.c
  echo "#include <unistd.h>" > $SRCFILE
  $CPP $SRCFILE > $INCLFILE
  rm -f $SRCFILE
else
# search the possible include files looking for a source
# of the constants.
  FILES="\
	/usr/include/unistd.h \
	/usr/include/sys/unistd.h \
	/usr/include/bsd/unistd.h \
	/usr/include/confname.h \
    "
  INCLFILE="none"
  for f in $FILES ; do
    if test -r $f ; then
      grep $PFIX $f > /dev/null
      if test $? -eq 0 ; then
	INCLFILE=$f
	break;
      fi
    fi
  done
fi
if test x$INCLFILE = xnone ; then
  echo "gen-posix-names.sh: unable to find <unistd.h>"
  exit 1
fi

echo "/* $OUTF" >> $OUTF
echo " *"       >> $OUTF
echo " * This file is generated by gen-posix-names.sh" >> $OUTF
echo " */"       >> $OUTF

if [ "$USED_ENUMS" = "TRUE" ]; then
  for i in `sed -n "s/.*$PFIX\([0-9A-Z_]*\).*/\1/p" $INCLFILE | sort -u`
  do
    echo "  {\"$i\",  $PFIX$i}," >> $OUTF
  done
else
  for i in `sed -n "s/.*$PFIX\([0-9A-Z_]*\).*/\1/p" $INCLFILE | sort -u`
  do
    echo "#ifdef $PFIX$i" >> $OUTF
    echo "  {\"$i\",  $PFIX$i}," >> $OUTF
    echo "#endif" >> $OUTF
  done
fi

if [ "$USED_ENUMS" = "TRUE" ]; then
  rm -f $INCLFILE
fi

exit 0
