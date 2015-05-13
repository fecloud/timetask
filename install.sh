#!/bin/sh

PROG="timetask"
PROG_PATH="/data/app/$PROG"
MSG_PREFIX=" *"
echo "$MSG_PREFIX start install $PROG"

make

if [ -d "$PROG_PATH" ] ; then
	rm -rf $PROG_PATH
fi

make install

if [ -f "/etc/init.d/$PROG" ] ;then
	echo "$MSG_PREFIX not need add to /etc/init.d"
else
	ln  -f -s $PROG_PATH/$PROG.sh /etc/init.d/$PROG
fi

if [ -f "/etc/rc0.d/K30$$PROG" ] ; then
	echo "$MSG_PREFIX not need add $PROG to boot"
else
	update-rc.d  $PROG defaults 30
fi

echo "$MSG_PREFIX install sucess $PROG"

service $$PROG start