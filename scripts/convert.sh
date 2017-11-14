#!/bin/bash

OUTPUT=/home/nayana/code/sinhala-os/charset/vconi/data/output
DEVANGARI=0x0900
BANGLA=0x0980
SINHALA=0x0D80
TAMIL=0x0B80

DEVANGARI_ALPHA=$OUTPUT/devangari_alphabet.txt
BANGLA_ALPHA=$OUTPUT/bengali_alphabet.txt
TAMIL_ALPHA=$OUTPUT/tamil_alphabet.txt

DEVANGARI_ALPHA_B8E=$OUTPUT/devangari_alphabet.b8e.txt
BANGLA_ALPHA_B8E=$OUTPUT/bengali_alphabet.b8e.txt
TAMIL_ALPHA_B8E=$OUTPUT/tamil_alphabet.b8e.txt

DEVANGARI_ALPHA_B8ER=$OUTPUT/devangari_alphabet.b8er.txt
BANGLA_ALPHA_B8ER=$OUTPUT/bengali_alphabet.b8er.txt
TAMIL_ALPHA_B8ER=$OUTPUT/tamil_alphabet.b8er.txt

#generate all
./bin/generate -l $DEVANGARI -c 0x0915 > $DEVANGARI_ALPHA
./bin/generate -l $BANGLA -c 0x0995 > $BANGLA_ALPHA
./bin/generate -l $TAMIL -c 0x0B95 > $TAMIL_ALPHA

#forward all
./bin/convert -l d -d f -f $DEVANGARI_ALPHA -t $DEVANGARI_ALPHA_B8E
./bin/convert -l b -d f -f $BANGLA_ALPHA -t $BANGLA_ALPHA_B8E
./bin/convert -l t -d f -f $TAMIL_ALPHA -t $TAMIL_ALPHA_B8E

#reverse all
./bin/convert -l d -d b -f $DEVANGARI_ALPHA_B8E -t $DEVANGARI_ALPHA_B8ER
./bin/convert -l b -d b -f $BANGLA_ALPHA_B8E -t $BANGLA_ALPHA_B8ER
./bin/convert -l t -d b -f $TAMIL_ALPHA_B8E -t $TAMIL_ALPHA_B8ER

echo -ne "checking bangla map correction - "
diff -qa $BANGLA_ALPHA $BANGLA_ALPHA_B8ER
echo -ne "checking devangari map correction - "
diff -qa $DEVANGARI_ALPHA $DEVANGARI_ALPHA_B8ER
echo -ne "checking tamil map correction - "
diff -qa $TAMIL_ALPHA $TAMIL_ALPHA_B8ER