const { io } = require('socket.io-client');
const prompt = require('prompt-sync')();

const socket = io('ws://localhost:3000');

let q, alpha, Xb, Yb, Ya, K;

socket.emit('start');

socket.on('q, alpha', (data) => {
  console.log('Received initial values', data, 'from server');

  q = data.q;
  alpha = data.alpha;
});

socket.on('Ya', (data) => {
  console.log('Received public key', data, 'from server');

  Xb = parseInt(prompt('Enter private key: '));
  Yb = power(alpha, Xb, q);

  console.log('Sending public key', { Yb }, 'to server');
  socket.emit('Yb', { Yb });

  Ya = data.Ya;
  K = power(Ya, Xb, q);

  console.log('Secret key generated', { K });
});

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
