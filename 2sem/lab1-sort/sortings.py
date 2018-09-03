import random as rd
import time

def show(array):
    print(array[:])
def radix(array):
    pass
def oddEven(array):
    start = time.time()
    sorted = False
    while sorted is False:
        sorted = True
        for i in range(1, len(array)-1, 2):
            if array[i] > array [i+1]:
                array[i], array[i+1] = array[i+1], array[i]
                sorted = False
        for i in range(0, len(array), 2):
            if array[i] > array [i+1]:
                array[i], array[i+1] = array[i+1], array[i]
                sorted = False
    print("elapsed time: %s seconds" % (time.time() - start))
def quick(self):
    pass

array = [rd.randint(0, 100000) for i in range(int(input("enter size: ")))]
#show(array)
oddEven(array)
#show(array)