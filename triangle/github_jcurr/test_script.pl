#!/usr/bin/perl

use strict;
use warnings;

my $test_count = 0;
my $passed = 0;
my $expected = "";
my $result = "";
my $program = "./triangle";
my $args = "";

print "***************** Testing *****************\n";

### Test orientations
# Test right small ----------------------------------------------------------------------------------
$args = "1 1 0 0 0 1";
$expected = "isosceles right";
test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "1 1 0 1 0 0";
$expected = "isosceles right";
test_and_print();

# Test right small ----------------------------------------------------------------------------------
$args = "0 0 0 1 1 1";
$expected = "isosceles right";
test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "0 0 1 1  0 1";
$expected = "isosceles right";

test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "0 1 1 1 0 0";
$expected = "isosceles right";
test_and_print();

# Test right small ----------------------------------------------------------------------------------
$args = "0 1 0 0 1 1";
$expected = "isosceles right";
test_and_print();

# Test right small ----------------------------------------------------------------------------------
$args = "-1 -1 0 0 0 -1";
$expected = "isosceles right";
test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "-1 -1 0 -1 0 0";
$expected = "isosceles right";
test_and_print();

# Test right small ----------------------------------------------------------------------------------
$args = "0 0 0 -1 -1 -1";
$expected = "isosceles right";
test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "0 0 -1 -1  0 -1";
$expected = "isosceles right";

test_and_print();
# Test right small ----------------------------------------------------------------------------------
$args = "0 -1 -1 -1 0 0";
$expected = "isosceles right";
test_and_print();

# Test right small ----------------------------------------------------------------------------------
$args = "0 -1 0 0 -1 -1";
$expected = "isosceles right";
test_and_print();


### Test right
# Test right small ----------------------------------------------------------------------------------
$args = "0 0 1 1 0 1";
$expected = "isosceles right";
test_and_print();

# Test right extreme----------------------------------------------------------------------------------
$args = "0 -1073741823 1 -1073741823 0 1073741823";
$expected = "scalene right";
test_and_print();

### Test obtuse
# Test obtuse small----------------------------------------------------------------------------------
$args = "0 0 -10 1 10 1";
$expected = "isosceles right";

### Test acute
# Test acute small---------------------------------------------------------------------------------
$args = "1 0 0 2 -1 0";
$expected = "isosceles acute";
test_and_print();

### Test not a triangle
# Test not a triangle x axis----------------------------------------------------------------------------------
$args = "1 0 1 3 1 78";
$expected = "not a triangle";
test_and_print();

# Test not a triangle y axis----------------------------------------------------------------------------------
$args = "12 9 434 9 3124 9";
$expected = "not a triangle";
test_and_print();

# Test not a triangle negative slope----------------------------------------------------------------------------------
$args = "0 10 5 5 10 0";
$expected = "not a triangle";
test_and_print();

# Test not a triangle positive slope----------------------------------------------------------------------------------
$args = "1 1 2 2 3 3";
$expected = "not a triangle";
test_and_print();


### Test error
# Test error out of range positive----------------------------------------------------------------------------------
$args = "1 1 2 0 1 1073741824";
$expected = "error";
test_and_print();

# Test error out of range negative----------------------------------------------------------------------------------
$args = "1 1 2 0 1 -1073741824";
$expected = "error";
test_and_print();

# Test error too few arguments----------------------------------------------------------------------------------
$args = "1 1 2 0 1";
$expected = "error";
test_and_print();

# Test error too many arguments----------------------------------------------------------------------------------
$args = "1 1 2 0 1 3 10737418249999999999";
$expected = "error";
test_and_print();

# Test error invalid integer----------------------------------------------------------------------------------
$args = "1 1 2s 0 1 1073741824";
$expected = "error";
test_and_print();

# Test error invalid integer----------------------------------------------------------------------------------
$args = "1 1 2 0 1 107.24";
$expected = "error";
test_and_print();

sub test_and_print{

$test_count++;
$result = `$program $args`;

if($result =~ m/$expected/)
  {
    $passed++;
  }
else
  {
    print "Test #$test_count Failed: $args\n\texpected:\t$expected\n\tactual:\t\t$result\n";
  }
}

###############
# print summary
if($passed == $test_count)
  {
    print "!!!\tAll Tests Passed\t\t!!!\n*******************************************\n";
  }
else
  {
    my $failed = $test_count - $passed;
    print "***\tFailed $failed / $test_count Tests\t\t***\n*******************************************\n";
  }
                                                                                                               178,3         Bot
