cmake --build /home/out/dde-shell-Debug-qt6/

/home/out/dde-shell-Debug-qt6/shell/dde-shell -c org.deepin.ds.osd &

sleep 1


dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:"SwitchMonitors"

sleep 1


dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:"AudioDown"

sleep 1

dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:"WLANOn"

sleep 1

dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:"WLANOff"

sleep 1

pkill dde-shell
