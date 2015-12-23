#!/usr/bin/python
# -*- coding: utf-8 -*-
# Portable testing system for IU9 students
# implemented by davvie, based on bandikoot's idea

import sys
import os
from termcolor import colored

def show_help():
  print colored('usage: ', 'magenta') + 'test.py xx-progname mode [-voff / -von] [-rws]'
  print 'xx: problem number (e.g. 01)'
  print 'mode:'
  print '0 - standard'
  print '1 - with command-line arguments'
  print '2 - without main()'
  print '-voff / -von: toggle valgrind (default: enabled)'
  print '-rws: replace ␣ characters with spaces'

def main():
    if len(sys.argv) < 3:
      show_help()
      return
    valgrindEnabled = True
    replaceWhiteSpaces = False
    mode = 0
    progname = ''
    if len(sys.argv) > 3:
      if sys.argv[3] == '-voff':
        valgrindEnabled = False
      if sys.argv[3] == '-rws':
        replaceWhiteSpaces = True
    if len(sys.argv) > 4:
      if sys.argv[4] == '-rws':
        replaceWhiteSpaces = True
    if len(sys.argv) > 2:
      progname = sys.argv[1]
      try:
        mode = int(sys.argv[2])
        if (mode > 2) or (mode < 0):
          print colored('error: mode out of range', 'cyan')
          return
      except:
        print colored('error: mode has to be a valid integer', 'cyan')
        return
    # replacing all ␣ characters with spaces if necessary
    if replaceWhiteSpaces:
      repl = []
      with open(progname + '.c', 'r') as f:
        for line in f.readlines():
          repl.append(line.replace('␣', ' '))
      with open(progname + '.c', 'w') as f:
        for line in repl:
            f.write(line)
    if mode != 2:
      os.system('gcc -o %s -g "%s.c" -lm' % (progname, progname))
    testFolderPath = os.path.abspath('..') + '/tests/' + progname + '/'
    testFiles = []
    if mode == 0:
      testFiles = [x for x in os.listdir(testFolderPath) if '.' not in x]
    elif mode == 1:
      testFiles = [x for x in os.listdir(testFolderPath) if '.arg' in x or '.' not in x]
    elif mode == 2:
      testFiles = [x for x in os.listdir(testFolderPath) if '.main.c' in x]
    testFiles = sorted(testFiles, key = lambda x: int(x.replace('.arg', '').replace('.main.c', '')))
    for tfile in testFiles:
      print colored('running test ' + tfile, 'yellow')
      cmd = ''
      if mode == 0:
        cmd = './%s < %s > result.txt' % (progname, testFolderPath + tfile)
      elif mode == 1:
        args = ''
        with open(testFolderPath + tfile, 'r') as argFile:
          args = argFile.read().replace('\n', '')
        cmd = './%s %s > result.txt' % (progname, args)
      elif mode == 2:
        with open('temp.c', 'w') as outfile:
          filesToMerge = [testFolderPath + tfile, progname + '.c']
          for item in filesToMerge:
            with open(item) as mfile:
              outfile.write(mfile.read())
        os.system('gcc -o %s -g "%s.c" -lm' % ('temp', 'temp'))
        cmd = './temp > result.txt'
      if valgrindEnabled:
        cmd = 'valgrind -q ' + cmd
        valgrindOutput = os.popen(cmd).read()
        if len (valgrindOutput) > 0:
          print colored('test %s failed. valgrind log:' % (tfile, ), 'red')
          print valgrindOutput
      else:
        os.system(cmd)
      diffOutput = os.popen('diff -b result.txt ' + testFolderPath + tfile.replace('.arg', '').replace('.main.c', '') + '.a').read()
      if len(diffOutput) > 0:
        print colored('test %s failed:' % (tfile, ), 'red')
        print diffOutput
        break
    os.remove('result.txt')
    if mode == 2:
      os.remove('temp.c')
      os.remove('temp')
    else:
      os.remove(progname)


if __name__ == '__main__':
    main()
