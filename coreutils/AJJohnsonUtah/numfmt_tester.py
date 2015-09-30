import subprocess
import sys

tests_passed = 0
tests_run = 0

def do_test(command, expected, description):
    global tests_run
    tests_run += 1
    test_output = subprocess.check_output(command, shell=True)
    if(test_output == expected):
        global tests_passed
        tests_passed += 1
        if(len(sys.argv) == 2 and (sys.argv[1] == "-v" or sys.argv[1] == "V")):
            print("PASSED: " + description)
        return True
    else:
        print("FAILED: %s\n\tIncorrect output: %s"
              % (description, test_output))
        return False

# Perform many tests to get widespread code coverage.

do_test("numfmt --to=si 123000000", "123M\n", "Simple conversion to si.")
do_test("numfmt --from=si 123G", "123000000000\n", "Simple conversion from si.")
do_test("numfmt --to=iec 100000000", "96M\n", "Conversion to iec.")
do_test("numfmt --from=iec 100K", "102400\n", "Conversion from iec.")
do_test("numfmt --to=iec-i 500000", "489Ki\n", "Conversion to iec-i.")
do_test("numfmt --from=iec-i 489Ki", "500736\n", "Conversion from iec-i.")
do_test("numfmt --from=si --to=iec 1T", "932G\n", "Conversion from si to iec.")
do_test("numfmt --to=si --round=nearest 123400", "123K\n", "Test rounding type nearest.")
do_test("numfmt --to=si --round=down 123400", "123K\n", "Test rounding type down.")
do_test("numfmt --to=si --round=up 123400", "124K\n", "Test rounding type up.")
do_test("numfmt --to=si --round=towards-zero 123400", "123K\n", "Test rounding type towards-zero.")
do_test("numfmt --to=si --padding=4 100000", "100K\n", "Test padding of 4.")
do_test("numfmt --to=si --padding=7 100000", "   100K\n", "Test padding of 7.")
do_test("numfmt --grouping 100000121", "100,000,121\n", "Test grouping.")
do_test("numfmt --from-unit=100 100000", "10000000\n", "Test from unit of 100.")
do_test("numfmt --to=si 10000 10000000 10000000000", "10K\n10M\n10G\n", "Multiple inputs.")

if(tests_run == tests_passed):
    print("Success! All " + str(tests_run) + " tests passed.")
else:
    print("Failure! " + str(tests_run - tests_passed) + "/" + str(tests_run) + " tests failed.")
