DESKTOP_FILE="/usr/share/xsessions/dwm.desktop"
mkdir -p bin

cc source/drw.c source/util.c source/main.c \
-I /usr/X10R6/include \
-I /usr/include/freetype2 -I ./source -I ./headers \
-L /usr/X11R6/lib -lXinerama -lfontconfig -lXft -lX11 -lm \
-Wno-deprecated-declarations -Wno-pragma-once-outside-header \
-o bin/dwm
compile_status=$?

if [ "$EUID" -eq 0 ]; then
    if [ ! -f $DESKTOP_FILE ]; then
        echo "[Desktop Entry]" >> "$DESKTOP_FILE"
        echo "Name=dwm" >> "$DESKTOP_FILE"
        echo "Comment=suckless dynamic window manager" >> "$DESKTOP_FILE"
        echo "Exec=dwm" >> "$DESKTOP_FILE"
        echo "Type=Application" >> "$DESKTOP_FILE"
        echo "INFO: Created desktop file: '$DESKTOP_FILE'"
    fi
    if [ $compile_status -eq 0 ]; then
        install -m 755 ./bin/dwm /usr/local/bin/dwm
        echo "OK"
    fi
else
    echo "INFO: RUN AS ROOT TO COMPLETE INSTALLATION"
fi
