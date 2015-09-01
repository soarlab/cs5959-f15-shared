# I used this shell script to test the output.
# I mainly check boundary conditions both between different 
# classifications and for integer boundaries. I probably 
# missed a lot but this is where I got.



function tester()
{
	#echo "$1"
	#echo "$2"
	if [ "$1" != "$2" ];
	then
		echo "$(tput setaf 1)FAIL! \n$1 $2 $(tput sgr0)"
	else
		echo "$(tput setaf 2)PASS! $(tput sgr0)"
	fi


}




EA="equilateral acute"
SO="scalene obtuse"
SR="scalene right"
SA="scalene acute"
IA="isosceles acute"
IO="isosceles obtuse"
IR="isosceles right"
NAT="not a triangle"
E="error"
 
let b=1073741823
let nb=-1073741823
echo "Test 1: For less then six arguments."
tester  "$(./triangle 0)" "$E"
echo "Test 2: For too many arguments."
tester "$(./triangle 0 0 0 0 0 0 0)" "$E"
echo "Test 3: For non-integer arguments."
tester "$(./triangle we re qw vf as 3)" "$E"
echo "Test 4: All of the same points so not a triangle."
tester "$(./triangle 0 0 0 0 0 0)" "$NAT"
echo "Test 5: Points that are colinear so not a triangle."
tester "$(./triangle -25 25 0 0 25 -25)" "$NAT"
echo "Test 6: Triangle is Isosceles Obtuse."
tester "$(./triangle -25 25 1 1 25 -25)" "$IO"
echo "Test 7: Triangle is Isosceles Obtuse angle is just more then 90 degreed."
tester "$(./triangle -25 25 24 24 25 -25)" "$IO"
echo "Test 8: Triangle is Isosceles Acute angle is less more then 90 degreed."
tester "$(./triangle -25 25 26 26 25 -25)" "$IA"
echo "Test 9: Triangle is Scalene Right."
tester "$(./triangle -20 25 25 25 25 -25)" "$SR"
echo "Test 10: Triangle is Scalene Obtuse."
tester "$(./triangle -20 25 24 24 25 -25)" "$SO"
echo "Test 11: Check boundaries"
# 1
tester "$(./triangle $nb $b 1 1 $b $nb)" "$IO"
# 2
tester "$(./triangle $nb $b $b $b $b $nb)" "$IR"
# 3
let test=$b-1
tester "$(./triangle $nb $b $test $test $b $nb)" "$IO"
# 4
let test=$b-1
let ntest=$nb+1
tester "$(./triangle $ntest 0 0 $b $test 0)" "$IA"
# 5
tester "$(./triangle $ntest $b $b $b $b $nb)" "$SR"
# 6
let ntest=$nb+3
tester "$(./triangle $ntest $b $test $test $b $b)" "$SO"
echo Last
tester "$(./triangle $nb $nb $b $nb $b $b)" "$IR"