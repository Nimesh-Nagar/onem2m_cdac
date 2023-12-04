#!/bin/bash 

# automatically discovers IP of the network, discover live (connected) devices and open ports.

#1. Get 3 octets of Network IP 
ifconfig | grep "broadcast" | cut -d " " -f 10 | cut -d "." -f 1,2,3 | uniq > octets.txt
OCTETS=$(cat octets.txt)

#create new txt file 
echo "" > $OCTETS.txt

#2. discover for live host by pinging them 
for ip in {230..245}
do 
    ping  -c 1 $OCTETS.$ip | grep "64 bytes" | cut -d " " -f 4 | tr -d ":" >> $OCTETS.txt
done 

cat $OCTETS.txt | sort >sorted_$OCTETS.txt 

#3. Scanning for open ports 
nmap -sS -iL sorted_$OCTETS.txt 
exit 

