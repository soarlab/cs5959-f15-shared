import random
import sys
import re 
import os
from subprocess import Popen, PIPE
import time

# global
NOW = None

def base_path():
  return 'txt/base.txt'

def diff_path():
  return ['log/v22_diff.txt', 'log/java_diff.txt']

def fuzz_path():
  return 'txt/fuzz'

def res_path():
  return 'log/res.txt'

def sums_path():
  return 'log/sums.txt'

def sha_path():
  return '../coreutils/src/sha1sum'

def exec_process(args):
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  print out
  return out

class Logger:
  def __init__(self, path):
    self.log_file = open(path, 'w+')

  def delim(self):
    self.log_file.write('====================================================================================================\n') 

  def write(self, str):
    self.log_file.write(str)
    
  def close(self):
    self.log_file.close()

class Sha1Sum:
  def __init__(self, path):
    self.args = [sha_path(), path]

  def run(self):
    return exec_process(self.args)

class Baser:
  def __init__(self, size):
    print 'baser init with size = ' + str(size)
    self.size = size
    self.path = base_path()

  def write_base(self):
    print 'writing base file'
    base_file = open(self.path, 'wb')
    for i in range(0, self.size):
      base_file.write(bytes(unichr(random.randint(32, 127))))
    base_file.close()

  def read_base(self):
    base_file = open(self.path, 'r')
    data = base_file.read()
    base_file.close()
    return data

class Fuzzer:
  def __init__(self, size, count):
    print 'fuzzer init with size = ' + str(size)
    self.size  = size
    self.count = count
    # self.path = fuzz_path + str(itr) + '.txt'
    self.baser = Baser(self.size)

  def fuzz(self):
    self.baser.write_base()
    
    for i in range(0, self.count):
      if i % 100 == 0:
        print 'fuzzing file # ' + str(i)
      fuzz_file = open(fuzz_path() + str(i) + '.txt', 'wb')
      data      = bytearray(self.baser.read_base())
      data[random.randint(0, len(data))] = bytes(unichr(random.randint(32, 127)))
      fuzz_file.write(data)
      fuzz_file.close()

  def run(self):
    log = Logger(sums_path())

    for i in range(0, self.count):
      result = Sha1Sum(fuzz_path() + str(i) + '.txt').run().rstrip('\n')
      log.write(result + '\n')

    log.close()

class Differ:
  def __init__(self, size, count):
    print 'differ init with size = ' + str(size)
    self.size  = size
    self.count = count

  def run(self):
    v_22_diff_file = open(diff_path()[0], 'w+')
    java_diff_file = open(diff_path()[1], 'w+')

    for i in range(0, self.count):
      if i % 100 == 0:
        print 'diffing file # ' + str(i)
      out1 = exec_process(['sha1sum', fuzz_path() + str(i) + '.txt'])
      out2 = exec_process(['java', '-cp', 'src', 'Jsha1sum', fuzz_path() + str(i) + '.txt', str(self.size)])
      v_22_diff_file.write(out1)
      java_diff_file.write(out2)

    v_22_diff_file.close()
    java_diff_file.close()

class Oracle:
  def __init__(self):
    None

  def run(self):
    print 'Oracle is running...'
    log = Logger(res_path())

    out1 = exec_process([sha_path(), '-c', sums_path()])
    out2 = exec_process([sha_path(), '-c', diff_path()[0]])
    out3 = exec_process([sha_path(), '-c', diff_path()[1]])

    out4 = exec_process(['sha1sum', '-c', sums_path()])
    out5 = exec_process(['sha1sum', '-c', diff_path()[0]])
    out6 = exec_process(['sha1sum', '-c', diff_path()[1]])

    fails = out1.count('FAILED')
    if out1 == out2 and out2 == out3:
      if out4 == out5 and out5 == out6:
        if out1 == out4:
          if fails > 0:
            log.write('All digests match but there were still ' + str(fails) + ' failures! \n')
            log.write('  random seed = ' + str(NOW) + ' \n')
          else:
            log.write('All digests verified. \n')
        else:
          log.write('Coreutil digests do not match system digests! \n')
      else:
        log.write('System digests do not match! \n')
    else:
      log.write('Coreutil digests do not match! \n')

    log.close()
    print 'Oracle is finished.'

if __name__ == '__main__':
  NOW = time.time()
  random.seed(NOW)
  f = Fuzzer(int(sys.argv[1]), int(sys.argv[2]))
  f.fuzz()
  f.run()
  d = Differ(int(sys.argv[1]), int(sys.argv[2]))
  d.run()
  Oracle().run()
  print 'See ya!'
