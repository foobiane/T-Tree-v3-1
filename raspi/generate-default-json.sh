#!/bin/bash

# Usage: ./generate-defaut-json [path]

args=("$@")

ssid="ttree3"
pw="ttree3_2026"
ip=""

while [ ! -z "$ip" -a "ip" == " " ] do
    ip=$(ifconfig wlan1 | awk '/inet / {print $2}')
done

port="8000"

cat << EOF > ${args[0]}/default.json
{
    "wifiSSID": "$ssid",
    "wifiPSK": "$pw",
    "oscIP1": "$ip",
    "oscPORT1": $port
}
EOF