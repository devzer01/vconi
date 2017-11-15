#!/usr/bin/env bash

for lang in `cat scripts/.langs`
do
    START=`echo $lang | cut -d',' -f1`
    CONSO=`echo $lang | cut -d',' -f2`
    ID=`echo $lang | cut -d',' -f3`
    NAME=`echo $lang | cut -d',' -f4`

   ./bin/generate -l $START -c $CONSO > data/output/$NAME-$ID-alpha.txt
   ./bin/convert -l $ID -d f -f data/output/$NAME-$ID-alpha.txt -t data/output/$NAME-$ID-alpha.txt8
   ./bin/convert -l $ID -d b -f data/output/$NAME-$ID-alpha.txt8 -t data/output/$NAME-$ID-alpha.txt-re
   diff data/output/$NAME-$ID-alpha.txt-re data/output/$NAME-$ID-alpha.txt > data/report/$NAME-basic.txt
   AGGR=`wc -l data/report/$NAME-basic.txt`
    echo "$NAME $AGGR " >> data/report/all.txt
done





















