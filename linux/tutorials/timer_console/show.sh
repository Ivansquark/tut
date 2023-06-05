#! /bin/sh
while true;
do 
    clear
    date
    echo "Video RAM: "
    glxinfo | grep 'Currently'
    echo "RAM: "
    cat /proc/meminfo | grep MemAvailable
    sleep 0.3
done
