#!/bin/bash

pkill dde-shell

cmake --build /home/out/dde-shell-Debug-qt6/

/home/out/dde-shell-Debug-qt6/shell/dde-shell -c org.deepin.ds.osd &

sleep 1

#busctl --user monitor --match="type='method_call',eavesdrop='true',destination='org.deepin.dde.Osd1'" -j |jq --unbuffered -r '.payload.data[0]' |xargs -I {}  dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:{}


#audio=("AudioUp" )
#brightness=("BrightnessUp")
#default=("WLANOn" "WLANOff")
#display=("SwitchMonitors" "DirectSwitchLayout")
#kblayout=("SwitchLayout" "SwitchLayout")


audio=("AudioUp" "AudioDown")
brightness=("BrightnessUp" "BrightnessDown")
default=("WLANOn" "CapsLockOn")
display=("SwitchMonitors")
kblayout=("SwitchLayout")


#audio=("AudioUp" "AudioDown" "AudioMute" "AudioUpAsh" "AudioDownAsh" "AudioMuteAsh")
#brightness=("BrightnessUp" "BrightnessDown" "BrightnessUpAsh" "BrightnessDownAsh")
#default=("WLANOn" "WLANOff" "CapsLockOn" "CapsLockOff" "NumLockOn" "NumLockOff" "TouchpadOn" "TouchpadOff" "TouchpadToggle" "FnToggle" "AirplaneModeOn" "AirplaneModeOff" "AudioMicMuteOn" "AudioMicMuteOff" "balance" "powersave" "performance" "SwitchWM3D" "SwitchWM2D" "SwitchWMError")
#display=("SwitchMonitors")
#kblayout=("SwitchLayout")

for type in  ${audio[@]} ${kblayout[@]} ${display[@]} ${brightness[@]} ${default[@]} ;
do

echo dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:$type

dbus-send --session --type=method_call --print-reply --dest=org.deepin.dde.Shell /org/deepin/osdService org.deepin.osdService.showText string:$type
sleep 1

done

#jobs -p |xargs kill
