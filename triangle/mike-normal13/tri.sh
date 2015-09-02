
#!/bin/bash
output1="$(./triangle 0 0 0 1 1 0)"
if [ "$output1" = "isosceles right" ]
	then
	echo "test 1 passed"
else
	echo "test 1 failed"
#echo $output1 

fi

output2="$(./triangle -5 1 5 1 0 0)"
if [ "$output2" = "isosceles obtuse" ]
	then
	echo "test 2 passed"
else
	echo "test 2 failed"
fi

output3="$(./triangle -1 5 1 5 0 0)"
if [ "$output3" = "isosceles acute" ]
	then
	echo "test 3 passed"
else
	echo "test 3 failed"
fi

output4="$(./triangle 0 0 0 3 5 0)"
if [ "$output4" = "scalene right" ]
	then
	echo "test 4 passed"
else
	echo "test 4 failed"
fi

output5="$(./triangle 5 0 0 0 0 5)"
if [ "$output5" = "isosceles right" ]
	then
	echo "test 5 passed"
else
	echo "test 5 failed"
fi

output6="$(./triangle 0 30 -10 0 10 11)"
if [ "$output6" = "scalene obtuse" ]
	then
	echo "test 6 passed"
else
	echo "test 6 failed"
fi

# barely obtuse
output7="$(./triangle -1001 4000 0 0 3000 0)"
if [ "$output7" = "scalene obtuse" ]
	then
	echo "test 7 passed"
else
	echo "test 7 failed"
fi

output8="$(./triangle 1 1 2 2 3 3)"
if [ "$output8" = "not a triangle" ]
	then
	echo "test 8 passed"
else
	echo "test 8 failed"
fi

# identical points
output9="$(./triangle 1 1 1 1 3 3)"
if [ "$output9" = "not a triangle" ]
	then
	echo "test 9 passed"
else
	echo "test 9 failed"
fi

# barely acute
output10="$(./triangle 1001 4000 0 0 3000 0)"
if [ "$output10" = "scalene acute" ]
	then
	echo "test 10 passed"
else
	echo "test 10 failed"
fi

output11="$(./triangle 1001 4000 0 0 3000 )"
if [ "$output11" = "error" ]
	then
	echo "test 11 passed"
else
	echo "test 11 failed"
fi

output12="$(./triangle 1001 4000 0 0 3000 h )"
if [ "$output12" = "error" ]
	then
	echo "test 12 passed"
else
	echo "test 12 failed"
fi

output13="$(./triangle 1073741824 0 0 1073741824 0 0)"
if [ "$output13" = "error" ]
	then
	echo "test 13 passed"
else
	echo "test 13 failed"
fi

output14="$(./triangle 1073741823 0 0 1073741823 0 0)"
if [ "$output14" = "isosceles right" ]
	then
	echo "test 14 passed"
else
	echo "test 14 failed"
fi

output15="$(./triangle 1073741823 0 0 -1073741823 0 0)"
if [ "$output15" = "isosceles right" ]
	then
	echo "test 15 passed"
else
	echo "test 15 failed"
fi

output16="$(./triangle -1073741823 0 0 -1073741823 0 0)"
if [ "$output16" = "isosceles right" ]
	then
	echo "test 16 passed"
else
	echo "test 16 failed"
fi

output17="$(./triangle -1073741823 5 1073741823 5 0 -1)"
if [ "$output17" = "isosceles obtuse" ]
	then
	echo "test 17 passed"
else
	echo "test 17 failed"
fi
