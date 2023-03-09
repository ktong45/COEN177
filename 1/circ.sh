# Kristin
# Sept 22, 2022
# Lab1 - areas of shapes
# compute area of circle

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "salagtash" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!" 
fi

response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of circle: "
        read radius
	r2=$(echo "$radius*$radius" | bc -l)
        pi=3.14
	area=$(echo "scale=2; $r2*$pi" | bc -l)
        echo "The area of the circle is $area"

        echo "Would you like to repeat for another circle [Yes/No]?"
        read response
done
