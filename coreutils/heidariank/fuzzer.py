import re
import os
from subprocess import Popen, PIPE
import random, string
import datetime
import time
import sys
import shutil
        #1. generate random number of random length
        #2. invoke numfmt using various flags plus random num
        #3. compare output with system's numfmt output
        #4. if outputs are not the same write to a directory containing log info
        # Log info should include 1. random num seed, 2. random number file 3. command
        #that triggered non-matching results

class Fuzzer:
    went_wrong = False
    seed = 1
    command = []
    sys_command = []
    out = ''
    error = ''
    sys_out = ''
    sys_error = ''

    def __init__(self):
        seed = 1

    def run(self, cmd):
        went_wrong = False
        self.seed = time.time()
        random.seed(self.seed)
        #randnum = random.randrange(0, 5242880) #I'm too afraid to go over 5M
        randlength = random.randrange(0, 5242)

        f = open('fuzz', 'w')

        for i in range(0, randlength):
            randnum = random.randrange(48, 58)
            randchar = str(unichr(randnum))
            f.write(randchar)
        #range that contains acceptable suffixes for numfmt
        suffixes = {0 : "E", 1 : "G", 2 : "K", 3 : "M",
                    4 : "P", 5 : "T", 6 : "Y", 7 : "Z"}
        f.write(suffixes[random.randrange(0,8)])
        if random.randrange(0,2):
            f.write(str(unichr(105)))
        f.close()

        f = open('fuzz', 'r')

        filedata = f.read()

        #self.command = ['./src/numfmt', filedata]
        cmd.append(filedata)
        #print "cmd: {}".format(cmd)
        self.command = cmd
        try:
            proc = Popen(self.command, stdout=PIPE, stderr=PIPE)
            (self.out, self.error) = proc.communicate()
            #print "self.command{}".format(self.command)

            #        sys_command = ['numfmt', filedata]
            self.sys_command = cmd
            self.sys_command[0] = self.sys_command[0][6:]

            sys_proc = Popen(self.sys_command, stdout=PIPE, stderr=PIPE)
            (self.sys_out, self.sys_error) = sys_proc.communicate()
        except OSError as inst:
            print type(inst)     # the exception instance
            print inst.args      # arguments stored in .args
            print inst           # __str__ allows args to be printed directly
        #print "sys_command{}".format(sys_command)

        #error = error[6:]
        #out = out[6:]

        if self.out != self.sys_out or self.error[6:] != self.sys_error:
            print "sys_out: {}".format(self.sys_out)
            print "out:     {}".format(self.out)
            print "sys_error: {}".format(self.sys_error)
            print "error:     {} ".format(self.error)
            self.went_wrong = True

        f.close()

'''Oracle'''
end_time = time.time() + 60*60 # time() is calculated in seconds
fileindex = 1

while time.time() < end_time:
    fuzzer = Fuzzer()
    #print os.path.join(os.sep, 'fuzz-results', 'results1')


    
    cmd = ["./src/numfmt"]

    flags = {0 : "",
             1 : "--to=si",
             2 : "--to=iec",
             3 : "--to=iec-i",
             4 : "--from=si",
             5 : "--from=iec",
             6 : "--from=auto"}
    rand_flag = random.randrange(0,7)
    cmd.append(flags[rand_flag])


    fuzzer.run(cmd)
    if fuzzer.went_wrong:
        results = open(os.path.join('fuzz-results', 'results{}'.format(fileindex)), 'w')
        f = open('fuzz', 'r')
        results.write('Date and time: {}\n'.format(datetime.datetime.now()))
        results.write('Random seed: {}\n'.format(fuzzer.seed))
        results.write('Command used: {}\n'.format(fuzzer.command))
        results.write('System Command used: {}\n'.format(fuzzer.sys_command))
        results.write('Output: {}\n'.format(fuzzer.out))
        results.write('Error: {}\n'.format(fuzzer.error))
        results.write('System Output: {}\n'.format(fuzzer.sys_out))
        results.write('System Error: {}\n'.format(fuzzer.sys_error))
        results.write('Data: ')
        results.write(f.read())
        results.write('\n')
    
        fileindex += 1

        results.close()
        f.close()

    #time.sleep(0.05)


