# AUTHOR: Jared Potter (u0729256)
#
# DATE: September 29, 2015
#
# Python unittest tests for CoreUtils expr utility

import os
from subprocess import Popen, PIPE
import unittest

class ExprTest(unittest.TestCase):

  def testNumber1(self):
    myTest = Expression('1 = 1'.split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber2(self):
    myTest = Expression('312313 = 312313'.split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber3(self):
    myTest = Expression('-928424 = -928424'.split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber4(self):
    myTest = Expression('-9223372036854775808 = -9223372036854775808'.split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber5(self):
    myTest = Expression('9223372036854775807 = 9223372036854775807'.split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber6(self):
    myTest = Expression('0803583085345 = 349875937535'.split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber7(self):
    myTest = Expression('0 = 1'.split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber8(self):
    myTest = Expression('112313 = 15345353635343434'.split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber9(self):
    myTest = Expression('1 = 9223372036854775807'.split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber10(self):
    myTest = Expression('-9223372036854775808 = 9223372036854775807'.split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber11(self):
    myTest = Expression("0 | 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber12(self):
    myTest = Expression("0 | 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber13(self):
    myTest = Expression("1 | 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber14(self):
    myTest = Expression("1 | 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber15(self):
    myTest = Expression("112312314 | 0".split())
    self.assertEqual(myTest.executeTest(),'112312314\n')

  def testNumber16(self):
    myTest = Expression("0 & 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber17(self):
    myTest = Expression("0 & 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber18(self):
    myTest = Expression("1 & 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber19(self):
    myTest = Expression("1 & 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')    

  def testNumber20(self):
	myTest = Expression("1523425 & 164535".split())
	self.assertEqual(myTest.executeTest(),'1523425\n')

  def testNumber21(self):
    myTest = Expression("0 < 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber22(self):
    myTest = Expression("0 < 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber23(self):
    myTest = Expression("1 < 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber24(self):
    myTest = Expression("1 < 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber25(self):
	myTest = Expression("152342 < 164535".split())
	self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber26(self):
    myTest = Expression("0 <= 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber27(self):
    myTest = Expression("0 <= 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber28(self):
    myTest = Expression("1 <= 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber29(self):
    myTest = Expression("1 <= 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')    

  def testNumber30(self):
	myTest = Expression("152342 <= 164535".split())
	self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber31(self):
    myTest = Expression("0 != 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber32(self):
    myTest = Expression("0 != 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber33(self):
    myTest = Expression("1 != 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber34(self):
    myTest = Expression("1 != 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber35(self):
	myTest = Expression("152342 <= 164535".split())
	self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber36(self):
    myTest = Expression("0 > 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber37(self):
    myTest = Expression("0 > 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber38(self):
    myTest = Expression("1 > 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber39(self):
    myTest = Expression("1 > 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber40(self):
	myTest = Expression("152342 > 164535".split())
	self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber41(self):
    myTest = Expression("0 >= 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber42(self):
    myTest = Expression("0 >= 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber43(self):
    myTest = Expression("1 >= 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber44(self):
    myTest = Expression("1 >= 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')    

  def testNumber45(self):
	myTest = Expression("152342 >= 164535".split())
	self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber46(self):
    myTest = Expression("0 + 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber47(self):
    myTest = Expression("0 + 1".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber48(self):
    myTest = Expression("1 + 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber49(self):
    myTest = Expression("1 + 1".split())
    self.assertEqual(myTest.executeTest(),'2\n')    

  def testNumber50(self):
	myTest = Expression("152342 + 164535".split())
	self.assertEqual(myTest.executeTest(),'316877\n')

  def testNumber51(self):
    myTest = Expression("0 - 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber52(self):
    myTest = Expression("0 - 1".split())
    self.assertEqual(myTest.executeTest(),'-1\n')

  def testNumber53(self):
    myTest = Expression("1 - 0".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber54(self):
    myTest = Expression("1 - 1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber55(self):
	myTest = Expression("152342 - 164535".split())
	self.assertEqual(myTest.executeTest(),'-12193\n')

  def testNumber56(self):
    myTest = Expression("0 * 0".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber57(self):
    myTest = Expression("123 * 2".split())
    self.assertEqual(myTest.executeTest(),'246\n')

  def testNumber58(self):
    myTest = Expression("2 * 6".split())
    self.assertEqual(myTest.executeTest(),'12\n')

  def testNumber59(self):
    myTest = Expression("1 * -1".split())
    self.assertEqual(myTest.executeTest(),'-1\n')    

  def testNumber60(self):
	myTest = Expression("152342 * 164535".split())
	self.assertEqual(myTest.executeTest(),'25065590970\n')

  def testNumber61(self):
    myTest = Expression("0 / 0".split())
    self.assertEqual(myTest.executeTest(),'')

  def testNumber62(self):
    myTest = Expression("123 / 2".split())
    self.assertEqual(myTest.executeTest(),'61\n')

  def testNumber63(self):
    myTest = Expression("2 / 6".split())
    self.assertEqual(myTest.executeTest(),'0\n')

  def testNumber64(self):
    myTest = Expression("1 / -1".split())
    self.assertEqual(myTest.executeTest(),'-1\n')    

  def testNumber65(self):
	myTest = Expression("164535 / 152342".split())
	self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber66(self):
    myTest = Expression("0 % 0".split())
    self.assertEqual(myTest.executeTest(),'')

  def testNumber67(self):
    myTest = Expression("123 % 2".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber68(self):
    myTest = Expression("2 % 6".split())
    self.assertEqual(myTest.executeTest(),'2\n')

  def testNumber69(self):
    myTest = Expression("1 % -1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber70(self):
	myTest = Expression("164535 / 152342".split())
	self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber71(self):
    myTest = Expression("0 % 0".split())
    self.assertEqual(myTest.executeTest(),'')

  def testNumber72(self):
    myTest = Expression("123 % 2".split())
    self.assertEqual(myTest.executeTest(),'1\n')

  def testNumber73(self):
    myTest = Expression("2 % 6".split())
    self.assertEqual(myTest.executeTest(),'2\n')

  def testNumber74(self):
    myTest = Expression("1 % -1".split())
    self.assertEqual(myTest.executeTest(),'0\n')    

  def testNumber75(self):
	myTest = Expression("164535 % 152342".split())
	self.assertEqual(myTest.executeTest(),'12193\n')

  def testNumber76(self):
    myTest = Expression("9223372036854775807 + 9223372036854775807".split())
    self.assertEqual(myTest.executeTest(),'')

  def testNumber77(self):
    myTest = Expression("-9223372036854775807 - 9223372036854775807".split())
    self.assertEqual(myTest.executeTest(),'')

  def testNumber78(self):
    myTest = Expression("9223372036854775807 * 9223372036854775807".split())
    self.assertEqual(myTest.executeTest(),'')    

  def testNumber79(self):
	myTest = Expression("9223372036854775807 / 0.5".split())
	self.assertEqual(myTest.executeTest(),'')

  def testNumber80(self):
    myTest = Expression("9223372036854775809 + 2".split())
    self.assertEqual(myTest.executeTest(),'')

  def testKeyword1(self):
    myTest = Expression('--help'.split())
    self.assertEqual(myTest.executeTest(),"Usage: ../coreutils/src/./expr EXPRESSION\n  or:  ../coreutils/src/./expr OPTION\n\n      --help     display this help and exit\n      --version  output version information and exit\n\nPrint the value of EXPRESSION to standard output.  A blank line below\nseparates increasing precedence groups.  EXPRESSION may be:\n\n  ARG1 | ARG2       ARG1 if it is neither null nor 0, otherwise ARG2\n\n  ARG1 & ARG2       ARG1 if neither argument is null or 0, otherwise 0\n\n  ARG1 < ARG2       ARG1 is less than ARG2\n  ARG1 <= ARG2      ARG1 is less than or equal to ARG2\n  ARG1 = ARG2       ARG1 is equal to ARG2\n  ARG1 != ARG2      ARG1 is unequal to ARG2\n  ARG1 >= ARG2      ARG1 is greater than or equal to ARG2\n  ARG1 > ARG2       ARG1 is greater than ARG2\n\n  ARG1 + ARG2       arithmetic sum of ARG1 and ARG2\n  ARG1 - ARG2       arithmetic difference of ARG1 and ARG2\n\n  ARG1 * ARG2       arithmetic product of ARG1 and ARG2\n  ARG1 / ARG2       arithmetic quotient of ARG1 divided by ARG2\n  ARG1 % ARG2       arithmetic remainder of ARG1 divided by ARG2\n\n  STRING : REGEXP   anchored pattern match of REGEXP in STRING\n\n  match STRING REGEXP        same as STRING : REGEXP\n  substr STRING POS LENGTH   substring of STRING, POS counted from 1\n  index STRING CHARS         index in STRING where any CHARS is found, or 0\n  length STRING              length of STRING\n  + TOKEN                    interpret TOKEN as a string, even if it is a\n                               keyword like 'match' or an operator like '/'\n\n  ( EXPRESSION )             value of EXPRESSION\n\nBeware that many operators need to be escaped or quoted for shells.\nComparisons are arithmetic if both ARGs are numbers, else lexicographical.\nPattern matches return the string matched between \\( and \\) or null; if\n\\( and \\) are not used, they return the number of characters matched or 0.\n\nExit status is 0 if EXPRESSION is neither null nor 0, 1 if EXPRESSION is null\nor 0, 2 if EXPRESSION is syntactically invalid, and 3 if an error occurred.\n\nGNU coreutils online help: <http://www.gnu.org/software/coreutils/>\nFull documentation at: <http://www.gnu.org/software/coreutils/expr>\nor available locally via: info '(coreutils) expr invocation'\n")

  def testKeyword2(self):
    myTest = Expression('--version'.split())
    self.assertEqual(myTest.executeTest(),"expr (GNU coreutils) 8.24.32-c7af0\nCopyright (C) 2015 Free Software Foundation, Inc.\nLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Mike Parker, James Youngman, and Paul Eggert.\n")

  def testKeyword3(self):
	myTest = Expression("match Gary Ga".split())
	self.assertEqual(myTest.executeTest(),'2\n')

  def testKeyword4(self):
	myTest = Expression("substr Elizabeth 4 8".split())
	self.assertEqual(myTest.executeTest(),'zabeth\n')

  def testKeyword5(self):
	myTest = Expression("length telephoneequipment".split())
	self.assertEqual(myTest.executeTest(),'18\n')

  def testKeyword6(self):
	myTest = Expression("--".split())
	self.assertEqual(myTest.executeTest(),'')

  def testKeyword7(self):
	myTest = Expression("a z".split())
	self.assertEqual(myTest.executeTest(),'')

  def testKeyword8(self):
	myTest = Expression("-- a".split())
	self.assertEqual(myTest.executeTest(),'a\n')

  def testKeyword9(self):
	myTest = Expression("7575 : 7575".split())
	self.assertEqual(myTest.executeTest(),'4\n')

  def testKeyword10(self):
	myTest = Expression("index index a".split())
	self.assertEqual(myTest.executeTest(),'')

  def testKeyword11(self):
	myTest = Expression("index + index a".split())
	self.assertEqual(myTest.executeTest(),'0\n')

  def testKeyword12(self):
	myTest = Expression("index 123456789 9".split())
	self.assertEqual(myTest.executeTest(),'9\n')

  def testRegex1(self):
	myTest = Expression("hello : hell".split())
	self.assertEqual(myTest.executeTest(),'4\n')

  def testRegex2(self):
	myTest = Expression("+ index : ind".split())
	self.assertEqual(myTest.executeTest(),'3\n')

  def testRegex3(self):
	myTest = Expression("aaa : a\+".split())
	self.assertEqual(myTest.executeTest(),'3\n')

  def testRegex4(self):
	myTest = Expression("abc : a\(.\)c".split())
	self.assertEqual(myTest.executeTest(),'b\n')

class Expression:  
  def __init__(self, arguments):
    self.args  = ['../coreutils/src/./expr'] # CoreUtils' expr
    #self.args  = ['expr'] # BSD's expr
    for item in arguments:
        self.args.append(item)

  def exp(self):
    return self.args

  def evauluateExpression(self):
	ps         = Popen(self.exp(), stdout=PIPE, stderr=PIPE)
	(out, err) = ps.communicate()
	exit_code  = ps.wait()
	return out

  def executeTest(self):
    self.out = self.evauluateExpression()
    return self.out

if __name__ == '__main__':
  unittest.main()