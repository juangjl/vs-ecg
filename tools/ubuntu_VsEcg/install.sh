export APP=VsEcg
export VS_ECG_HOME=ubuntu_$APP

#-----------------------------------------------------------------------#
# install
#-----------------------------------------------------------------------#
cd ..
sudo rm -fR /usr/share/$APP
sudo cp -fR $VS_ECG_HOME 		/usr/share/$APP
sudo cp -fR $VS_ECG_HOME/$APP.desktop 	/usr/share/applications
sudo cp -fR $VS_ECG_HOME/img/$APP.xpm 	/usr/share/pixmaps

#-----------------------------------------------------------------------#
# clear previous install
#-----------------------------------------------------------------------#
cd $VS_ECG_HOME
sudo rm -fR ~/$APP
sudo mkdir  ~/$APP

#-----------------------------------------------------------------------#
# copy new data
#-----------------------------------------------------------------------#
sudo cp  -fR img 	~/$APP
sudo cp  -fR css 	~/$APP
sudo cp  -fR data 	~/$APP
