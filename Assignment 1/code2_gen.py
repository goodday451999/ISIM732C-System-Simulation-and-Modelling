import random 

def func(x, coeff): 
    value = 0
    for i in range(0,len(coeff)):
        value = value + (coeff[i] * pow(x, i))
    return value

def func_check(a, b, coeff):
    if (func(a, coeff) * func(b, coeff) > 0): 
       return -1
    else:
        return 1

def bisection(l, r, coeff): 
    mid = l  
    if func(l, coeff) == 0:
    	print("The root is : ","%.4f"%l)
	#return
    if func(r, coeff) == 0:
    	print("The root is : ","%.4f"%r)  
	#return
	
    while ((r-l) >= 0.001): 
  
        mid = (l+r)/2
   
        if (func(mid, coeff) == 0.0): 
            break
   
        if (func(mid, coeff) * func(l, coeff) < 0): 
            r = mid 
        else: 
            l = mid 
              
    print("The root is : ","%.4f"%mid) 
      

coeff = []
degree = int(input("Enter the degree: "))
for i in range(0,degree+1):
    print("Enter the coefficient {}".format(i))
    c_val = int(input())
    coeff.append(c_val)


cf = -1
while(cf == -1):
    a = random.randint(-100, 100)
    b = random.randint(-100, 100)
    cf = func_check(a, b, coeff)

if(a > b):
    c = a
    a = b
    b = c 

bisection(a, b, coeff)
