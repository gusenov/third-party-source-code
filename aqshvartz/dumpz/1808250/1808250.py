#from math import gcd
#print(gcd(20,8))

#recursion
def gcd(a, b):
    a = abs(a)
    b = abs(b)
    if b == 0:
        return a
    elif a == 0:
        return b
    elif a < b:
        return gcd(b % a, a)
    else:
        return gcd(a % b, b)

print(gcd(3542,2464))

def lcm(a,b):
    return ((abs( a * b) / gcd(a,b)))

#print(lcm(3,4))

def IsPrime(n):
    d = 2
    while d * d <= n and n % d != 0:
        d += 1
    return d * d > n
#print (IsPrime(4))

#cycles
def nod2(m,n):
    while n:
        m,n = n, m % n
    return abs(m)

def lcm2(a,b):
    return ((abs( a * b) / gcd(a,b)))
