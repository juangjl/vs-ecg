export APP=VsEcg
rm -fR /Users/Shared/$APP
mkdir  /Users/Shared/$APP
cp -fR $APP.App/Contents/css		/Users/Shared/$APP
cp -fR $APP.App/Contents/img		/Users/Shared/$APP
cp -fR $APP.App/Contents/data		/Users/Shared/$APP

# remove previos version
rm -fR /Applications/$APP.App
cp -fR $APP.App /Applications

