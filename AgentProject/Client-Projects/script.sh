#!/bin/bash

work_folder () {
	MYPATH="$1"
	echo "$MYPATH"
	cd "$MYPATH"
	shopt -s nullglob
	for d in *.cpp ; do
		echo "found $d"
		cd "../"
		return
	done

	OLDDIR="$PWD"
	TEMPDIR="temp$RANDOM"
	rm -rf $TEMPDIR
	mkdir $TEMPDIR
	find . -type f -name \*.cpp -exec cp {} $TEMPDIR \;
	find . -type f -name \*.h -exec cp {} $TEMPDIR \;
	find . -type f -name \*.hpp -exec cp {} $TEMPDIR \;

	find . ! \( -name $TEMPDIR -o -name ".." -o -name "." \) -type d -exec rm -rf {} +
	find . -maxdepth 1 -type f  -exec rm -f {} +
	mv "$TEMPDIR"/* .
	rm -rf $TEMPDIR

	cd "../"
	echo done
}

echo $PWD

# for d in */ ; do
	compile "AEDA-FINAL-PROJECT Joao Nuno"
# done