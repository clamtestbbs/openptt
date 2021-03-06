/*     壽星程式               96 10/11            */

#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "pttstruct.h"
#include "util.h"
#include "common.h"

#define OUTFILE    BBSHOME "/etc/birth.today"

struct userec_t cuser;

int bad_user_id() {
    register char ch;
    int j;
    if (strlen(cuser.userid) < 2 || !isalpha(cuser.userid[0]))
	return 1;
    if (cuser.numlogins == 0 || cuser.numlogins > 15000)
	return 1;
    if (cuser.numposts > 15000)
	return 1;
    for (j = 1; (ch = cuser.userid[j]); j++)
    {
	if (!isalnum(ch))
	    return 1;
    }
    return 0;
}

int Link(char *src, char *dst) {
    char cmd[200];

    if (link(src, dst) == 0)
	return 0;

    sprintf(cmd, "/bin/cp -R %s %s", src, dst);
    return system(cmd);
}

int main(argc, argv)
    int argc;
    char **argv;
{
    FILE *fp1;
    fileheader_t mymail;
    char today[500][14], today_name[500][24];
    int i, day = 0, a[50], b[50];
    time_t now;
    struct tm *ptime;
    int j;

    now = time(NULL);		/* back to ancent */
    ptime = localtime(&now);

    if(passwd_mmap())
	exit(1);
    for(j = 1; j <= MAX_USERS; j++) {
	passwd_query(j, &cuser);
	if (bad_user_id())
	    continue;
	if (cuser.month == ptime->tm_mon + 1)
	{
	    if (cuser.day == ptime->tm_mday)
	    {
		char genbuf[200];
		sprintf(genbuf, BBSHOME "/home/%c/%s", cuser.userid[0], cuser.userid);
		stampfile(genbuf, &mymail);
		strcpy(mymail.owner, BBSNAME);
		strcpy(mymail.title, "!! 生日快樂 !!");
		mymail.savemode = 0;
		unlink(genbuf);
		Link(BBSHOME "/etc/Welcome_birth", genbuf);
		sprintf(genbuf, BBSHOME "/home/%c/%s/.DIR", cuser.userid[0], cuser.userid);
		append_record(genbuf, &mymail, sizeof(mymail));
		if ((cuser.numlogins + cuser.numposts) < 20)
		    continue;
		a[day] = cuser.numlogins;
		b[day] = cuser.numposts;
		strcpy(today[day], cuser.userid);
		strcpy(today_name[day++], cuser.username);
	    }
/*
  else if(cuser.day <= ptime->tm_mday+2 && cuser.day >=
  ptime->tm_mday-2)
  {
  if((cuser.numlogins + cuser.numposts) < 10) continue;
  week_day[wee] = cuser.day;
  strcpy(week[wee++],cuser.userid);
  }
  else
  {
  month_day[mon] = cuser.day;
  strcpy(month[mon++],cuser.userid);
  }
*/
	}
    }
    printf("*製表\n");
    fp1 = fopen(OUTFILE, "w");

    fprintf(fp1, "\n                      "
	    "[1m★[35m★[34m★[33m★[32m★[31m★[45;33m 壽星大觀 "
	    "[40m★[32m★[33m★[34m★[35m★[1m★[m \n\n");
    if (day > 0)
    {
	fprintf(fp1, "[33m【[1;45m本日壽星[40;33m】[m \n");
	for (i = 0; i < day; i++)
	{
	    fprintf(fp1, "   [33m[%2d/%-2d] %-14s[0m %-24s login:%-5d post:%-5d\n",
		    ptime->tm_mon + 1, ptime->tm_mday, today[i], today_name[i], a[i], b[i]);
	}

    }
    fclose(fp1);
    return 0;
}
