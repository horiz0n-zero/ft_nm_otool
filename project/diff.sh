#!/bin/bash

./ft_nm $2 $1 > a
nm $2 $1 > b
diff a b > c
if [ -s c ]
then
	cat c | head
else
	echo "\033[38;5;154m no diff $2 $1"
fi
rm a b c
