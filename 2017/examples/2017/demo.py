import random
import time
import os
import sys


while True: 
    strn = ''
    rows, columns = os.popen('stty size', 'r').read().split()
    for i in range(0, int(columns)): 
        unimax = 0x266B
        num = random.randint(0, unimax) 
        letter = chr(num)
        strn += letter# + '(' + str(hex(num)) + ')'
    print(strn)
    sys.stdout.flush()

    time.sleep(0.05)
