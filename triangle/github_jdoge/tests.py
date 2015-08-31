# AUTHOR: Jared Potter (u0729256)
#
# DATE: August 31, 2015
#
# Python unittest tests for triangle_classifier.c


import os
from subprocess import Popen, PIPE
import unittest

class TriangleTests(unittest.TestCase):

  def testScaleneAcuteTriangl(self):
    myTriangle = Triangle('-1073741823 1073741823 -1073741823 -78374343 750234243 123412323'.split())
    self.assertEqual(myTriangle.executeTest(),'scalene acute\n')

  def testScaleneObtuseTriangl(self):
    myTriangle = Triangle('-1073741823 0 -500 1073741823 -400 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'scalene obtuse\n')

  def testIsoscelesAcuteTriangl(self):
    myTriangle = Triangle('-1073741823 0 0 3 0 -3'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles acute\n')    

  def testIsoscelesObtuseTriangl(self):
    myTriangle = Triangle('-1073741823 0 -500 1073741823 -500 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles obtuse\n')

  # top right  
  def testIsoscelesRightTriangle1(self):
    myTriangle = Triangle('-1073741823 1073741823 1073741823 -1073741823 1073741823 1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles right\n')

  # top left 
  def testIsoscelesRightTriangle2(self):
    myTriangle = Triangle('-1073741823 -1073741823 1073741823 -1073741823 1073741823 1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles right\n')

  # bottom right
  def testIsoscelesRightTriangle3(self):
    myTriangle = Triangle('-1073741823 1073741823 -1073741823 -1073741823 1073741823 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles right\n')

  # bottom left
  def testIsoscelesRightTriangle4(self):
    myTriangle = Triangle('-1073741823 1073741823 -1073741823 -1073741823 1073741823 1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles right\n')

  # left middle
  def testIsoscelesRightTriangle5(self):
    myTriangle = Triangle('-1073741823 0 0 1073741823 0 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'isosceles right\n')

  # vertical line
  def testColinear1(self):
    myTriangle = Triangle('0 1073741823 0 0 0 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'not a triangle\n')

  # horizontal line
  def testColinear1(self):
    myTriangle = Triangle('-1073741823 0 0 0 1073741823 0'.split())
    self.assertEqual(myTriangle.executeTest(),'not a triangle\n')

  # top left to bottom right
  def testColinear1(self):
    myTriangle = Triangle('-1073741823 1073741823 0 0 1073741823 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'not a triangle\n')

  # top right to bottom left
  def testColinear1(self):
    myTriangle = Triangle('1073741823 1073741823 0 0 -1073741823 -1073741823'.split())
    self.assertEqual(myTriangle.executeTest(),'not a triangle\n')

  def testSamePoints1(self):
    myTriangle = Triangle('0 0 0 0 3 4'.split())
    self.assertEqual(myTriangle.executeTest(), 'not a triangle\n')

  def testSamePoints2(self):
    myTriangle = Triangle('3 4 0 0 3 4'.split())
    self.assertEqual(myTriangle.executeTest(), 'not a triangle\n')

  def testSamePoints3(self):
    myTriangle = Triangle('0 0 12 -6 0 0'.split())
    self.assertEqual(myTriangle.executeTest(), 'not a triangle\n')

  def testInvlidCharacter1(self):
    myTriangle = Triangle('0 0 0 0 a 8'.split())
    self.assertEqual(myTriangle.executeTest(), 'error\n')

  def testInvlidCharacter2(self):
    myTriangle = Triangle('0 0 0 0 a 8'.split())
    self.assertEqual(myTriangle.executeTest(), 'error\n')

  def testInvlidCharacter3(self):
    myTriangle = Triangle('0 0 0 0 0@ 0'.split())
    self.assertEqual(myTriangle.executeTest(), 'error\n')

class Triangle:  
  def __init__(self, coordinates):
    self.args  = ['./triangle', coordinates[0], coordinates[1], coordinates[2], coordinates[3], coordinates[4], coordinates[5]]

  def triangle(self):
    return self.args

  def classifyTriangle(self):
	ps         = Popen(self.triangle(), stdout=PIPE)
	(out, err) = ps.communicate()
	exit_code  = ps.wait()
	return out

  def executeTest(self):
    self.out = self.classifyTriangle()
    return self.out

if __name__ == '__main__':
  unittest.main()