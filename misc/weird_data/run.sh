#! /bin/bash

while true; 
do
    nc -klq 1 0.0.0.0 6789 < "./chal"
  sleep 1
done
