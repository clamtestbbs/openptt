#!/bin/sh
# $Id: openticket.sh,v 1.2 2000/08/01 04:19:17 davidyu Exp $

bin/openticket > etc/jackpot
bin/post Record "�m�餤���W��" "[������i]" etc/jackpot
bin/post Record "�q�Ʀr�����W��" "[�q�Ʀr���i]" etc/winguess.log
bin/post Record "�¥մѹ�԰O��" "[�q�Ʀr���i]" etc/othello.log
rm -f etc/winguess.log
rm -f etc/loseguess.log
rm -f etc/othello.log
