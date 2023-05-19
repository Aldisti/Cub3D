#!/bin/sh

CYAN="\033[1;36m"
GREEN="\033[1;32m"
RED="\033[1;31m"
PURPLE="\033[1;35m"
RESET="\033[0m"

FILE="out/file.out"

rm -rf out >/dev/null 2>&1
mkdir out >/dev/null 2>&1

if [ -f "cub3d" ]; then
	printf "$PURPLE cub3d already exists$RESET\n"
else
	printf "$PURPLE compiling cub3d...$RESET\n"
	make > /dev/null 2>&1
	make clean > /dev/null 2>&1
	printf "$PURPLE cub3d compiled...$RESET\n"
fi

ko=0
i=0
while [ $i -lt 43 ]; do
	printf "\033[1K\r$PURPLE Doing test $CYAN$i$RESET"
	i=$((i + 1))
	./cub3d "maps/wrong$i.cub" >$FILE 2>&1
	sleep .5
	if ! [ "$(pgrep cub3d)" = "" ]; then
		kill -kill $(pgrep cub3d)
		ko=$((ko + 1))
		mv $FILE "out/$i.out"
	elif [ $(grep "error" $FILE | wc -l) -eq 0 ]; then
		ko=$((ko + 1))
		mv $FILE "out/$i.out"
	fi
	rm -f $FILE
done
printf "\033[1K\r"

if [ $ko -eq 0 ]; then
	rm -rf out >/dev/null 2>&1
fi

ok=$((i - ko))
printf "$CYAN ok: $GREEN$ok$CYAN ko: $RED$ko$RESET\n"
