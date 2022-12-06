const { Server } = require('socket.io');
const prompt = require('prompt-sync')();

const io = new Server(3000);

let q, alpha, Xa, Ya, Yb, K;

io.on('connection', (socket) => {
  socket.on('start', () => {
    while (true) {
      q = parseInt(prompt('Enter large prime no. q: '));

      if (isPrime(q)) break;
      else console.log('Given no. not prime');
    }

    alpha = findPrimitive(q);

    console.log('Sending initial values', { q, alpha }, 'to client');
    socket.emit('q, alpha', { q, alpha });

    Xa = parseInt(prompt('Enter private key: '));
    Ya = power(alpha, Xa, q);

    console.log('Sending public key', { Ya }, 'to client');
    socket.emit('Ya', { Ya });
  });

  socket.on('Yb', (data) => {
    console.log('Received public key', data, 'from client');

    Yb = data.Yb;
    K = power(Yb, Xa, q);

    console.log('Secret key generated', { K });
  });
});

function isPrime(n) {
  if (n < 2) return false;

  const root = Math.sqrt(n);

  if (n != 2 && n % 2 == 0) return false;

  for (let i = 3; i < root; i += 2) {
    if (n % i == 0) return false;
  }

  return true;
}

// Iterative Function to calculate (x^n)%p in O(logy)
function power(x, y, p) {
  let res = 1n; // Initialize result
  let x_ = BigInt(x);
  let p_ = BigInt(p);

  x_ = x_ % p_; // Update x if it is more than or
  // equal to p

  while (y > 0) {
    // If y is odd, multiply x with result
    if (y & 1) res = (res * x_) % p_;

    // y must be even now
    y = y >> 1; // y = y/2
    x_ = (x_ * x_) % p_;
  }
  return Number(res);
}

// Utility function to store prime factors of a number
function findPrimefactors(s, n) {
  // Print the number of 2s that divide n
  while (n % 2 == 0) {
    s.add(2);
    n = n / 2;
  }

  // n must be odd at this point. So we can skip
  // one element (Note i = i +2)
  for (let i = 3; i <= Math.sqrt(n); i = i + 2) {
    // While i divides n, print i and divide n
    while (n % i == 0) {
      s.add(i);
      n = n / i;
    }
  }

  // This condition is to handle the case when
  // n is a prime number greater than 2
  if (n > 2) s.add(n);
}

// Function to find smallest primitive root of n
function findPrimitive(n) {
  let s = new Set();

  // Check if n is prime or not
  if (isPrime(n) == false) return -1;

  // Find value of Euler Totient function of n
  // Since n is a prime number, the value of Euler
  // Totient function is n-1 as there are n-1
  // relatively prime numbers.
  let phi = n - 1;

  // Find prime factors of phi and store in a set
  findPrimefactors(s, phi);

  // Check for every number from 2 to phi
  for (let r = 2; r <= phi; r++) {
    // Iterate through all prime factors of phi.
    // and check if we found a power with value 1
    let flag = false;
    for (let it of s) {
      // Check if r^((phi)/primefactors) mod n
      // is 1 or not
      if (power(r, phi / it, n) == 1) {
        flag = true;
        break;
      }
    }

    // If there was no power with value 1.
    if (flag == false) return r;
  }

  // If no primitive root found
  return -1;
}
