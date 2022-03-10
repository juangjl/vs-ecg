export VS_APP_HOME=ubuntu_VsFlash
export VS_APP=VsFlash
#-----------------------------------------------------------------------#
# install
#-----------------------------------------------------------------------#
cd ..
sudo rm -fR /usr/share/$VS_APP
sudo cp -fR $VS_APP_HOME			/usr/share/$VS_APP
sudo cp -fR $VS_APP_HOME/$VS_APP.desktop 	/usr/share/applications
sudo cp -fR $VS_APP_HOME/img/$VS_APP.xpm 	/usr/share/pixmaps

#-----------------------------------------------------------------------#
# clear previous install
#-----------------------------------------------------------------------#
cd $VS_APP_HOME
sudo rm -fR 	~/$VS_APP
sudo mkdir	~/$VS_APP

#-----------------------------------------------------------------------#
# copy new daa
#-----------------------------------------------------------------------#
sudo cp  -fR img	~/$VS_APP
sudo cp  -fR css	~/$VS_APP
sudo cp  -fR data 	~/$VS_APP

