import argparse
import subprocess
import loremipsum
import random
import time
import logging

class FmtCompTester:
    """
    The FmtCompTester class represents a comparison tester for GNU's 'fmt' utility. This
    class contains the fields and methods needed to test two different versions of the
    utility.
    """

    def __init__(self, path1, path2):
        """
        FmtCompTester constructor.

        :path1: The path to the first version of GNU's 'fmt' utility.
        :path2: The path to the second version of GNU's 'fmt' utility.
        """
        self.fmt_args = ['-c', '-t', '-s', '-u', '-w', '-g', '-p']
        self.fmt_path1 = path1
        self.fmt_path2 = path2
        self.generator = loremipsum.Generator()


    def run_fmt(self, text, args):
        """
        Runs the two different versions of GNU's 'fmt' utility on the input
        file specified, and returns True if the two outputs matched or False
        otherwise.

        :text: A string containing randomized paragraph text.
        :args: An array containing the arguments that fmt should be invoked with.
        """

        cmd1 = [self.fmt_path1 + "fmt"]
        cmd2 = [self.fmt_path2 + "fmt"]
        args = [str(arg) for arg in args]
        cmd1 += args
        cmd2 += args

        # echo the randomized paragraph text into the 'fmt' utility
        echo_proc = subprocess.Popen(["echo", text], stdout=subprocess.PIPE)
        out1 = subprocess.check_output(cmd1, shell=True, stdin=echo_proc.stdout)
        echo_proc = subprocess.Popen(["echo", text], stdout=subprocess.PIPE)
        out2 = subprocess.check_output(cmd2, shell=True, stdin=echo_proc.stdout)

        # check that the outputs matched
        if out1 != out2:
            str_cmd1 = "echo '{0}' | {1}".format(text, ' '.join(cmd1))
            str_cmd2 = "echo '{0}' | {1}".format(text, ' '.join(cmd2))
            log_message = "\n{0}\n\n{1}\nFAILED!\n\nOutput 1:\n{2}\nOutput 2:\n{3}".format(str_cmd1, str_cmd2, out1, out2)
            logging.info(log_message)
            return False

        return True


    def test_randomly(self, n):
        """
        Tests the two 'fmt' utilities against each other for randomized paragraphs
        of text a total of n times. If any test results in the two different
        versions result in different output, then these cases will be logged to the
        console. This function will return the number of failed tests that occurred.

        :n: An integer number indicating the number of tests to run.
        """
        fail_cnt = 0

        for i in range(0, n):
            # generate randomized paragraph text
            par_text = self.generator.generate_paragraph()[2]

            # generate a random set of command line arguments for the 'fmt' utility
            random.seed(time.time())
            args = []
            for j in range(0, random.randint(1, len(self.fmt_args))):
                k = random.randint(0, len(self.fmt_args) - 1)
                c = self.fmt_args[k]

                # if there are no matching occurances of this flag already in the argument
                # list, then add the flag to the list
                matches = [arg for arg in args if c in arg]
                if not matches:
                    if c == '-w':
                        arg = "-w {0}".format(random.randint(1, 100))
                        args.append(arg)
                    elif c == '-g':
                        arg = "-g {0}".format(random.randint(1, 100))
                        args.append(arg)
                    elif c == '-p':
                        words = self.generator.words
                        rand_word = words[random.randint(0, len(words) - 1)]
                        arg = "-p {0}".format(rand_word)
                        args.append(arg)
                    else:
                        args.append(c)

            # run the 'fmt' utility on the randomized paragraph text
            passed = self.run_fmt(par_text, args)
            if not passed:
                fail_cnt += 1

        return fail_cnt


if __name__ == '__main__':

    logging.basicConfig(level=logging.INFO)

    parser = argparse.ArgumentParser(description="A comparison tester for GNU's 'fmt' utility.")
    parser.add_argument("--path1", required=True, help="The directory where the first version of GNU's 'fmt' utility lives.")
    parser.add_argument("--path2", required=True, help="The directory where the second version of GNU's 'fmt' utility lives.")
    parser.add_argument("-n", type=int, help="An optional number of tests to run (100 by default).")

    # parse the command line arguments
    args = parser.parse_args()

    tester = FmtCompTester(args.path1, args.path2)

    # perform n = 1000 random comparisons
    n = args.n if args.n else 100
    fails = tester.test_randomly(n)
    if not fails:
        print ("All tests passed!")
