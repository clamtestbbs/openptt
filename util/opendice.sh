#!/bin/sh
# $Id: opendice.sh,v 1.2 2000/08/01 04:19:17 davidyu Exp $

bin/countalldice > etc/dice.dis
bin/post  Record   "��l�����W��"  "[��l���i]"   etc/windice.log
bin/post  Security   "��l���ѦW��"  "[��l���i]"   etc/lostdice.log
bin/post  Security "��l�����"    "[��l���i]"   etc/dice.dis
rm -f etc/windice.log
rm -f etc/lostdice.log
rm -f etc/dice.dis