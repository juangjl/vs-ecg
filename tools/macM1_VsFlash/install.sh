export APP=VsFlash
sudo rm -fR /Users/Shared/$APP
sudo mkdir  /Users/Shared/$APP
sudo cp -fR $APP.App/Contents/css		/Users/Shared/$APP
sudo cp -fR $APP.App/Contents/img		/Users/Shared/$APP
sudo cp -fR $APP.App/Contents/data	/Users/Shared/$APP
# copy to application
sudo rm -fR /Applications/$APP.app
sudo cp -fR $APP.app /Applications
