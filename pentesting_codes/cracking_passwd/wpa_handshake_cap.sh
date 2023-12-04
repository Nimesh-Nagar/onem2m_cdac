#! /bin/bash 

echo "----------------------------------------------------------------------------"
echo "           Welcome To WPA/WPA2 or WEP Password Cracking  Interface          "
echo "----------------------------------------------------------------------------"

# Function to capture handshake.
target_ap()
{
    read -p "Enter BSSID of Target-AP " bssid_ap
    echo $bssid_ap
}


# Check if the script is running as root
if [ "$EUID" -ne 0 ]; 
then
    echo -e "[ERROR]: This script must be run as root. Please use sudo or run as root."
    exit 1
fi

# Check for avilable wireless interfaces 

list=`airmon-ng | grep "wl" | awk '{print $2}'`
if [[ -z "$list" ]];     # To find out if a bash variable is empty (-z retn. 0 if true)
then
    echo "[ERROR]: No Wireless Adapter detected.... "

else
    ntw_inter=($list)
    echo "Available Wireless Interfaces are : "
    for ((i=0; i<${#ntw_inter[@]}; i++));
    do 
        echo "$i - ${ntw_inter[i]}"
    done

    read -p "Please select number of interface : " index 
    wifi_card=${ntw_inter[index]}

    ##############################################################################################
    echo "Turning $wifi_card into monitoring mode........"
    sudo airmon-ng start $wifi_card 
    sleep 3
    
    # Scanning for Wireless networks in monitoring mode or not
    list2=`iwconfig | grep "Mode:Monitor" | awk '{print $1}'`
    card_mon=($list2)

    if [[ -z "$card_mon" ]];     # To find out if a bash variable is empty (-z retn. 0 if true)
    then 
        echo "[ERROR]: Your Wifi Interface doesn't Support Monitoring Mode "
    
    elif [[ ${#card_mon[@]} -gt 1 ]];
    then 
        for ((i=0; i<${#card_mon[@]}; i++));
        do 
            echo "$i - ${card_mon[i]}"
        done
        read "selected any one mode : " index
        sudo airodump-ng ${card_mon[index]}

    else
        echo "Press CTRL+C to Stop scanning.. "
        trap 'target_ap' SIGINT      # For KEYBOARD Interrupt.. 
        sudo airodump-ng $card_mon

    fi 

fi 


