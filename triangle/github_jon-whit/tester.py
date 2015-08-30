import subprocess

failed_cnt = 0

def run_test(test, expected):
    output = subprocess.check_output(test, shell=True)

    if output != expected:
        global failed_cnt
        failed_cnt += 1
        print ("FAILED TEST: '%s'\n\tEXPECTED: %s\r\tRETURNED: %s\n") % (test, expected, output)

if __name__ == "__main__":
    subprocess.call(['make'], shell=True)

    # test 3 points on a line
    run_test("./a.out 1 2 3 4 5 6", "not a triangle\n")
    run_test("./a.out 1    2    3    4    5    6", "not a triangle\n")
    run_test("./a.out 0 0 0 0 0 0", "not a triangle\n")

    # test isosceles triangles
    run_test("./a.out 1073741823 0 -1073741823 0 0 1", "isosceles obtuse\n")
    run_test("./a.out -1073741823 0 1073741823 0 0 1", "isosceles obtuse\n")
    run_test("./a.out 0 0 0 1073741823 1073741823 0", "isosceles right\n")

    # test scalene triangles
    run_test("./a.out 0 0 0 1073741823 1073741822 0", "scalene right\n")
    run_test("./a.out 0 0 -1 1073741823 1073741823 0", "scalene obtuse\n")
    run_test("./a.out 0 0 1 1073741823 1073741823 0", "scalene acute\n")

    # test illegal input
    run_test("./a.out", "error\n")
    run_test("./a.out 1 2 3 4 56", "error\n")
    run_test("./a.out 1 2 3 4 5 6 7", "error\n")
    run_test("./a.out 1  2  3  4  56", "error\n")
    run_test("./a.out 1  2  3  4  5  6  7", "error\n")
    run_test("./a.out 1073741824 0 0 0 1 2", "error\n")
    run_test("./a.out -1073741824 0 0 0 1 2", "error\n")
    run_test("./a.out a b c d e f", "error\n")
    run_test("./a.out a3 1 2 3 4 5", "error\n")
    run_test("./a.out 1 as3df 2 3 4 5", "error\n")
    run_test("./a.out 1 2 3 4asdf 5 6", "error\n")
    run_test("./a.out 1 2 3 4 5 jon", "error\n")

    if failed_cnt == 0:
        print ("Tests Passed!")
