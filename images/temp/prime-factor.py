import time

start_time = time.time()

primes = [] # read from file

print('Reading data from file')
with open('p.txt', 'r') as file:
  for line in file:
    primes.append(int(line))
  file.close()
print('Read completed')

end_time = time.time()
duration = end_time - start_time
print('Time taken to read file:', duration)

def factorizeSemiprime(num, digits):
  start_time = time.time()

  found = False
  root = num ** 0.5

  factor = None

  for p in primes:
    if p > root:
      break

    if num % p == 0:
      factor = p
      found = True
      break

  end_time = time.time()
  duration = end_time - start_time

  print(f'Time taken for {num} ({digits} digits):', duration)
  if found:
    print(f'{num} = {factor} * {num // factor}')
  else:
    print('Can not be computed using available preprocessed data')


semiprimes = [1000010666663, 10000079888899, 100000008888889, 1000000518888883, 10000000058888887, 100000005178888819, 1000000000099987889, 10000000000097987989, 100000000088787877679]
digits = [12, 13, 14, 15, 16, 18, 17, 19, 20]

for i in range(len(semiprimes)):
  factorizeSemiprime(semiprimes[i], digits[i])
