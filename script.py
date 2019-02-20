import os

path = "Eval/"

count = 0
functions = 0
returns = ['void', 'int', 'Lexeme*']

for filename in os.listdir(path):
    if filename == 'files':
        for jfile in os.listdir(path+'files/'):
            with open(path+files+'/'+jfile, 'r') as ffp:
                for line in ffp.readlines():
                    count += 1

    else:
        with open(path + filename, 'r') as fp:
            for line in fp.readlines():
                count += 1
                if filename.endswith('.h'):
                    for r in returns:
                        if line.startswith(r):
                            functions += 1


print('Number of lines: ', count)
print('Number of funcs: ', functions)
