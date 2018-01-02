#!/bin/sh
# $Id: mailog.sh,v 1.2 2000/08/01 04:19:17 davidyu Exp $
#
# 整理出廣告信名單

bin/antispam 
bin/post Record 今日違法廣告信名單 [Ptt警察局] etc/spam
bin/post Security 站外來信紀錄mailog [系統安全局] etc/mailog
rm etc/mailog
