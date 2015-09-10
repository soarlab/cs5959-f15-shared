#!/bin/bash
printf "\n==Triangle Tester==\n"
PASS=0
FAIL=0

printf "\n-TEST 1-\nString: Hello 1 1 1 1 1\n\t"
output=$(./triangle Hello 1 1 1 1 1)
if [[ $output =~ "error" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 2-\nNot a Triangle: 1 2 3 4 5 6\n\t" 
output=$(./triangle 1 2 3 4 5 6)
if [[ $output =~ "not a triangle" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 3-\nNot a Triangle: 1073741823 1073741823 -1073741823 -1073741823 0 0\n\t"
output=$(./triangle 1073741823 1073741823 -1073741823 -1073741823 0 0)
if [[ $output =~ "not a triangle" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 4-\nNot a Triangle: 22 19 52 45 82 71\n\t"
output=$(./triangle 22 19 52 45 82 71)
if [[ $output =~ "not a triangle" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 5-\nNot Enough Arguments: NONE\n\t"
output=$(./triangle)
if [[ $output =~ "error" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 6-\nScalene Obtuse: 200 120 349 424 385 261\n\t"
output=$(./triangle 200 120 349 424 385 261)
if [[ $output =~ "scalene obtuse" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 7-\nScalene Obtuse: 1073741823 1073741823 -1073741823 -1073741823 0 1\n\t"
output=$(./triangle 1073741823 1073741823 -1073741823 -1073741823 0 1)
if [[ $output =~ "scalene obtuse" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 8-\nScalene Acute: 200 120 273 168 292 107\n\t"
output=$(./triangle 200 120 273 168 292 107)
if [[ $output =~ "scalene acute" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 9-\nScalene Right: 170 170 270 170 270 100\n\t"
output=$(./triangle 170 170 270 170 270 100)
if [[ $output =~ "scalene right" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 10-\nIsosceles Acute: 200 0 400 0 300 300\n\t"
output=$(./triangle 200 0 400 0 300 300)
if [[ $output =~ "isosceles acute" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1] 
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1] 
fi

printf "\n-TEST 11-\nIsosceles Right: 1073741823 1073741823 -1073741823 -1073741823 1073741823 -1073741823\n\t"
output=$(./triangle 1073741823 1073741823 -1073741823 -1073741823 1073741823 -1073741823)
if [[ $output =~ "isosceles right" ]]
	then
		printf "PASS\n\t"
		PASS=$[PASS + 1]
	else
		printf "FAIL\n\t"
		FAIL=$[FAIL + 1]
fi

TOTAL=$((PASS + FAIL))

printf "\n==Finished Testing==\n"
printf "PASSED: %s FAILED: %s TOTAL: %s\n\n" "$PASS" "$FAIL" "$TOTAL"
