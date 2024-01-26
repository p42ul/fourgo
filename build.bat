%GBDK_HOME%\bin\lcc ^
	-I%GBDK_HOME%\hUGETracker-1.0.4-windows\hUGEDriver\include ^
	-Wl-llib\hUGEDriver.lib ^
	-o fourgo.gb ^
	sprites\puck.c ^
	board.c drawing.c sound.c fourgo.c
