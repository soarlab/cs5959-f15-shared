#!/bin/bash
printf "\n==Triangle Tester==\n"

printf "\n-TEST 1-\nInput String:\n\t"
./triangle Hello 1 1 1 1 1

printf "\n-TEST 2-\nInput Not a Triangle:\n\t" 
./triangle 1 2 3 4 5 6

printf "\n-TEST 3-\nInput Not a Triangle:\n\t"
./triangle 1073741823 1073741823 -1073741823 -1073741823 0 0

printf "\n-TEST 4-\nInput Not a Triangle:\n\t"
./triangle  22 19 52 45 82 71

printf "\n-TEST 5-\nInput Not Enough Arguments:\n\t"
./triangle

printf "\n-TEST 6-\nInput Scalene Obtuse:\n\t"
./triangle 200 120 349 424 385 261

printf "\n-TEST 7-\nInput Scalene Obtuse:\n\t"
./triangle 1073741823 1073741823 -1073741823 -1073741823 0 1

printf "\n-TEST 8-\nInput Scalene Acute:\n\t"
./triangle  200 120 273 168 292 107

printf "\n-TEST 9-\nInput Scalene Right:\n\t"
./triangle 170 170 270 170 270 100

printf "\n-TEST 10-\nInput Isosceles Acute:\n\t"
./triangle  200 0 400 0 300 300

printf "\n-TEST 11-\nInput Isosceles Right:\n\t"
./triangle 1073741823 1073741823 -1073741823 -1073741823 1073741823 -1073741823

printf "\n==Finished Testing==\n\n"
