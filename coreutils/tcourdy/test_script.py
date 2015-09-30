import subprocess
import filecmp

testFile= "/home/tarik/Documents/cs5959/cut_testing/cut_test_file2.txt";
writeLocation = "/home/tarik/Documents/cs5959/cut_testing/cutResult";
cutUtil= "/home/tarik/Documents/cs5959/core_utils_repo/coreutils/obj-gcov/src/cut";

#print(cutUtil + " -c 1 " + testFile + " >> " + writeLocation + "1.txt");

subprocess.call(cutUtil + " -c 1 " + testFile + " > " + writeLocation + "1_1.txt", shell=True);
subprocess.call(cutUtil + " -c 4-10 " + testFile + " > " + writeLocation + "2_2.txt", shell=True);
subprocess.call(cutUtil + " -b 1 " + testFile + " > " + writeLocation + "3_3.txt", shell=True);
subprocess.call(cutUtil + " -b 2-7 " + testFile + " > " + writeLocation + "4_4.txt", shell=True);
subprocess.call(cutUtil + " -f 1 " + testFile + " > " + writeLocation + "5_5.txt", shell=True);
subprocess.call(cutUtil + " -d ':' -f 1- " + testFile + " > " + writeLocation + "6_6.txt", shell=True);
subprocess.call(cutUtil + " -d ' ' -f 7- " + testFile + " > " + writeLocation + "7_7.txt", shell=True);
subprocess.call(cutUtil + " -c 7- " + testFile + " > " + writeLocation + "8_8.txt", shell=True);
subprocess.call(cutUtil + " -b 7- " + testFile + " > " + writeLocation + "9_9.txt", shell=True);
subprocess.call(cutUtil + " -d ':' -s -f 1- " + testFile + " > " + writeLocation+ "10_10.txt", shell=True);

#compare files to known correct files from simple test file
assert(filecmp.cmp(writeLocation + "1.txt", writeLocation + "1_1.txt") == True);
assert(filecmp.cmp(writeLocation + "2.txt", writeLocation + "2_2.txt") == True);
assert(filecmp.cmp(writeLocation + "3.txt", writeLocation + "3_3.txt") == True);
assert(filecmp.cmp(writeLocation + "4.txt", writeLocation + "4_4.txt") == True);
assert(filecmp.cmp(writeLocation + "5.txt", writeLocation + "5_5.txt") == True);
assert(filecmp.cmp(writeLocation + "6.txt", writeLocation + "6_6.txt") == True);
assert(filecmp.cmp(writeLocation + "7.txt", writeLocation + "7_7.txt") == True);
assert(filecmp.cmp(writeLocation + "8.txt", writeLocation + "8_8.txt") == True);
assert(filecmp.cmp(writeLocation + "9.txt", writeLocation + "9_9.txt") == True);
assert(filecmp.cmp(writeLocation + "10.txt", writeLocation + "10_10.txt") == True);

#print(filecmp.cmp(writeLocation + "1.txt", writeLocation + "1_1.txt"));
#print(filecmp.cmp("/home/tarik/Documents/cs5959/cut_testing/cutResult1.txt", "/home/tarik/Documents/cs5959/cut_testing/cutResult1_1.txt"));

#error call
subprocess.call(cutUtil + " -c 0 " + testFile + " > " + writeLocation+ "11.txt", shell=True);

#valgrind check for leaks
#subprocess.call("valgrind " + cutUtil + " -c 1 " + testFile, shell=True);
#subprocess.call("valgrind " + cutUtil + " -c 4-10 " + testFile, shell=True);
#subprocess.call("valgrind " + cutUtil + " -b 1 " + testFile , shell=True);
#subprocess.call("valgrind " + cutUtil + " -b 2-7 " + testFile, shell=True);
#subprocess.call("valgrind " + cutUtil + " -f 1 " + testFile , shell=True);
#subprocess.call("valgrind " + cutUtil + " -d ':' -f 1- " + testFile , shell=True);
#subprocess.call("valgrind " + cutUtil + " -d ' ' -f 7- " + testFile , shell=True);
#subprocess.call("valgrind " + cutUtil + " -c 7- " + testFile  , shell=True);
#subprocess.call("valgrind " + cutUtil + " -b 7- " + testFile , shell=True);
#subprocess.call("valgrind " + cutUtil + " -d ':' -s -f 1- " + testFile , shell=True);
