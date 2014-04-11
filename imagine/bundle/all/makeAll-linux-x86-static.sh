makefilesToRun='
	src/libpng/linux-x86.mk
	src/minizip/linux-x86.mk
'

for makefile in $makefilesToRun
do
	oldDir=`pwd`
	cd `dirname $makefile`
	echo "running make on $makefile"
	make -f `basename $makefile` $@
	if [ $? != 0 ]
	then
		exit 1
	fi
	cd $oldDir
done

