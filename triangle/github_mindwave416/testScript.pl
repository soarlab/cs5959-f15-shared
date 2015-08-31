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
  print "Scalene Obtuse Test Failed: 0 0 0 -1 1 0 expected: \tscalene obtuse\n\tresulted:\t\t$result2\n";
}
my $result3 = `./triangle -10 0 10 0 0 25`;

if($result3 =~ m/isosceles acute/){
  print "Isosceles Acute Test Passed\n";
}
else{
  print "Isosceles Acute Test Failed: -10 0 10 0 0 25  expected: \tisosceles acute\n\tresulted:\t\t$result3\n";
}
my $result4 = `./triangle 0 0 1 1 1 `;

if($result4 =~ m/error/){
  print "Too Few Input Test Passed\n";
}
else{
  print "Too Few Input Test Failed: 0 0 1 1 1 expected: \terror\n\tresulted:\t\t$result4\n";
}
my $result5 = `./triangle 0 0 1 1 1 1 1`;

if($result5 =~ m/error/){
  print "Too Many Input Test Passed\n";
}
else{
  print "Too Many Input Test Failed: 0 0 1 1 1 1 1 expected: \terror\n\tresulted:\t\t$result5\n";
}
my $result6 = `./triangle 15 6 25 6 100 6 `;

if($result6 =~ m/not a triangle/){
  print "Not a Triangle Y Axis Test Passed\n";
}
else{
  print "Not a Triangle Y Axis Test Failed: 15 6 25 6 100 6 expected: \tnot a triangle\n\tresulted:\t\t$result6\n";
}
my $result7 = `./triangle 0 0 0 1 0 3 `;

if($result7 =~ m/not a triangle/){
  print "Not a Triangle X Axis Test Passed\n";
}
else{
  print "Not a Triangle X Axis Test Failed: 0 0 0 1 0 3 expected: \tnot a triangle\n\tresulted:\t\t$result7\n";
}
my $result8 = `./triangle foo bar 0 1 0 3 `;

if($result8 =~ m/error/){
  print "Non Integer Input Test Passed\n";
}
else{
  print "Non Integer Input Test Failed: foo bar 0 1 0 3 expected: \terror\n\tresulted:\t\t$result8\n";
}
my $result9 = `./triangle 0 1 0 0 3 0 `;

if($result9 =~ m/scalene right/){
  print "Scalene Right Test Passed\n";
}
else{
  print "Scalene Right Test Failed: 0 1 0 0 3 0 expected: \tScalene Right\n\tresulted:\t\t$result9\n";
}
