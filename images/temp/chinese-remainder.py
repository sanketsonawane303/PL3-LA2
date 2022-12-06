def calcMultInv(a: int, b: int):
  r1 = a
  r2 = b
  t1 = 0
  t2 = 1

  while r2 != 0:
    q = r1 // r2
    r = r1 - q * r2
    t = t1 - q * t2

    r1 = r2
    r2 = r
    t1 = t2
    t2 = t

  if r1 == 1:
    if t1 > 0:
      return t1
    else:
      return a + t1
  else:
    return None

def main():
  n = int(input('Enter no. of equations: '))
  a = list(map(int, input('Enter a0 a1 a2 ... an: ').split()))
  m = list(map(int, input('Enter m0 m1 m2 ... mn: ').split()))

  pM = 1
  for i in range(n):
    pM *= m[i]
  
  M = []
  for i in range(n):
    M.append(pM // m[i])

  MInv = []
  for i in range(n):
    MInv.append(calcMultInv(m[i], M[i]))
  
  x = 0
  for i in range(n):
    try:
      x = (x + a[i] * M[i] * MInv[i]) % pM
    except:
      print('m0 m1 m2.... not coprime')

  print('\na =', a)
  print('m =', m)
  print('pM =', pM)
  print('M =', M)
  print('MInv =', MInv)
  print('\nx =', x)

main()
