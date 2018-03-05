def function(list1):
    x = {}
    i = 0
    counter = 0
    while i < len(list1):
        st = list1[i]
        if(st is list1[i]):
            counter = counter + 1
            i = i + 1
        x[st] = counter
       
    return x
   
   
   
list1 = ['comp1', 'comp1', 'comp1', 'comp2', 'comp2']
y = function(list1)
print y