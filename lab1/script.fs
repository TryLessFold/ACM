#!/bin/bash

echo " Дата: " `date`
echo " Имя учётной записи: " `echo $USER`
echo " Доменное имя ПК: "`hostname`

echo " Процессор: "
TMP=`lscpu | grep "Имя модели"`
printf "%7s  " •
echo ${TMP/"Имя модели:"/"Модель - "}

TMP=`lscpu | grep "Архитектура"`
printf "%7s  " •
echo ${TMP/"Архитектура:"/"Архитектура - "}

TMP=`lscpu | grep -m 1 "CPU max MHz"`
printf "%7s  " •
echo ${TMP/"CPU max MHz:"/"Тактовая частота - "}

TMP=`lscpu | grep "CPU(s):"`
printf "%7s  " •
echo ${TMP/"CPU(s):"/"Количество ядер - "}

TMP=`lscpu | grep "Thread(s) per core:"`
printf "%7s  " •
echo ${TMP/"Thread(s) per core:"/"Количество потоков на одно ядро - "}

echo " Оперативная память: "
read -r _ TOTAL _ FREE _ <<< `free -h | grep "Mem:"`
printf "%7s  " •
echo "Всего - " $TOTAL

TMP=`lscpu | grep "Архитектура"`
printf "%7s  " •
echo "Свободно - " $FREE

echo " Жесткий диск: "
read -r _ TOTAL _ FREE _ DIRECTORY <<< `df -h | grep "/dev/sda3"`
printf "%7s  " •
echo "Всего - " $TOTAL

printf "%7s  " •
echo "Свободно - " $FREE

printf "%7s  " •
echo "Директория - " $DIRECTORY

read -r _ TOTAL _ FREE _ <<< `free -h | grep "Swap:"`
printf "%7s  " •
echo "SWAP всего - " $TOTAL

printf "%7s  " •
echo "SWAP доступно - " $FREE

echo " Сетевые интерфейсы: "
printf "%7s  " •
echo " Количество сетевых интерфейсов - "
#TMP=``
#TMP=${${ifconfig |cut -d ' ' -f1| awk '{printf $1}}//:/ }

for i in $(ifconfig| cut -d ' ' -f1| tr ':' ' '| awk NF)
do
	echo $i
done
