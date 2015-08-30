
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
echo "Test 3: All of the same points so not a triangle."
tester "$(./triangle 0 0 0 0 0 0)" "$NAT"
echo "Test 4: Points that are colinear so not a triangle."
tester "$(./triangle -25 25 0 0 25 -25)" "$NAT"
echo "Test 5: Triangle is Isosceles Obtuse."
tester "$(./triangle -25 25 1 1 25 -25)" "$IO"
echo "Test 6: Triangle is Isosceles Obtuse angle is just more then 90 degreed."
tester "$(./triangle -25 25 24 24 25 -25)" "$IO"
echo "Test 7: Triangle is Isosceles Acute angle is less more then 90 degreed."
tester "$(./triangle -25 25 26 26 25 -25)" "$IA"
echo "Test 8: Triangle is Scalene Right."
tester "$(./triangle -20 25 25 25 25 -25)" "$SR"
echo "Test 9: Triangle is Scalene Obtuse."
tester "$(./triangle -20 25 24 24 25 -25)" "$SO"
echo "Test 10: Check boundaries"
tester "$(./triangle $nb $b 1 1 $b $nb)" "$IO"
tester "$(./triangle $nb $b $b $b $b $nb)" "$IR"
let test=$b-1
tester "$(./triangle $nb $b $test $test $b $nb)" "$IO"
let ntest=$nb+1
tester "$(./triangle -1073741823 1073741823 1073741823 1073741823 1073741823 -1073741823)" "$IR"


tester "$(./triangle -1073741820 1073741823 1073741823 1073741823 1073741823 -1073741823)" "$SR"
tester "$(./triangle -1073741820 1073741823 1073741822 1073741822 1073741823 -1073741823)" "$SO"