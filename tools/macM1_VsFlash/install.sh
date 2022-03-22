export APP=VsFlash
sudo rm -fR /Users/Shared/$APP
sudo mkdir  /Users/Shared/$APP
sudo cp -fR $APP.App/Contents/css		/Users/Shared/$APP
sudo cp -fR $APP.App/Contents/img		/Users/Shared/$APP
sudo cp -fR $APP.App/Contents/data	/Users/Shared/$APP
sudo chmod -R 777 /Users/Shared/$APP/data
sudo chmod -R 777 /Users/Shared/$APP/css
sudo chmod -R 777 /Users/Shared/$APP/img
# copy to application
sudo rm -fR /Applications/$APP.app
sudo cp -fR $APP.app /Applications
