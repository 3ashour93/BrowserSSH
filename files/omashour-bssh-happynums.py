Sum = 0
#This Function calculates the sum of the square of each digitt of any number
def sumOfSquares(a):
    global Sum
    Sum =(a%10)**2 + Sum 
    if a == 0:
        a = Sum     
        Sum = 0
        return a
    a = a/10               
    return sumOfSquares(a)

def isHappy(a):    
    if sumOfSquares(a) == 4:       
        return False
    if sumOfSquares(a) == 1:
        return True
    else:
        return isHappy(sumOfSquares(a))
nu =int( raw_input("Enter a number to check its happiness:"))
print isHappy(nu)

print('ahmaddoooo')

