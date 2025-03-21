# RSA-Z-nZ Project

This project includes:

- 64-bit \(\mathbb{Z}/n\mathbb{Z}\) arithmetic and RSA
- Multi-precision big integers
- Galois Field \(\mathbf{F}_{128}\) (polynomial and Zech-log)

## Build and Run

1. **Compile**:
   ```bash
   make
    ```

## Executables:
- test_mybigint (multi-precision demo)
- test-znz (64-bit modular arithmetic)
- test-rsa (RSA with a single pair of primes)
- test-rsa-extended (RSA with multiple primes)
- f128-demo (F128 with polynomials)
- f128-zech-demo (F128​ with Zech logs)

### Run each:

```bash
./test_mybigint
./test-znz
./test-rsa
./test-rsa-extended
./f128-demo
./f128-zech-demo
```

## Clean up:

```bash
make clean
```
