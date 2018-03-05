from math import  sqrt
def inp():
    counts = []
    print ("Do it")
    while True:
        count = input()
        if not count:
            break
        else:
            counts.append(float(count))
    print ("The length of list =   " +  str(len(counts)))
    print ("Sum of items =   " + str(sum(counts)))

    if len(counts) > 0:
        print("Arithmetic average =  " + str(sum(counts)/len(counts)))
        print("Max =  " + str(max(counts)))
        print("Min =  " + str(min(counts)))

    for i in counts:
        if i < 0:
            a = 0
            break
        elif i > 0:
            a = 1
    #print (a)
    if a == 1:
        print("Max element of sqrt" + str(max(counts,key = sqrt)))
        print("Min element of sqrt" + str(min(counts,key = sqrt)))
    else:
        print("Items < 0!")

inp()
