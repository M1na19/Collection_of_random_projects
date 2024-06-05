import os
from colorama import Fore,init
repeats=10

init(autoreset=True)

for i in range(8):
    avg=0
    for j in range(repeats):
        result=os.popen("./Runable/main ./Examples/input"+str(i+1)+".in output.out").read()
        print(result)
        num=result.split().pop()
        avg+=int(num)
    print(Fore.CYAN+"INPUT"+str(i+1)+": "+str(avg/repeats)+" microseconds\n")
    