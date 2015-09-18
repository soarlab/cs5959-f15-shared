 # 
 # AUTHOR :     Taylor Wilson
 # UID :        U0323893
 # 
 # DATE :       August 29, 2015
 # 
 # PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 #              University of Utah
 #

import re
import os
from subprocess import Popen, PIPE
import unittest

class Types:
  SCA = 'scalene'
  ISO = 'isosceles'
  EQU = 'equilateral'
  ACU = 'acute'
  OBT = 'obtuse'
  RIG = 'right'
  NAT = 'not a triangle\n'
  ERR = 'error\n'

# ==============================================================================================================
# Test Class
# ==============================================================================================================

class TestTriangle(unittest.TestCase):

  pattern  = '(((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle|error)\n'
  triangle = None

  def setUp(self):
    pass

  def tearDown(self):
    pass

  # ============================================================================================================
  # Assertion Helpers: 
  # ============================================================================================================

  def assertSubType(self, subType):
    self.assertTrue(re.match(self.pattern, self.triangle.output()))
    if subType == Types.ACU:
      self.assertEqual(self.triangle.subType, Types.ACU)
    elif subType == Types.RIG:
      self.assertEqual(self.triangle.subType, Types.RIG)
    elif subType == Types.OBT:
      self.assertEqual(self.triangle.subType, Types.OBT)

  def assertIsosceles(self, subType):
    self.triangle.build()
    self.assertEqual(self.triangle.priType, Types.ISO)
    self.assertSubType(subType)

  def assertScalene(self, subType):
    self.triangle.build()
    self.assertEqual(self.triangle.priType, Types.SCA)
    self.assertSubType(subType)

  def assertError(self):
    self.triangle.build()
    self.assertTrue(re.match(self.pattern, self.triangle.output()))
    self.assertEqual(self.triangle.output(), Types.ERR)

  def assertNotATriangle(self):
    self.triangle.build()
    self.assertTrue(re.match(self.pattern, self.triangle.output()))
    self.assertEqual(self.triangle.output(), Types.NAT)

  # ============================================================================================================
  # Test Cases for bad inputs
  # ============================================================================================================

  def testNoArgs(self):
    self.triangle = Triangle('0 0 0 0 0 0'.split())
    self.triangle.erasePoints()
    self.assertError()

  def testExcessArgs(self):
    self.triangle = Triangle('0 0 0 0 0 0'.split())
    self.triangle.addPoint('1')
    self.assertError()

  def testMissingArgs(self):
    self.triangle = Triangle('0 0 0 0 0 0'.split())
    self.triangle.removePoint('0')
    self.assertError()

  def testInvalidChars(self):
    self.triangle = Triangle('0 0 0 0* 0 0'.split())
    self.assertError()

  def testNegativeSign(self):
    self.triangle = Triangle('-1 -1 0 0 -1 1'.split())
    self.assertIsosceles(Types.RIG)

  def testLeadingZeros(self):
    self.triangle = Triangle('00000000000000000000001 0 0 000 0000000 01'.split())
    self.assertIsosceles(Types.RIG)

  def testOverflowArgs(self):
    self.triangle = Triangle('1 2 3 4 0 1073741824'.split())
    self.assertError()

  def testUnderflowArgs(self):
    self.triangle = Triangle('1 2 3 4 0 -1073741824'.split())
    self.assertError()

  def testDuplicatePoints1(self):
    self.triangle = Triangle('-1073741823 1073741823 -1073741823 1073741823 1073741823 1073741823'.split())
    self.assertNotATriangle()

  def testDuplicatePoints2(self):
    self.triangle = Triangle('-1073741823 1073741823 -1073741823 1073741823 -1073741823 1073741823'.split())
    self.assertNotATriangle()

  def testVerticalLine(self):
    self.triangle = Triangle('0 -123456789 0 0 0 123456789'.split())
    self.assertNotATriangle()

  def testHorizontalLine(self):
    self.triangle = Triangle('-987654321 0 0 0 987654321 0'.split())
    self.assertNotATriangle()

  def testDiagonalLine1(self):
    self.triangle = Triangle('0 100000033 100000033 0 200000066 -100000033'.split())
    self.assertNotATriangle()

  def testDiagonalLine2(self):
    self.triangle = Triangle('0 0 -123456789 -123456789 123456789 123456789'.split())
    self.assertNotATriangle()

  # ============================================================================================================
  # Test Cases Isosceles Triangles
  # ============================================================================================================

  def testIsoscelesAcute(self):
    self.triangle = Triangle('-1073741822 0 0 1073741823 1073741822 0'.split())
    self.assertIsosceles(Types.ACU)

  def testIsoscelesRight(self):
    self.triangle = Triangle('0 1073741823 -1073741823 0 1073741823 0'.split())
    self.assertIsosceles(Types.RIG)

  def testIsoscelesObtuse1(self):
    self.triangle = Triangle('0 1073741822 -1073741823 0 1073741823 0'.split())
    self.assertIsosceles(Types.OBT)

  def testIsoscelesObtuse2(self):
    self.triangle = Triangle('-1073741823 0 0 -1 1073741823 0'.split())
    self.assertIsosceles(Types.OBT)

  # ============================================================================================================
  # Test Cases Scalene Triangles
  # ============================================================================================================

  def testScaleneAcute(self):
    self.triangle = Triangle('-1073741823 -1073741823 -1073741822 1073741822 0 -1073741822'.split())
    self.assertScalene(Types.ACU)

  def testScaleneRight(self):
    self.triangle = Triangle('-1073741822 -1073741822 -1073741822 1073741822 0 -1073741822'.split())
    self.assertScalene(Types.RIG)

  def testScaleneObtuse1(self):
    self.triangle = Triangle('-1073741822 -1073741821 -1073741822 1073741822 0 -1073741822'.split())
    self.assertScalene(Types.OBT)

  def testScaleneObtuse2(self):
    self.triangle = Triangle('-1073741823 -1073741823 -1073741822 -1073741823 1073741823 1073741823'.split())
    self.assertScalene(Types.OBT)

  # arg! what integer points form an equilateral triangle ???
  # def equilateral(self):
  #   triangle = Triangle('? ? ? ? ? ?'.split())
  #   triangle.build()
  #   self.assertEqual(triangle.priType, Types.EQU)
  #   self.assertEqual(triangle.subType, Types.ACU)

# ==============================================================================================================
# Triangle Class
# ==============================================================================================================

class Triangle:  
  def __init__(self, pts):
    self.args  = ['./triangle', pts[0], pts[1], pts[2], pts[3], pts[4], pts[5]]
    self.priType = None
    self.subType = None

  def erasePoints(self):
    self.args = ['./triangle', '']

  def removePoint(self, value):
    if len(self.args) > 1:
      self.args.remove(value)

  def addPoint(self, pt):
    self.args.append(pt)

  def triangle(self):
    return self.args

  def execTri(self):
    ps         = Popen(self.triangle(), stdout=PIPE)
    (out, err) = ps.communicate()
    exit_code  = ps.wait()
    return out

  def build(self):
    self.out = self.execTri()
    if len(self.out.split()) == 2:
      self.priType = self.out.split()[0]
      self.subType = self.out.split()[1]

  def output(self):
    return self.out

# ==============================================================================================================
# Executes from here
# ==============================================================================================================

if __name__ == '__main__':
  unittest.main()
