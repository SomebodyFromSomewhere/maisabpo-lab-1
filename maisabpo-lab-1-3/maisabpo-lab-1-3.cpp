#include <iostream>
#include <string>

template <typename T>
T gcdExtended(T a, T b, T* x, T* y);

template <typename T>
T binpow(T a, T n, T mod) {
	T res = 1;
	while (n != 0) {
		if (n & 1)
			res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

// Function to compute a^-1 under modulo m.
template <typename T>
T inv(T x, T mod) {
	return binpow<T>(x, mod - 2, mod);
}

// Function to compute a+b under modulo m.
template <typename T>
T sumM(T a, T b, T M)
{
	return (a + b) % M;
}

// Function to compute a-b under modulo m.
template <typename T>
T subM(T a, T b, T M)
{
	return (a - b + M) % M;
}

// Function to compute a*b under modulo m.
template <typename T>
T mulM(T a, T b, T M)
{
	return (a * b) % M;
}

// Function to find modulo inverse of b. It returns
// -1 when inverse doesn't
template <typename T>
T invM(T b, T m)
{
	T x, y; // used in extended GCD algorithm
	T g = gcdExtended(b, m, &x, &y);

	// Return -1 if b and m are not co-prime
	if (g != 1)
		return -1;

	// m is added to handle negative x
	return (x % m + m) % m;
}

// Function to compute a/b under modulo m.
template <typename T>
T divM(T a, T b, T m)
{
	a = a % m;
	T inv = invM(b, m);
	if (inv == -1)
		return -1;
	else
		return (inv * a) % m;
}

// Function for extended Euclidean Algorithm (used to
// find modular inverse.
template <typename T>
T gcdExtended(T a, T b, T* x, T* y)
{
	// Base Case
	if (a == 0)
	{
		*x = 0, * y = 1;
		return b;
	}

	T x1, y1; // To store results of recursive call
	T gcd = gcdExtended(b % a, a, &x1, &y1);

	// Update x and y using results of recursive
	// call
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}


template <typename T>
T powM(T a, T b, T M)
{
	uint64_t r = M == 1 ? 0 : 1;
	while (b > 0) {
		if (b & 1) r = mulM(r, a, M);
		b = b >> 1;
		a = mulM(a, a, M);
	}

	return r;
}

void printMessage(std::string functionName, int64_t value, int64_t expectedValue)
{
	bool status = (value == expectedValue);
	std::cout << "Function: " << functionName << "\tResult: " << value << "\tExpected: " << expectedValue << "\tStatus: " << ((status) ? "Ok" : "Failed") << std::endl;
}

bool test()
{
	uint64_t a = 123, b = 456, M = 551;
	uint64_t result = sumM<uint64_t>(a, b, M);
	printMessage("sumM", result, 28);

	result = subM<uint64_t>(a, b, M);
	printMessage("subM", result, 218);

	result = mulM<uint64_t>(a, b, M);
	printMessage("mulM", result, 437);

	result = powM<uint64_t>(a, b, M);
	printMessage("powM", result, 239);

	result = invM<uint64_t>(a, M);
	printMessage("invM", result, 112);

	result = invM<uint64_t>(b, M);
	printMessage("invM", result, -1);

	result = divM<uint64_t>(a, b, M);
	printMessage("divM", result, -1);

	result = divM<uint64_t>(b, a, M);
	printMessage("divM", result, 380); // In task result is 281, on planetcalc is 380.

	return true;
}

int main()
{
	test();

	return 0;
}