 # 
 # AUTHOR :     Taylor Wilson
 # UID :        U0323893
 # 
 # DATE :       September 26, 2015
 # 
 # PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 #              University of Utah
 #

import re 
import os
from subprocess import Popen, PIPE
import time

def exec_process(args):
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out

class Baser:
  def __init__(self, size):
    self.args = ['src/baser.o', str(size)]

  def run(self):
    # returns the random seed for the baser
    return exec_process(self.args).split(' ')[-2] 

class Fuzzer:
  def __init__(self, size):
    self.args = ['src/fuzzer.o', str(size), str(0)]

  def run(self):
    # sleeping 1 second ensure the randomized seed will change between runs
    # returns the random seed for the fuzzer
    time.sleep(1)
    return exec_process(self.args).split(' ')[-2]

  def update_index(self, index):
    self.args[2] = str(index)

class Sha1Sum:
  def __init__(self):
    self.args = ['../coreutils/src/sha1sum', './fuzz.txt']

  def run(self):
    return exec_process(self.args)

class Differ:
  def __init__(self, size):
    self.args1 = ['sha1sum', './fuzz.txt']
    self.args2 = ['java', '-cp', 'src', 'Jsha1sum', str(size)]

  def run(self):
    out = []
    out.append(exec_process(self.args1))
    out.append(exec_process(self.args2))
    return out

class Logger:
  def __init__(self):
    self.log_file = open('log.txt', 'w+')

  def delim(self):
    self.log_file.write('====================================================================================================\n') 

  def write(self, str):
    self.log_file.write(str)
    
  def close(self):
    self.log_file.close()

class Oracle:
  def __init__(self):
    self.results   = set()
    self.res_count = 0
    self.max_size  = 1024

  def run(self):
    self.log     = Logger()
    self.baser   = Baser(self.max_size)
    self.fuzzer  = Fuzzer(self.max_size)
    self.sha1sum = Sha1Sum()

    self.base_seed  = self.baser.run()
    for i in range(0, self.max_size):
      self.fuzz_seed  = self.fuzzer.run()
      self.fuzz_index = i
      self.fuzzer.update_index(i)
      self.check_digest(self.sha1sum.run())

    self.log.close()

  def check_digest(self, digest):
    if len(digest) == 53:
      # run differential test
      diff = Differ(self.max_size).run()
      if digest == diff[0] and diff[0] == diff[1]:
        # check for collisions
        self.results.add(digest)
        self.res_count += 1
        if len(self.results) != self.res_count:
          print 'FAIL'
          # collision found
          self.log.delim()
          self.log.write('FAILURE\n')
          self.log.write('  Algorithm produced a collision.\n')
          self.log.write('    base random seed = ' + str(self.base_seed)  + '\n')
          self.log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
          self.log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n\n')
          self.log.write('    digest           = ' + digest)
          self.log.delim()
        else:
          print 'PASS \t' + digest.rstrip('\n')
      else:
        print 'FAIL'
        self.log.delim()
        self.log.write('FAILURE\n')
        self.log.write('  Comparison between coreutils v.24 digest, coreutils v.22 digest, and java.crypto digest failed.\n')
        self.log.write('    base random seed = ' + str(self.base_seed)  + '\n')
        self.log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
        self.log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n')
        self.log.write('    digest v.24      = ' + digest)
        self.log.write('    digest v.22      = ' + diff[0])
        self.log.write('    digest java      = ' + diff[1])
        self.log.delim()
    else:
      print 'FAIL'
      self.log.delim()
      self.log.write('FAILURE\n')
      self.log.write('  Computed digest was an unexpected number of bytes.\n')
      self.log.write('    base random seed = ' + str(self.base_seed)  + '\n')
      self.log.write('    fuzz random seed = ' + str(self.fuzz_seed)  + '\n')
      self.log.write('    fuzzed index     = ' + str(self.fuzz_index) + '\n')
      self.log.write('    digest           = ' + digest)
      self.log.delim()

if __name__ == '__main__':
  Oracle().run()
