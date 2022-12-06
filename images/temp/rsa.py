def isPrime(n):
  if n < 2:
    return False

  if n != 2 and n % 2 == 0:
    return False

  for i in range(3, int(n ** 0.5) + 1, 2):
    if n % i == 0:
      return False
  
  return True

def gcd(a, b):
  r1 = a
  r2 = b

  while r2 != 0:
    q = r1 // r2
    r = r1 - q * r2

    r1 = r2
    r2 = r
  
  return r1

def multiplicativeInverse(a, b):
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

  if t1 > 0:
    return t1
  else:
    return a + t1

def generateKeys():
  p = 0
  q = 0

  while True:
    p = int(input('Enter large prime p: '))

    if isPrime(p):
      break
    else:
      print('Given number is not prime')

  while True:
    q = int(input('Enter large prime q: '))

    if p == q:
      print('q can not be equal to p')
    elif isPrime(q):
      break
    else:
      print('Given number is not prime')
  
  n = p * q
  phi = (p - 1) * (q - 1)

  e = 0
  d = 0

  while True:
    e = int(input(f'Enter number e coprime to and less than {phi}: '))

    if e < phi and gcd(e, phi) == 1:
      d = multiplicativeInverse(phi, e)

      if e != d:
        break
      else:
        print('e == d not allowed; Try some other value for e')
    else:
      print('Given number not coprime')

  print(f'Public key: {{{e}, {n}}}')
  print(f'Private key: {{{d}, {n}}}')

# Iterative Function to calculate (x^n)%p in O(logy)
def power(x, y, p):
  res = 1 # Initialize result

  x = x % p # Update x if it is more than or equal to p

  while (y > 0):
    # If y is odd, multiply x with result
    if (y & 1):
      res = (res * x) % p

    # y must be even now
    y = y >> 1 # y = y/2
    x = (x * x) % p

  return res

def encrypt(plaintext, e, n):
  plainNums = list(map(ord, plaintext))
  cipherNums = []

  for M in plainNums:
    cipherNums.append(power(M, e, n))

  return ' '.join(map(str, cipherNums))

def decrypt(ciphertext, d, n):
  cipherNums = list(map(int, ciphertext.split()))
  plainNums = []

  for C in cipherNums:
    plainNums.append(power(C, d, n))
  
  return ''.join(map(chr, plainNums))

def main():
  print('RSA Algorithm:')
  print('1. Generate Keys')
  print('2. Encrypt')
  print('3. Decrypt')
  
  choice = int(input('Enter your choice: '))

  if choice not in [1, 2, 3]:
    print('Invalid choice')
    return
  
  if choice == 1:
    generateKeys()
  elif choice == 2:
    plaintext = input('Enter plaintext: ')

    print('Enter public key:')
    e = int(input('e = '))
    n = int(input('n = '))

    ciphertext = encrypt(plaintext, e, n)
    print(ciphertext)
  else:
    ciphertext = input('Enter ciphertext: ')

    print('Enter private key:')
    d = int(input('d = '))
    n = int(input('n = '))

    plaintext = decrypt(ciphertext, d, n)
    print(plaintext)

main()
