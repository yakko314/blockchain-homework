# INPUT
P=(493,5564)
Q=(1539,4742)
R=(4403,5202)

a = 497
b = 1768
p = 9739


def add(P,Q):
    if P is None:
        return Q
    if Q is None:
        return P

    x1,y1 = P
    x2,y2 = Q
    if x1 == x2 and (y1+y2) % p == 0:
        return None

    if P == Q:
        # lam = (3*x1^2+a)/2*y1
        num = (3 * x1**2 + a ) % p
        den_inv = pow(2*y1,-1,p)

        lam = (num*den_inv) % p
        # we dont divide, we mulitply by inverse
    else:
        # lam = (y2-y1)/(x2-x1)
        num = (y2-y1) % p
        den_inv = pow(x2-x1, -1, p)
        lam = (num*den_inv) % p
        # same story
    x3 = (lam**2 - x1 - x2 ) % p
    y3 = (lam * (x1 - x3) - y1) % p
    return x3,y3


# X=(5274,2841)
# Y=(8669,740)
# print(add(X,Y))
# print(add(X,X))


sol = add(P,P)
sol = add(sol,Q)
sol = add(sol,R)
print(sol)


