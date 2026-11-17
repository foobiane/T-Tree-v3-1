#!/bin/bash

# Usage: ./generate-defaut-json [path]

args=("$@")

ssid="ttree3"
pw="ttree3_2026"
ip=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')
port="8000"

cat << EOF > ${args[1]}
{
    "wifiSSID": "$ssid",
    "wifiPSK": "$pw",
    "oscIP1": "$ip",
    "oscPORT1": "$port"
}
EOF