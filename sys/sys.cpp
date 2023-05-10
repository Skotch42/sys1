#include <iostream>
#include <iomanip>
#include <cstddef>
#include <bitset>
#include <intrin.h>

void* memoryAllocator = _ReturnAddress();
using namespace std;

class Assembler
{

public:

	void add(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			add eax, valueTwo

			mov result, eax
		}

		cout << "\n" << "add: " << result;
	}

	void subtract(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			sub eax, valueTwo

			mov result, eax
		}

		cout << "\n" << "subtract: " << result;
	}

	void multiply(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			mov ebx, valueTwo

			mul ebx

			mov result, eax
		}

		cout << "\n" << "multiply: " << result;
	}

	void divide(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			mov ebx, valueTwo
			mov edx, 0

			div ebx

			mov result, eax
		}

		cout << "\n" << "divide: " << result;
	}

	void Compare(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			cmp eax, valueTwo
			ja L0
			mov eax, valueTwo
			mov result, eax

			L0 : mov result, eax
		}

		cout << "\n" << "prints bigger number: " << result;
	}

	void Equal(int32_t valueOne, int32_t valueTwo)
	{
		int32_t result;

		__asm
		{
			mov eax, valueOne
			cmp eax, valueTwo
			je L1
			mov eax, 0
			mov result, eax

			L1 : mov result, eax
		}

		cout << "\n" << "prints number if they are equal: " << result;
	}

	void Not(uint16_t byte_1)
	{
		uint16_t result;

		__asm
		{
			mov ax, byte_1
			not ax

			mov result, ax
		}

		cout << "\n" << "not: " << bitset<8>{result} << "\t (BYTE_1: " << bitset<8>{byte_1} << ")";
	}

	void conjunction(uint16_t byte_1, uint16_t byte_2)
	{
		uint16_t result;

		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			and ax, bx

			mov result, ax
		}

		cout << "\n" << "and: " << bitset<8>{result} << "\t (BYTE_2: " << bitset<8>{byte_2} << ")";
	}

	void disjunction(uint16_t byte_1, uint16_t byte_2)
	{
		uint16_t result;

		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			or ax, bx

			mov result, ax
		}

		cout << "\n" << "or: " << bitset<8>{result};
	}

	void XOR(uint16_t byte_1, uint16_t byte_2)
	{
		uint16_t result;

		__asm
		{
			mov ax, byte_1
			mov bx, byte_2

			xor ax, bx

			mov result, ax
		}

		cout << "\n" << "xor: " << bitset<8>{result} << '\n';
	}

	void array_sum()
	{
		int32_t result = 0;

		const int n = 10;
		int sum = 0;
		int mass[n]{};

		for (size_t i = 0; i < n; i++)
		{
			mass[i] = rand() % 100 + 1;
		}

		for (size_t i = 0; i < n; i++)
		{
			cout << "[" << i << "] " << mass[i] << " ";
		}

		__asm
		{
			mov eax, sum
			mov ecx, n
			lea ebx, mass

			L :
			add eax, [ebx]
				add ebx, type mass
				dec ecx
				cmp ecx, 0
				jne L

				mov result, eax
		}

		cout << "\narray summ = " << result << '\n';
	}

	void shift_array(bool isRightShift, uint16_t byteValue)
	{
		uint16_t result;

		switch (isRightShift)
		{

		case true:

			__asm
			{
				mov ax, byteValue
				shr ax, 1

				mov result, ax
			}

			cout << "\n" << "shift right: " << result << '\t' << bitset<16>{result} << '\n';
			break;

		case false:

			__asm
			{
				mov ax, byteValue
				shl ax, 1

				mov result, ax
			}

			cout << "\n" << "shift left: " << result << '\t' << bitset<16>{result} << '\n';
			break;

		default:
			break;
		}
	}

};

int main()
{
	Assembler assembler;
	int32_t a, b;
	int32_t result;

	cout << "Enter 2 numbers: \n";
	cin >> a >> b;

	cout << setiosflags(ios::right);
	cout << '\n' << "a = " << a << " b = " << b << '\n';

	assembler.add(a, b);
	assembler.subtract(a, b);
	assembler.multiply(a, b);
	assembler.divide(a, b);
	cout << '\n';

	assembler.Compare(a, b);
	assembler.Equal(a, b);
	cout << '\n';

	uint16_t byteOne, byteTwo;

	cout << "\nEnter bytes: \n";
	cin >> byteOne >> byteTwo;

	assembler.Not(byteOne);
	assembler.conjunction(byteOne, byteTwo);
	assembler.disjunction(byteOne, byteTwo);
	assembler.XOR(byteOne, byteTwo);
	cout << '\n';

	assembler.array_sum();
	assembler.shift_array(true, byteOne);
	assembler.shift_array(false, byteTwo);

	return 0;
}