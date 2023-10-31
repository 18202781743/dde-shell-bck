#!/bin/bash

cmake --build /home/out/dde-shell-Debug-qt6/

/home/out/dde-shell-Debug-qt6/shell/dde-shell -c org.deepin.ds.osd &

sleep 1

audio=("AudioUp" )
#brightness=("BrightnessUp" "BrightnessDown" "BrightnessUpAsh" "BrightnessDownAsh")
default=("WLANOn" "WLANOff")
display=("SwitchMonitors")
#kblayout=("SwitchLayout")

#audio=("AudioUp" "AudioDown" "AudioMute" "AudioUpAsh" "AudioDownAsh" "AudioMuteAsh")
#brightness=("BrightnessUp" "BrightnessDown" "BrightnessUpAsh" "BrightnessDownAsh")
#default=("WLANOn" "WLANOff" "CapsLockOn" "CapsLockOff" "NumLockOn" "NumLockOff" "TouchpadOn" "TouchpadOff" "TouchpadToggle" "FnToggle" "AirplaneModeOn" "AirplaneModeOff" "AudioMicMuteOn" "AudioMicMuteOff" "balance" "powersave" "performance" "SwitchWM3D" "SwitchWM2D" "SwitchWMError")
#display=("SwitchMonitors")
#kblayout=("SwitchLayout")

for type in  ${kblayout[@]} ${display[@]} ${audio[@]} ${brightness[@]} ${default[@]} ;
do

echo dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:$type

dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:$type
sleep 1

done

jobs -p |xargs kill
