#!/bin/bash 
fail=0
pass=0
testCount=0
#scalene acute
echo Test Scalene Acute: 
testCount=$[testCount + 1]
testVar=$(./triangle 2 1 1 -2 -1 1)
if [[ $testVar =~ "scalene acute" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#scalene obtuse
echo Test Scalene Obtuse
testCount=$[testCount + 1]
testVar=$(./triangle 0 0 1 5 -1 1)
if [[ $testVar =~ "scalene obtuse" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#scalene right
echo Test Scalene Right
testCount=$[testCount + 1]
testVar=$(./triangle 1 1 3 1 1 0)
if [[ $testVar =~ "scalene right" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#isosceles acute
echo Test Isosceles Acute
testCount=$[testCount + 1]
testVar=$(./triangle 0 0 1 2 -1 1 )
if [[ $testVar =~ "isosceles acute" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#isosceles obtuse
echo Test Isosceles Obtuse
testCount=$[testCount + 1]
testVar=$(./triangle 866 0 0 0 433 250)
if [[ $testVar =~ "isosceles obtuse" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#isosceles right
echo Test Isosceles Right
testCount=$[testCount + 1]
testVar=$(./triangle 0 0 0 1 1 1)
if [[ $testVar =~ "isosceles right" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi

#equilateral acute
echo Test Equilateral Acute
testCount=$[testCount + 1]
testVar=$(./triangle 0 0 0 1 1 1)
if [[ $testVar =~ "isosceles right" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test just barely acute
echo Test Barely Acute
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741821 1073741821)
if [[ $testVar =~ "acute" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test just barely obtuse
echo testVar Barely Obtuse
testCount=$[testCount + 1]
testVar=$(./triangle -1073741822 -1073741822 1073741822 -1073741822 1073741823 1073741823)
if [[ $testVar =~ "obtuse" ]]
	then
 		echo pass
 		pass=$[pass + 1] 
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test largest valid
echo testVar Largest Allowed Triangle
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 1073741823)
if [[ $testVar =~ "error" ]]
	then
 		echo fail
 		fail=$[fail + 1] 
 	else
 		echo pass
 		pass=$[pass + 1]
fi
#testVar invalid ( a point is too big)
echo Test Invalid -- a point is too big 
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 1073741824)
if [[ $testVar =~ "error" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test invalid ( not a number )
echo Test Invalid -- not a number 
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 a)
if [[ $testVar =~ "error" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test too many arguments
echo Test too many arguments
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 1073741823 a)
if [[ $testVar =~ "error" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi

#test too few arguments
echo Test too few arguments
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 )
if [[ $testVar =~ "error" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test all same point
echo Test all the same point
testCount=$[testCount + 1]
testVar=$(./triangle -1073741823 -1073741823 -1073741823 -1073741823 -1073741823 -1073741823 )
if [[ $testVar =~ "not a triangle" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi
#test collinear
echo Test collienar points
testCount=$[testCount + 1]
testVar=$(./triangle 0 0 1 1 2 2 )
if [[ $testVar =~ "not a triangle" ]]
	then
 		echo pass
 		pass=$[pass + 1] 		
 	else
 		echo fail
 		fail=$[fail + 1] 
fi

echo $pass of the $testCount tests passed. $fail failed.





