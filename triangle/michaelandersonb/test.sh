#!/bin/bash
echo "See code for test cases"
#Test if handling non-integers 
! echo "1 2 3 4 5 a" | ./triangle | grep -q error
echo "Test 1" $? 
#Test if handling for right number of args
! echo "1 2 3 4 5 6 7" | ./triangle | grep -q error
echo "Test 2" $? 
#Testing if buffer is large enough to accept any valid input and error if not valid
! echo "-1073741823 -1073741823 -1073741822 -1073741822 -1073741822 -10737418232" | ./triangle | grep -q error
echo "Test 3" $? 
#Error integer not allowed (should be possible though had it not been explicitly prohibited)
! echo "-1073741834 1073741834 -9223372036854775809 9223372036854775810 1073741822 1073741823" | ./triangle | grep -q error
echo "Test 4" $? 
#NAT straight large line
! echo "-1073741823 -1073741823 1073741823 1073741823 0 0" | ./triangle | grep -q "not a triangle"
echo "Test 5" $? 
#NAT equal coordinates
! echo "0 0 0 0 1073741823 1073741823" | ./triangle | grep -q "not a triangle"
echo "Test 6" $? 
#Obtuse
! echo "-1073741823 -1073741823 1073741822 1073741823 0 0" | ./triangle | grep -q "scalene obtuse"
echo "Test 7" $? 
#Right (Longest possible line)
! echo "-1073741823 -1073741823 1073741823 1073741823 1073741823 -1073741823" | ./triangle | grep -q "isosceles right"
echo "Test 8" $? 
#Rotated Right
! echo "-1073741823 1073741823 1073741823 1073741823 0 0" | ./triangle | grep -q "isosceles right"
echo "Test 9" $? 
#Rotated Obtuse
! echo "-1073741823 1073741823 1073741823 1073741822 0 0" | ./triangle | grep -q "scalene obtuse"
echo "Test 10" $?