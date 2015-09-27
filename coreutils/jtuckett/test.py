import base64
import re
import os
import datetime
import random
import string
from subprocess import Popen, PIPE

inputFileName = 'inputFile.txt'
outputFileName = 'outputFile'
oracleFileName = 'oracle.txt'
seed = datetime.datetime.now()
random.seed()


def execute( argIn ):
    arguments = ['./base64']
    for args in argIn:
        arguments.append(args)
    ps  = Popen(arguments, stdout=PIPE, stderr=PIPE)
    result = ps.communicate()
    return result

def reportError(section, error):
    print("Error")
    log = open('log.txt', 'a')
    log.write("Error in:  " + section + " Output:  " + error+"\n\n\n\n")

def generateCharacter():
    bits = ''
    for bit in range(8):
        bits += random.sample({'0','1'}, 1)[0]
    return chr(int(bits, 2))

def generateRandomFile():
    #number of characters
    charCount = random.sample(xrange(100000), 1)[0]
    toReturn = ""
    for c in range(charCount):
        toReturn += generateCharacter()
    #return string
    return toReturn;

def getResults(inputs):
    results = execute( inputs )
    if results[1] != "":
        reportError("Execute: ", results[1]+"   ".join(inputs))
    return results[0]

def reciprocal():
    inputFile = open(inputFileName, 'w')
    outputFile = open(outputFileName, 'w')
    toEncode = generateRandomFile()
    inputFile.write(toEncode)
    inputFile.close()
    results = getResults( [inputFileName] )
    outputFile.write(results)
    outputFile.close()
    results = getResults(['-d', outputFileName])
    if toEncode != results:
        reportError("Reciprocal", "Original is different from Encoded/decoded")

def oracle():
    inputFile = open(inputFileName, 'w')
    codedString = generateRandomFile()
    inputFile.write(codedString)
    inputFile.close()
    resultsCore = getResults( [inputFileName, '-w 0'] )
    resultsOracle = base64.b64encode(codedString)
    for i in range(len(resultsCore)):
        if resultsCore[i] != resultsOracle[i]:
            reportError("Oracle", "Strings do not match at position: %d received:  " + resultsCore[i] + " Expected: " +resultsOracle[i])


def ignoreOption():
    inputFile = open(inputFileName, 'w')
    toDecode = generateRandomFile()
    inputFile.write(toDecode)
    inputFile.close()
    getResults(['-i', inputFileName])

getResults(['--help'])
getResults(['--version'])
testFile = open('testFile.txt', 'w')
while True:
    print("Reciprocal")
    reciprocal()
    print("Oracle")
    oracle()
    print("IgnoreOption")
    ignoreOption()
