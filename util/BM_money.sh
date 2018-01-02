#!/bin/sh
# $Id: BM_money.sh,v 1.2 2000/08/01 04:19:17 davidyu Exp $

bin/BM_money > etc/BM_money
bin/post Record 星期五' '版主發薪日 [財金消息] etc/BM_money
