/* unix-signals.c
 *
 * Compute the signal table information for UNIX systems.  This is used to
 * generate the unix-signal-table.c file and the system-signals.h file.  We
 * assume that the  signals SIGHUP, SIGINT, SIGQUIT, SIGALRM, and SIGTERM
 * are (at least) provided.
 */

#include "../config.h"

#include "runtime-unixdep.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen.h"
#include "gen-unix-signals.h"


/** The UNIX signals **/
sig_desc_t	SigTable[] = {
	{ SIGHUP,	"SIGHUP",	"HUP"},		/* POSIX */
	{ SIGINT,	"SIGINT",	"INTERRUPT"},		/* POSIX */
	{ SIGQUIT,	"SIGQUIT",	"QUIT"},	/* POSIX */
	{ SIGALRM,	"SIGALRM",	"ALARM"},	/* POSIX */
	{ SIGTERM,	"SIGTERM",	"TERMINAL"},	/* POSIX */
#ifdef SIGPIPE
	{ SIGPIPE,	"SIGPIPE",	"PIPE"},	/* POSIX */
#endif
#ifdef SIGUSR1
	{ SIGUSR1,	"SIGUSR1",	"USR1"},	/* POSIX */
#endif
#ifdef SIGUSR2
	{ SIGUSR2,	"SIGUSR2",	"USR2"},	/* POSIX */
#endif
#if defined(SIGCHLD)
	{ SIGCHLD,	"SIGCHLD",	"CHLD"},	/* POSIX */
#elif defined(SIGCLD)
	{ SIGCLD,	"SIGCLD",	"CHLD"},
#endif
#if defined(SIGWINCH)
	{ SIGWINCH,	"SIGWINCH",	"WINCH"},
#elif defined(SIGWINDOW)
	{ SIGWINDOW,	"SIGWINDOW",	"WINCH"},
#endif
#ifdef SIGURG
	{ SIGURG,	"SIGURG",	"URG"},
#endif
#ifdef SIGIO
	{ SIGIO,	"SIGIO",	"IO"},
#endif
#ifdef SIGPOLL
	{ SIGPOLL,	"SIGPOLL",	"POLL"},
#endif
#ifdef SIGTSTP
	{ SIGTSTP,	"SIGTSTP",	"TSTP"},	/* POSIX */
#endif
#ifdef SIGCONT
	{ SIGCONT,	"SIGCONT",	"CONT"},	/* POSIX */
#endif
#ifdef SIGTTIN
	{ SIGTTIN,	"SIGTTIN",	"TTIN"},	/* POSIX */
#endif
#ifdef SIGTTOU
	{ SIGTTOU,	"SIGTTOU",	"TTOU"},	/* POSIX */
#endif
#ifdef SIGVTALRM
	{ SIGVTALRM,	"SIGVTALRM",	"VTALRM"},
#endif
};
#define TABLE_SIZE	(sizeof(SigTable)/sizeof(sig_desc_t))

/* the run-time system generated signals */
sig_desc_t    RunTSignals[] = {
	{ -1,           "RUNSIG_GC",    "GARBAGE_COLLECTION" },
};
#define NUM_RUN_SIGS  (sizeof(RunTSignals)/sizeof(sig_desc_t))

/* SortSignalTable:
 */
sig_info_t *SortSignalTable ()
{
    int		    i, j, k, n;
    sig_desc_t	    **signals;
    sig_info_t	    *sigInfo;

    signals = NEW_VEC(sig_desc_t *, TABLE_SIZE + NUM_RUN_SIGS);

    /* Sort the signal table by increasing signal number.
     * The sort removes duplicates by mapping to the first name.
     * We need this because some systems alias signals.
     */
    for (i = 0, n = 0;  i < TABLE_SIZE;  i++) {

        /* Invariant: signals[0..n-1] is sorted */

	sig_desc_t	*p = &(SigTable[i]);

	for (j = 0;  j < n;  j++) {
	    if (signals[j]->sig == p->sig)
	      /* a duplicate */
		break;
	    if (signals[j]->sig > p->sig) {
	      /* insert the signal at position j */
		for (k = n;  k >= j;  k--)
		    signals[k] = signals[k-1];
		signals[j] = p;  n++;
		break;
	    }
	}
	if (j == n) {
	    signals[n++] = p;
	}
    }

    /* Here, n is the number of system signals and
     * signals[n-1]->sig is the largest system signal code.
     */

    /* Add the run-time system signals to the table:
     */
    for (i = 0, j = n;  i < NUM_RUN_SIGS;  i++, j++) {
      signals[j] = &(RunTSignals[i]);
      signals[j]->sig = signals[n-1]->sig+i+1;
    }


    sigInfo = NEW_CHUNK(sig_info_t);
    sigInfo->sigs	= signals;
    sigInfo->numSysSigs	= n;
    sigInfo->numRunSigs	= NUM_RUN_SIGS;
    sigInfo->minSysSig	= signals[0]->sig;
    sigInfo->maxSysSig	= signals[n-1]->sig;

    return sigInfo;

}


/* COPYRIGHT (c) 1995 by AT&T Bell Laboratories.
 * Subsequent changes by Jeff Prothero Copyright (c) 2010,
 * released under Gnu Public Licence version 3.
 */

/* end of SortSignalTable */
