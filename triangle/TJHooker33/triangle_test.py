 # *******************************************************************************************
 # AUTHOR :     Taylor Wilson
 # UID :        U0323893
 # 
 # DATE :       August 29, 2015
 # 
 # PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 #              University of Utah
 # 
 # *******************************************************************************************
 
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

  def setUp(self):
    pass

  def tearDown(self):
    pass

  def testNoArgs(self):
    tri = Triangle('0 0 0 0 0 0'.split())
    tri.erasePoints()
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testExcessArgs(self):
    tri = Triangle('0 0 0 0 0 0'.split())
    tri.addPoint('1')
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testMissingArgs(self):
    tri = Triangle('0 0 0 0 0 0'.split())
    tri.removePoint('0')
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testInvalidChars(self):
    tri = Triangle('0 0 0 0* 0 0'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testNegativeSign(self):
    tri = Triangle('-1 -1 0 0 -1 1'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.ISO)
    self.assertEqual(tri.typeB, Types.RIG)

  def testLeadingZeros(self):
    tri = Triangle('00000000000000000000001 0 0 000 0000000 01'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.ISO)
    self.assertEqual(tri.typeB, Types.RIG)

  def testOverflowArgs(self):
    tri = Triangle('1 2 3 4 0 1073741824'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testUnderflowArgs(self):
    tri = Triangle('1 2 3 4 0 -1073741824'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.ERR)

  def testDuplicatePoints1(self):
    tri = Triangle('-1073741823 1073741823 -1073741823 1073741823 1073741823 1073741823'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testDuplicatePoints2(self):
    tri = Triangle('-1073741823 1073741823 -1073741823 1073741823 -1073741823 1073741823'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testVerticalLine(self):
    tri = Triangle('0 -123456789 0 0 0 123456789'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testHorizontalLine(self):
    tri = Triangle('-987654321 0 0 0 987654321 0'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testDiagonalLine1(self):
    tri = Triangle('0 100000033 100000033 0 200000066 -100000033'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testDiagonalLine2(self):
    tri = Triangle('0 0 -123456789 -123456789 123456789 123456789'.split())
    tri.build()
    self.assertEqual(tri.output(), Types.NAT)

  def testIsoscelesAcute(self):
    tri = Triangle('-1073741822 0 0 1073741823 1073741822 0'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.ISO)
    self.assertEqual(tri.typeB, Types.ACU)

  def testIsoscelesRight(self):
    tri = Triangle('0 1073741823 -1073741823 0 1073741823 0'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.ISO)
    self.assertEqual(tri.typeB, Types.RIG)

  def testIsoscelesObtuse(self):
    tri = Triangle('0 1073741822 -1073741823 0 1073741823 0'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.ISO)
    self.assertEqual(tri.typeB, Types.OBT)

  def testScaleneAcute(self):
    tri = Triangle('-1073741823 -1073741823 -1073741822 1073741822 0 -1073741822'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.SCA)
    self.assertEqual(tri.typeB, Types.ACU)

  def testScaleneRight(self):
    tri = Triangle('-1073741822 -1073741822 -1073741822 1073741822 0 -1073741822'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.SCA)
    self.assertEqual(tri.typeB, Types.RIG)

  def testScaleneObtuse(self):
    tri = Triangle('-1073741822 -1073741821 -1073741822 1073741822 0 -1073741822'.split())
    tri.build()
    self.assertEqual(tri.typeA, Types.SCA)
    self.assertEqual(tri.typeB, Types.OBT)

  # arg! what integer points form an equilateral tri ???
  # def equilateral(self):
  #   tri = Triangle('? ? ? ? ? ?'.split())
  #   tri.build()
  #   self.assertEqual(tri.typeA, Types.EQU)
  #   self.assertEqual(tri.typeB, Types.ACU)

# ==============================================================================================================
# Triangle Class
# ==============================================================================================================

class Triangle:  
  def __init__(self, pts):
    self.args  = ['./triangle', pts[0], pts[1], pts[2], pts[3], pts[4], pts[5]]
    self.typeA = None
    self.typeB = None

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
      self.typeA = self.out.split()[0]
      self.typeB = self.out.split()[1]

  def output(self):
    return self.out

# ==============================================================================================================
# Executes from here
# ==============================================================================================================

if __name__ == '__main__':
  unittest.main()
