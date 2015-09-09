 #Dustin Jay Tuckett
 #U0204088
 #September 9th, 2015
import re
import os
from subprocess import Popen, PIPE

def execute( points ):
    arguments = ['./triangle', points[0], points[1], points[2], points[3], points[4], points[5]]
    ps         = Popen(arguments, stdout=PIPE)
    (out, err) = ps.communicate()
    exit_code  = ps.wait()
    return out
def execute7(  points ):
  arguments = ['./triangle', points[0], points[1], points[2], points[3], points[4], points[5], points[6]]
  ps         = Popen(arguments, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out

def execute5(  points ):
  arguments = ['./triangle', points[0], points[1], points[2], points[3], points[4]]
  ps         = Popen(arguments, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out

def test( testname, expected, points, argCount ):
  result = ''
  if ( argCount > 6):
    result = execute7( points )
  elif (argCount < 6 ):
    result = execute5( points )
  else:
    result = execute( points )
  print( testname )
  if ( expected in result ):
    print( "Pass ")
  else: 
    print( "Fail!  Expected:  %s, Received: %s"% (expected, result) )




test( "Test for scalene acute", "scalene acute", ['2', '1', '1', '-2', '-1', '1'] ,6)
test( "Test for scalene obtuse", "scalene obtuse",['0', '0', '1', '5', '-1', '1'] ,6)
test( "Test for scalene right", "scalene right",['1', '1', '3', '1', '1', '0'] ,6)
test( "Test for isosceles acute", "isosceles acute",['0', '0', '1', '2', '-1', '1'] ,6)
test( "Test for isosceles obtuse", "isosceles obtuse",['866', '0', '0', '0', '433', '250'] ,6)
test( "Test for isosceles right", "isosceles right",['0', '0', '0', '1', '1', '1'] ,6)
test( "Test for barely acute", "acute",['-1073741823', '-1073741823', '1073741823', '-1073741823', '1073741821', '1073741821'] ,6)
test( "Test for barely obtuse", "obtuse",['-1073741822', '-1073741822', '1073741822', '-1073741822', '1073741823', '1073741823'] ,6)
test( "Test for largest allowed", "isosceles right",['-1073741823', '-1073741823', '1073741823', '-1073741823', '1073741823', '1073741823'] ,6)
test( "Test for invalid (a point is too big)", "error",['-1073741823', '-1073741823', '1073741823', '-1073741823', '1073741823', '1073741824'] ,6)
test( "Test for invalid (not a number)", "error",['-1073741821', '-1073741821', '1073741821', '-1073741821', '1073741821', 'a'] ,6)
test( "Test for too many arguments", "error",['-1073741821', '-1073741821', '1073741821', '-1073741821', '1073741821', '1073741821', '1073741821'], 7)
test( "Test for too few arguments", "error",['-1073741821', '-1073741821', '1073741821', '-1073741821', '1073741821'], 5)
test( "Test for all the same point", "not a triangle",['-1073741821', '-1073741821', '-1073741821', '-1073741821', '-1073741821', '-1073741821'] ,6)
test( "Test for collinear points", "not a triangle",['0', '0', '1', '1', '2', '2'] ,6)