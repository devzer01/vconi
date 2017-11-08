#!/bin/bash
make all
sudo rm -f /home/nayana/code/sinhala-os/charset/vconi/output/devan_on.txt
sudo rm -f /home/nayana/code/sinhala-os/charset/vconi/output/devan.txt
./bin/convert -l d -d f -f /home/nayana/code/sinhala-os/charset/vconi/input/devan.txt -t /home/nayana/code/sinhala-os/charset/vconi/output/devan_on.txt
sudo chmod 666  /home/nayana/code/sinhala-os/charset/vconi/output/devan_on.txt
./bin/convert -l d -d b -f /home/nayana/code/sinhala-os/charset/vconi/output/devan_on.txt -t /home/nayana/code/sinhala-os/charset/vconi/output/devan.txt
sudo chmod 666  /home/nayana/code/sinhala-os/charset/vconi/output/devan.txt

sudo rm -f /home/nayana/code/sinhala-os/charset/vconi/output/bangla_on.txt
sudo rm -f /home/nayana/code/sinhala-os/charset/vconi/output/bangla.txt
./bin/convert -l b -d f -f /home/nayana/code/sinhala-os/charset/vconi/input/bangla.txt -t /home/nayana/code/sinhala-os/charset/vconi/output/bangla_on.txt
sudo chmod 666  /home/nayana/code/sinhala-os/charset/vconi/output/bangla_on.txt
./bin/convert -l b -d b -f /home/nayana/code/sinhala-os/charset/vconi/output/bangla_on.txt -t /home/nayana/code/sinhala-os/charset/vconi/output/bangla.txt
sudo chmod 666  /home/nayana/code/sinhala-os/charset/vconi/output/bangla.txt

ls -al output/

./bin/compare ./output/devan_on.txt ./output/bangla_on.txt
mv p1.txt dp1.txt
mv p2.txt bp2.txt
./bin/compare ./output/bangla_on.txt ./output/devan_on.txt
mv p1.txt bp1.txt
mv p2.txt dp2.txt

#./bin/convert -l d -d b -t output/devan.txt -f output/devan_on.txt
#./bin/convert -l b -d b -t output/bangla.txt -f output/bangla_on.txt
