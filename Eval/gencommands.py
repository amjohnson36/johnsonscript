import random
import sys
num = int(sys.argv[1])
l = random.sample(range(1, 100), num)

with open('files/commands', 'w') as fp:
    for i in range(len(l)):
        fp.write("{0} {1}\n".format(str(1), str(l[i])))
    fp.write("0\n")

with open('files/vlist', 'w') as fp:
    for i in range(len(l)):
        fp.write("{},".format(str(l[i])))

