import subprocess
import filecmp
import os
import string
import random
import shutil
import sys


CONST_SMALL = 1024;
CONST_MED = CONST_SMALL * 1000;
CONST_LRG = CONST_MED * 50;
CUT_LOCATION = "/home/tarik/Documents/cs5959/core_utils_repo/coreutils/obj-gcov/src/cut";
CUT_COMPARE_LOCATION = "/usr/bin/cut";
CUT_OPTIONS = ['b', 'f', 'c'];
WRITE_LOCATION = "/home/tarik/Documents/cs5959/cut_testing/tempCutFile";
ERROR_LOCATION = "/home/tarik/Documents/cs5959/cut_testing/fuzzErrors";
FILE_COUNT = 1;
LOOP_COUNT = 150;

smallFile = open("smallRandom.txt", "w+");
medFile = open("medRandom.txt", "w+");
lrgFile = open("lrgRandom.txt", "w+");

outerCount = 49;

def callCut(option, start, end, theFile):
    global FILE_COUNT;
    global CUT_LOCATION;
    global CUT_COMPARE_LOCATION;
    global WRITE_LOCATION;
    global ERROR_LOCATION;
#You can't cut in reverse order. (ie: 100-50 doesn't work.  correct syntax is 50-100).  I have tested that cut catches this correctly so I'm not including it in fuzzing
    if(end < start):
        temp = start;
        start = end;
        end = temp;

    if(option == 'f'):
        delimiter = random.choice(string.printable);
        if(delimiter == '"' or delimiter == "'"):
            return;
        #print(CUT_LOCATION + " -d '" + delimiter + "' -f " + start + "-" + end + " " + theFile + ">" + WRITE_LOCATION + str(FILE_COUNT) + " 2>>" + ERROR_LOCATION + "/error.txt");
        subprocess.call(CUT_LOCATION + " -d '" + delimiter + "' -f " + start + "-" + end + " " + theFile + ">" + WRITE_LOCATION + str(FILE_COUNT) + " 2>>" + ERROR_LOCATION + "/error.txt", shell=True);
        #subprocess.call("valgrind --logfile='valgrind.txt'" + CUT_LOCATION + " -d " + delimiter + " -f " + start + "-" + end + " " + theFile + "> /dev/null 2>&1", shell=True);
        subprocess.call(CUT_COMPARE_LOCATION + " -d '" + delimiter + "' -f " + start + "-" + end + " " + theFile + ">" + WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT) + " 2>>" + ERROR_LOCATION + "/error.txt", shell=True);
    else:
        subprocess.call(CUT_LOCATION + " -" + option + " " + start + "-" + end + " " + theFile + ">" + WRITE_LOCATION + str(FILE_COUNT) + " 2>>" + ERROR_LOCATION + "/error.txt", shell=True);
        #subprocess.call("valgrind --logfile='valgrind.txt'" + CUT_LOCATION + " -" + option + " " + start + "-" + end + " " + theFile + "> /dev/null 2>&1", shell=True);
        subprocess.call(CUT_COMPARE_LOCATION + " -" + option + " " + start + "-" + end + " " + theFile + ">" + WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT) + " 2>>" + ERROR_LOCATION + "/error.txt", shell=True);

#if the files aren't the same between both versions of cut then there is a problem.  Copy them to error directory for further analysis and then delete.  If they are the same then just delete them for next fuzz.
    if(filecmp.cmp(WRITE_LOCATION + str(FILE_COUNT), WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT)) == False):
        badFile = open(WRITE_LOCATION + str(FILE_COUNT));
        if(delimiter is not None):
            badFile.write(CUT_LOCATION + " -d '" + delimiter + "' -f " + start + "-" + end + " " + theFile );
        else:
            badFile.write(CUT_LOCATION + " -" + option + " " + start + "-" + end + " " + theFile);
        badFile.close();    
        shutil.copy(WRITE_LOCATION + str(FILE_COUNT), ERROR_LOCATION);
        shutil.copy(WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT), ERROR_LOCATION);
        os.remove(WRITE_LOCATION + str(FILE_COUNT));
        os.remove(WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT));
        FILE_COUNT+=1; #only have to increase file count if we save this number to error directory.
        print("ERROR CHECK ERROR DIRECTORY!");
    else:
        os.remove(WRITE_LOCATION + str(FILE_COUNT));
        os.remove(WRITE_LOCATION + str(FILE_COUNT) + "_" + str(FILE_COUNT));
        

#create the random files
while(outerCount < LOOP_COUNT):
    while(os.path.getsize(smallFile.name) <= CONST_SMALL):
        line = "";
        while(len(line) <= 80):
            line += random.choice(string.printable);

        smallFile.write(line);


    while(os.path.getsize(medFile.name) <= CONST_MED):
        line = "";
        while(len(line) <= 80):
            line += random.choice(string.printable);

        medFile.write(line);


    while(os.path.getsize("lrgRandom.txt") <= CONST_LRG):
        line = "";
        while(len(line) <= 80):
            line += random.choice(string.printable);

        lrgFile.write(line);


    #create some random options for cut command and then execute them on each of the files
    innerCount = 0;
    while(innerCount < LOOP_COUNT):
        option = random.choice(CUT_OPTIONS);
        start = random.randint(1, sys.maxint);
        end = random.randint(1, sys.maxint);
        callCut(option, str(start), str(end), smallFile.name);
        callCut(option, str(start), str(end), medFile.name);
        callCut(option, str(start), str(end), lrgFile.name);
        innerCount +=1;

   
    outerCount += 1     

smallFile.close();
medFile.close();
lrgFile.close();