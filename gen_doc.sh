#!/usr/bin/env bash

doxygen

if [ "$USER" = "guemasg" ] && ! [ -f "./.lock" ]
then
	touch .lock
	scp ./doc/html/* root@163.172.148.143:/var/www/html
	scp ./doc/html/search/* root@163.172.148.143:/var/www/html/search/
	rm .lock
#	rm -fr /tmp/doc/
#	mkdir /tmp/doc/
#	cp ./doc/html/ -rf /tmp/doc
#	cp ./doc/html/.git/ -rf /tmp/doc/tmp/
#	cd /tmp/doc
#	git commit -am "doc maj"
#	git push
#	echo "cd /var/www ; git pull" | ssh root@163.172.148.143
fi