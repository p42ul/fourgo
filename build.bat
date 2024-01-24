%GBDK_HOME%\bin\lcc ^
	-I%GBDK_HOME%\hUGETracker-1.0.4-windows\hUGEDriver\include ^
	-Wl-llib\hUGEDriver.lib ^
	-o fourgo.gb ^
	board.c drawing.c sound.c fourgo.c ^
	sprites\puck_map.c sprites\puck_tiles.c sprites\winner_lines.c
