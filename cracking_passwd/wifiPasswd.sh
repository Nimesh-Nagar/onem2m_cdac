#!/bin/bash 

echo "----------------------------------------------------------------------------"
echo "           Welcome To WPA/WPA2 or WEP Password Cracking  Interface          "
echo "----------------------------------------------------------------------------"

echo -e "\nScanning for wireless interfaces ..... \n"
iwconfig

read -p "Enter wireless interface Name : " wifi_card
echo $wifi_card "interface selected for Monitoring mode. "

# converting wireless interface in monitoring Mode.
airmon-ng start $wifi_card 

#capturing all packets for analysis 
read -p "Enter wireless interface which is in monitoring mode : " wifi_mon  #(automate it ! )

echo "press CTRL+C to stop scanning "
# file_path=$HOME/iot_security/codes/cracking_passwd/packets/
read -p "Enter file name for Packet capture : " file_name

airodump-ng -w $file_name $wifi_mon