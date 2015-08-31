#!/usr/bin/perl

use strict;
use warnings;

my $result0 = `./triangle -50 0 50 0 0 5`;

if($result0 =~ m/isosceles obtuse/){
  print "Isoceles Obtuse Test Passed\n";
}
else{
  print "Isoceles Obtuse Test Failed: -50 0 50 0 0 5 expected: \tisosceles obtuse\n\tresulted:\t\t$result0\n";
}
my $result1 = `./triangle 1073741823 1073741823 1073741823 -1073741823 -1073741823 -1073741823`;

if($result1 =~ m/isosceles right/){
  print "Isoceles Right Test Passed\n";
}
else{
  print "Isoceles Right Test Failed: 1073741823 1073741823 1073741823 -1073741823 -1073741823 -1073741823 expected: \tisosceles right\n\tresulted:\t\t$result1\n";
}
my $result2 = `./triangle 0 0 -1 1 1 0`;

if($result2 =~ m/scalene obtuse/){
  print "Scalene Obtuse Test Passed\n";
}
else{
  print "Test Failed: 0 0 0 -1 1 0 expected: \tscalene obtuse\n\tresulted:\t\t$result2\n";
}
my $result3 = `./triangle 0 2 1 1 2 -3`;

if($result3 =~ m/scalene acute/){
  print "Test Passed\n";
}
else{
  print "Test Failed: 0 2 1 1 2 -3  expected: \tscalene acute\n\tresulted:\t\t$result3\n";
}


my $result4 = `./triangle 0 0 1 1 1 `;

if($result4 =~ m/error/){
  print "Too Few Input Test Passed\n";
}
else{
  print "Test Failed: 0 0 0 1 1 0 expected: \tscalene acute\n\tresulted:\t\t$result4\n";
}
my $result5 = `./triangle 0 0 1 1 1 1 1`;

if($result5 =~ m/error/){
  print "Too Many Input Test Passed\n";
}
else{
  print "Test Failed: 0 0 0 1 1 0 expected: \tscalene acute\n\tresulted:\t\t$result5\n";
}
