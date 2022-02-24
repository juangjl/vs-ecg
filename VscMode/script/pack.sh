#rm ip.txt
export app=$(basename "$PWD")
rm ./pack/lib/*
ldd ./out/$app.o | grep '\/mingw.*\.dll' -o | xargs -I{} cp "{}" ./pack/lib

cp -f ./out/$app.o ./pack/bin/$app.exe
