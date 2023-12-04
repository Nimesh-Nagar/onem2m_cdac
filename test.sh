#! /bin/bash


interrupt_handler() 
{
    echo "Keyboard interrupt detected... Exiting bye..."
    exit 1
}


i=10
echo "This script is running. Press Ctrl+C to trigger a keyboard interrupt."

while [[ $i -gt 0 ]];
do 
    trap "interrupt_handler" SIGINT
    echo "value $i"
    i=$((i-1))
    sleep 2
    
done 

echo "outside $i"












########## [DONE]
# Scanning for Wireless networks
# card_mon=`iwconfig | grep "Mode:Monitor" | awk '{print $1}'`
# if [[ -z "$card_mon" ]];     # To find out if a bash variable is empty (-z retn. 0 if true)
# then 
#     echo "ERROR : Your Wifi Interface doesn't Support Monitoring Mode "
# fi 
# echo $card_mon

########## [DONE]

############## FOR LOOP ##################

# ntw_inter=`airmon-ng | grep "wl" | awk '{print $2}'`
# array=($ntw_inter)

# # i=0
# # for sr in "${array[@]}";
# # do 
# #     echo "$i - $sr" 
# #     i=$((i+1))
# # done 

# for ((i=0; i<${#array[@]}; i++));
# do 
#     echo "$i : ${array[i]}"
# done
# read -p "select: " index
# echo ${array[$index]}

# array=(nimesh)
# echo ${#array[@]}

# if [[ -z $array ]];
# then
#     echo "not supported"

# elif [[ ${#array[@]} -gt 1 ]];
# then
#     echo "Select any one "
#     for ((i=0; i<${#array[@]}; i++));
#     do 
#         echo "$i : ${array[i]}"
#     done 

#     read -p "select: " index 

# else
#     echo "ok done"
#     echo $array
# fi  

# echo ${array[@]}
# echo "selected interface = " ${array[index]}

