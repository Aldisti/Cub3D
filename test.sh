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
	printf "$PURPLE compiling cub3d...$RESET"
	make > /dev/null 2>&1
	make clean > /dev/null 2>&1
	printf "\033[1K\r$PURPLE cub3d compiled...$RESET\n"
fi

test_wrong_map()
{
	printf "\033[1K\r$PURPLE Testing wrong maps, n: $CYAN$1$RESET"
	i=$((i + 1))
	./cub3d $2 >$FILE 2>&1 &
	sleep .5
	if ! [ "$(pgrep cub3d)" = "" ]; then
		kill -kill $(pgrep cub3d)
		mv $FILE "out/$1.out"
		ko=$((ko + 1))
	elif [ $(grep "Error" $FILE | wc -l) -eq 0 ]; then
		mv $FILE "out/$1.out"
		ko=$((ko + 1))
	fi
	rm -f $FILE >/dev/null 2>&1
	return 0
}

ko=0
i=1
while [ $i -lt 43 ]; do
	test_wrong_map $i "maps/wrong$i.cub"
done
# OTHER TESTS
test_wrong_map $i "maps/mapcub"
test_wrong_map $i "maps/mapub"
test_wrong_map $i "maps/mapb"
test_wrong_map $i "maps/map."
test_wrong_map $i "plokmijnuhbygvtfcrdxeszwaq"

i=$((i - 1))

printf "\033[1K\r$PURPLE $i tests executed\n"

if [ $ko -eq 0 ]; then
	rm -rf out >/dev/null 2>&1
else
	rm -rf $FILE >/dev/null 2>&1
fi

printf "$CYAN ok: $GREEN$((i - ko))$CYAN ko: $RED$ko$RESET\n"
