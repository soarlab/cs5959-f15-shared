 # 
 # AUTHOR :     Taylor Wilson
 # UID :        U0323893
 # 
 # DATE :       September 26, 2015
 # 
 # PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 #              University of Utah
 #

import random
import sys
import re 
import os
from subprocess import Popen, PIPE
import time

# returns the output of a process
def exec_process(args):
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  # print out
  return out

# writes a base file of random bytes
class Baser:
  def __init__(self, seed, size):
    self.args = ['src/baser.o', str(seed), str(size)]

  def run(self):
    # returns the random seed for the baser
    return exec_process(self.args).split(' ')[-2] 

# generates a fuzzed file from the base file
class Fuzzer:
  def __init__(self, seed, size, index):
    self.args = ['src/fuzzer.o', str(seed), str(size), str(index)]

  def run(self):
    return exec_process(self.args).split(' ')[-2]

# executes the software under test
class Sha1Sum:
  def __init__(self):
    self.args = ['../coreutils/src/sha1sum', './fuzz.txt']

  def run(self):
    return exec_process(self.args)

# executes differential versions (system's sha1sum and java)
class Differ:
  def __init__(self, size):
    self.args1 = ['sha1sum', './fuzz.txt']
    self.args2 = ['java', '-cp', 'src', 'Jsha1sum', './fuzz.txt', str(size)]

  def run(self):
    out = []
    out.append(exec_process(self.args1))
    out.append(exec_process(self.args2))
    return out

# logs results to disk
class Logger:
  def __init__(self, path):
    self.fail_log_file = open(path, 'w+')

  def delim(self):
    self.fail_log_file.write('====================================================================================================\n') 

  def write(self, str):
    self.fail_log_file.write(str)
    
  def close(self):
    self.fail_log_file.close()

# determines pass/fail results
class Oracle:
  def __init__(self, max_size):
    self.results   = set()
    self.res_count = 0
    self.max_size  = int(max_size)
    self.seed      = int(round(time.time() * 1000))
    random.seed(self.seed)

    print 'Oracle initialzed to test inputs of ' + str(max_size) + ' Bytes. \nOracle initialized with seed ' + str(self.seed) + '\n'

  def run(self):
    self.fail_log   = Logger('fail_log.txt')
    self.pass_log   = Logger('pass_log.txt')
    self.baser      = Baser(self.seed, self.max_size)
    self.sha1sum    = Sha1Sum()
    self.fuzz_indez = 0

    self.base_seed  = self.baser.run()
    for i in range(0, self.max_size):
      seed = random.randint(0, 2147483648)
      self.fuzz_seed  = Fuzzer(seed, self.max_size, random.randint(0, self.max_size)).run()
      self.fuzz_index = i
      self.check_digest(self.sha1sum.run())
      self.seed += 1
      
    self.fail_log.close()
    self.pass_log.close()

  def check_digest(self, digest):
    if len(digest) == 53:
      # run differential test
      diff = Differ(self.max_size).run()
      if digest == diff[0] and diff[0] == diff[1]:
        # check for collisions
        if digest in self.results:
          print 'FAIL \t' + digest.rstrip('\n')
          # collision found
          self.fail_log.delim()
          self.fail_log.write('FAILURE\n')
          self.fail_log.write('  Algorithm produced a collision.\n')
          self.fail_log.write('    oracle rand seed = ' + str(self.seed)       + '\n')
          self.fail_log.write('    base random seed = ' + str(self.base_seed)  + '\n')
          self.fail_log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
          self.fail_log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n')
          self.fail_log.write('    digest           = ' + digest)
          self.fail_log.delim()
        else:
          self.results.add(digest)
          print 'PASS \t' + digest.rstrip('\n')
          self.pass_log.write('  digest = ' + digest)

      else:
        print 'FAIL'
        self.fail_log.delim()
        self.fail_log.write('FAILURE\n')
        self.fail_log.write('  Comparison between coreutils v.24 digest, coreutils v.22 digest, and java.crypto digest failed.\n')
        self.fail_log.write('    oracle rand seed = ' + str(self.seed)       + '\n')
        self.fail_log.write('    base random seed = ' + str(self.base_seed)  + '\n')
        self.fail_log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
        self.fail_log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n')
        self.fail_log.write('    digest v.24      = ' + digest)
        self.fail_log.write('    digest v.22      = ' + diff[0])
        self.fail_log.write('    digest java      = ' + diff[1])
        self.fail_log.delim()
    else:
      print 'FAIL'
      self.fail_log.delim()
      self.fail_log.write('FAILURE\n')
      self.fail_log.write('  Computed digest was an unexpected number of bytes.\n')
      self.fail_log.write('    oracle rand seed = ' + str(self.seed)       + '\n')
      self.fail_log.write('    base random seed = ' + str(self.base_seed)  + '\n')
      self.fail_log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
      self.fail_log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n')
      self.fail_log.write('    digest           = ' + digest)
      self.fail_log.delim()

if __name__ == '__main__':
  Oracle(sys.argv[1]).run()
