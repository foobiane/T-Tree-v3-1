#!/bin/bash

# Usage: ./generate-defaut-json [path]

args=("$@")

ssid="ttree3"
pw="ttree3_2026"
ip=$(ifconfig wlan1 | awk '/inet / {print $2}')
port="8000"

cat << EOF > ${args[0]}/default.json
{
    "wifiSSID": "$ssid",
    "wifiPSK": "$pw",
    "oscIP1": "$ip",
    "oscPORT1": $port
}
EOF