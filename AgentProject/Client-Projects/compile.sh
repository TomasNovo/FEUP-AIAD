#!/bin/bash

link() {
	command="g++ -o main "
	for d in *.o ; do
		# echo "$d"
		command="$command $d"
	done

	echo "$command"
	$command
}

compile() {
	cd "$1"
	shopt -s nullglob
	for d in *.cpp ; do
		filename="${d%.*}"
		echo "$filename"
		command="g++ -c $d -o $filename.o"
		echo "$command"
		$command
	done

	link

	cd "../"
}

for d in */ ; do
	compile "$d"
done