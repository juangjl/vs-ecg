export app=$(basename "$PWD")

#----------------------------------------------------------------------------#
# Packing windows application: init
#----------------------------------------------------------------------------#
if [ "$1" = "clear" ]
then
	echo "pack clear"
	rm -fR ./pack
	exit;
fi

if [ "$1" = "init" ]
then
	echo "PACK_INIT"
	echo off
	rm -fR ./pack
	mkdir pack
	cd pack
	mkdir img
	mkdir lib
	mkdir bin
	mkdir css
	mkdir data
	mkdir ./data/VSH101
	mkdir ./data/VSD101	
	cd ..
	cp  ./img/* ./pack/img
	cp  ./css/* ./pack/css
	cp  ./data/VSH101/* ./pack/data/VSH101
	cp  ./data/VSD101/* ./pack/data/VSD101
	cp  ./data/*.txt ./pack/data
	ldd ./out/$app.o | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" ./pack/lib
	cp  ./prj/run.bat ./pack
	cp -fR	./prj/gdk-pixbuf-2.0 ./pack/lib
	echo on
fi

#----------------------------------------------------------------------------#
# Packing window application: Copy
#----------------------------------------------------------------------------#
echo "PACK_EXE"
cp -f ./out/$app.o ./pack/bin/$app.exe

