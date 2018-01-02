#!/bin/sh
# $Id: cvslog.sh,v 1.2 2000/08/01 04:19:17 davidyu Exp $

board="cvslog"
subject=$1

/home/bbs/bin/post $board "commit: $subject" `id -un` - > /dev/null
