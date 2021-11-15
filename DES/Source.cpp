#include "iostream"
#include "stdio.h"
#include "string"
#include "deque"
#include "math.h"

using namespace std;

template <typename T>
struct ArrayT
{
	T* arr;
	int size = 64;
};
template <typename T>
using  ArrayType = struct ArrayT<T>;

typedef enum {
	Round1, Round2, Round3, Round4,
	Round5, Round6, Round7, Round8,
	Round9, Round10, Round11, Round12,
	Round13, Round14, Round15, Round16,

} RoundNo;

template <typename T>
class DES {
private:
	char * plainText; // last one for null '\0'
	char * key ;
	int binaryPlainText[64];
	int binaryKey[64];
	int* rBinary;
	int binaryIntialPermutation[64];
	int binaryInverseInitalPermutation[64];
	int binaryPermutationChoiceOneKey[56];
	int	binaryPermutationChoiceTwoKey[48];
	int binaryExpansionPermutation[48];
	int binaryOutputSBox[32];
	int binaryPermutation[32];

	int binaryDataLeft[32];
	int binaryDataRight[32];
	int binaryOutput[64];
	char outChar[16];

	deque<T> * roundKeyL = new deque<T>();
	deque<T> * roundKeyR = new deque<T>();

public:
	DES(char * p,char * k) {
		plainText = p;
		key = k;

		//turn all chars to decimal value ...
		//for plainText
		int i = 0;
		while (true) {
			plainText[i] = charToInt(plainText[i]);
			i++;
			if (i == 16) {
				break;
			}
			/*if (plainText[i] == '\0') {
				break;
			}*/
		}

		//for key
		i = 0;
		while (true) {
			key[i] = charToInt(key[i]);
			i++;
			if (i == 16) {
				break;
			}
			/*if (key[i] == '\0') {
				break;
			}*/
		}


		//turn all decimal value to binary ...
		
		//for plainText
		i = 0;
		while (true) {
			rBinary = halfByteToBinary(plainText[i]);
			for (int j = 0; j < 4; j++) {
				binaryPlainText[(i * 4) + j] = rBinary[j];
			}
			i++;
			if (i == 16) {
				break;
			}
		}

		//for key
		i = 0;
		while (true) {
			rBinary = halfByteToBinary(key[i]);
			for (int j = 0; j < 4; j++) {
				binaryKey[(i * 4) + j] = rBinary[j];
			}
			i++;
			if (i == 16) {
				break;
			}
			/*if (key[i] == '\0') {
				break;
			}*/
		}

	}

	ArrayType<T> getBinaryPlainText() {
		//ArrayType<T> out = 
		return { binaryPlainText,64};
	}
	ArrayType<T> getBinaryIntialPermutation() {
		return { binaryIntialPermutation, 64 };
	}
	ArrayType<T> getBinaryInverseIntialPermutation() {
		return { binaryInverseInitalPermutation , 64 };
	}
	ArrayType<T> getBinaryPermutationChoiceOneKey() {
		return { binaryPermutationChoiceOneKey, 56 };
	}
	ArrayType<T> getBinaryPermutationChoiceTwoKey() {
		return { binaryPermutationChoiceTwoKey,48 };
	}
	ArrayType<T> getBinaryExpansionPermutation() {
		return { binaryExpansionPermutation,48 };
	}
	ArrayType<T> getBinaryOutputSBox() {
		return { binaryOutputSBox,32 };
	}
	ArrayType<T> getBinaryPermutation() {
		return { binaryPermutation,32 };
	}
	ArrayType<T> getBinaryDataLeft() {
		return { binaryDataLeft,32 };
	}
	ArrayType<T> getBinaryDataRight() {
		return { binaryDataRight,32 };
	}
	ArrayType<T> getBinaryOutput() {
		for (int i = 0; i < 64; i++)
			binaryOutput[i] = binaryInverseInitalPermutation[i];
		return { binaryOutput,64 };
	}

	void printArray(ArrayType<T> a) {
		for (int i = 0; i < a.size; i++) {

			cout << a.arr[i];
		}
	}
	/*void printBinaryPlainText() {
		for (int i = 0; i < 64; i++) {

			cout << binaryPlainText[i];
		}
	}*/

	/*void printBinaryIntialPermutation() {
		for (int i = 0; i < 64; i++) {

			cout << binaryIntialPermutation[i];
		}
	}*/

	
	/*void printInverseBinaryIntialPermutation() {
		for (int i = 0; i < 64; i++) {

			cout << binaryInverseInitalPermutation[i];
		}
	}*/

	
	/*void printBinaryPermutationChoiceOneKey() {
		for (int i = 0; i < 56; i++) {

			cout << binaryPermutationChoiceOneKey[i];
		}
	}*/
	void swap(ArrayType<T> a, ArrayType<T> b) {
		int temp[32];
		for (int i = 0; i < a.size; i++) {
			temp[i] = a.arr[i];
			a.arr[i] = b.arr[i];
			b.arr[i] = temp[i];
		}
	}
	void minusOne(ArrayType<T> a) {
		
		for (int i = 0; i < a.size ; i++) {
			a.arr[i]--;
		}
	}
	void replace(T* a, T* b) {
		T temp = *a;
		*a = *b;
		*b = temp;
	}
	int charToInt(char a) {
		if (a < 58 && a > 47) {
			a -= 48;
		}
		else if (a < 71 && a > 64)
		{
			a = (a - 65) + 10;
		}
		else {
			a = -1;
		}
		return a;
	}
	int* halfByteToBinary(T p) {
		int bin[4];
		for (int i = 0; i < 4; i++) {
			bin[i] = p & 0x8 ? 1 : 0;
			p <<= 1;
		}
		return bin;
	}
	int * halfByteBinaryToInt(T * p) {
		int ints[16][4];
		int out[16];
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 4; j++) {
				ints[i][j] = p[(4 * i) + j];
			}
		}
		for (int i = 0; i < 16; i++) {
			out[i] = 8 * ints[i][0] + 4 * ints[i][1] + 2 * ints[i][2] + 1 * ints[i][3];
		}
		return out;
	}
	char intToChar(int a) {
		if (a < 10 && a > -1) {
			a += 48;
		}
		else if (a < 16 && a > 9)
		{
			a = (a - 10) + 65;
		}
		else {
			a = -1;
		}
		return a;
	}

	char * evaluateOutputChar(T* in) {
		int * outV ;
	//	outV = halfByteBinaryToInt(binaryOutput);
		outV = halfByteBinaryToInt(in);
		for (int i = 0; i < 16; i++) {
		outChar[i] = intToChar(outV[i]);
		}
		return  outChar;
	}
	ArrayType<char> getOutChar() {
		return { outChar,16 };
	}
	void printOutChar() {
		for (int i = 0; i < outChar; i++) {

			cout << outChar[i];
		}
	}
	void printArrayChar(ArrayType<char> a) {
		for (int i = 0; i < a.size; i++) {

			cout << a.arr[i];
		}
	}
	
	T* initalPermutation() {
		int initailTable[64] = {
			58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9, 1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7
		};
		minusOne({ initailTable,64 });
		for (int i = 0; i < 64; i++) {
			binaryIntialPermutation[i] = binaryPlainText[initailTable[i]];
		}
		for (int i = 0; i < 32; i++) {
			binaryDataLeft[i] = binaryIntialPermutation[i];
		}
		for (int i = 0; i < 32; i++) {
			binaryDataRight[i] = binaryIntialPermutation[i+32];
		}
		return binaryIntialPermutation;
	}
	T* inverseInitalPermutation(T * data) {
		int inverseTable[64] = {
			40, 8, 48, 16, 56, 24, 64, 32,
			39, 7, 47, 15, 55, 23, 63, 31,
			38, 6, 46, 14, 54, 22, 62, 30,
			37, 5, 45, 13, 53, 21, 61, 29,
			36, 4, 44, 12, 52, 20, 60, 28,
			35, 3, 43, 11, 51, 19, 59, 27,
			34, 2, 42, 10, 50, 18, 58, 26,
			33, 1, 41, 9, 49, 17, 57, 25
		};
		minusOne({ inverseTable,64 });
		for (int i = 0; i < 64; i++) {
			binaryInverseInitalPermutation[i] = data[inverseTable[i]];
		}
		return binaryInverseInitalPermutation;
	}
	T* permutationChoiceOneKey() {
		int choiceOneTable[56] = {
			57, 49, 41, 33, 25, 17, 9,
			1, 58, 50, 42, 34, 26, 18,
			10, 2, 59, 51, 43, 35, 27,
			19, 11, 3, 60, 52, 44, 36,
			63, 55, 47, 39, 31, 23, 15,
			7, 62, 54, 46, 38, 30, 22,
			14, 6, 61, 53, 45, 37, 29,
			21, 13, 5, 28, 20, 12, 4
		};
		minusOne({ choiceOneTable,56 });
		for (int i = 0; i < 56; i++) {
			binaryPermutationChoiceOneKey[i] = binaryKey[choiceOneTable[i]];
		}
		return binaryPermutationChoiceOneKey;
	}

	void leftShiftCircularDeque(deque<T> * dq) {
		T temp;
		temp = dq->front();
		dq->pop_front();
		dq->push_back(temp);
	}
	void leftShifCircularKey(int r) {

		//temp = roundR.front();
		//roundR.pop_front();
		//roundR.push_back(temp);
		//temp = roundL.front();
		//roundL.pop_front();
		//roundL.push_back(temp);

		switch (r)
		{
		case Round1:
			for (int i = 0; i < 28; i++) {
				roundKeyL->push_back(binaryPermutationChoiceOneKey[i]);
				roundKeyR->push_back(binaryPermutationChoiceOneKey[i + 28]);
			}
			for (int i = 0; i < 1; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round2:
			for (int i = 0; i < 1; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round3:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round4:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round5:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round6:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round7:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round8:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round9:
			for (int i = 0; i < 1; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round10:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round11:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round12:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round13:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round14:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round15:
			for (int i = 0; i < 2; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;
		case Round16:
			for (int i = 0; i < 1; i++) {
				leftShiftCircularDeque(roundKeyL);
				leftShiftCircularDeque(roundKeyR);
			}
			break;

		default:
			break;
		}


	}
	T* permutationChoiceTwoKey(int r) {
		int choiceTwoTable[48] = {
			14, 17, 11, 24, 1, 5,
			3, 28, 15, 6, 21, 10,
			23, 19, 12, 4, 26, 8,
			16, 7, 27, 20, 13, 2,
			41, 52, 31, 37, 47, 55,
			30, 40, 51, 45, 33, 48, 
			44, 49, 39, 56, 34, 53, 
			46, 42, 50, 36, 29, 32 
		};
		int tempA[56];
		minusOne({ choiceTwoTable, 48 });
		leftShifCircularKey(r);
			deque <int> ::iterator it;
		int j = 0;
		for (it = roundKeyL->begin(); it != roundKeyL->end(); ++it) {
			
			tempA[j] = *it;
			j++;
		}
		
		for (it = roundKeyR->begin(); it != roundKeyR->end(); ++it) {
			
			tempA[j] = *it;
			j++;
		}
		for (int i = 0; i < 48; i++) {
			binaryPermutationChoiceTwoKey[i] = tempA[choiceTwoTable[i]];
		}
		return binaryPermutationChoiceTwoKey;
	}
	T* expansionPermutation(T * dataRight) {
		int expanstionTable[48] = {
			32, 1, 2, 3, 4, 5,
			4, 5, 6, 7, 8, 9,
			8, 9, 10, 11, 12, 13,
			12, 13, 14, 15, 16, 17,
			16, 17, 18, 19, 20, 21,
			20, 21, 22, 23, 24, 25,
			24, 25, 26, 27, 28, 29,
			28, 29, 30, 31, 32, 1
		};
		minusOne({ expanstionTable,48 });
		for (int i = 0; i < 48; i++) {
			binaryExpansionPermutation[i] = dataRight[expanstionTable[i]];
		}
		return binaryExpansionPermutation;
	}
	T* permutation(T* data) {
		int permutationTable[32] = {
			16, 7, 20, 21,
			29, 12, 28, 17, 
			1, 15, 23, 26,
			5, 18, 31, 10,
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25,
		};
		minusOne({ permutationTable,32 });
		for (int i = 0; i < 32; i++) {
			binaryPermutation[i] = data[permutationTable[i]];
		}
		return binaryPermutation;
	}
	T* sBox(T* xorData) {
		//xordata is 48 bits

		//the table for s boxes
		int sT[8][4][16] = {
			14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
			15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
			10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
			13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
			1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
			7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
			13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
			10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
			3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
			2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
			14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
			4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
			11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
			12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
			10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
			9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
			4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
			4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
			13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
			1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
			6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
			13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
			1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
			7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
			2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
		};

		int sI[8][6];
		int sO[8];

		// devide the input to 8 for the 8 boxes
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				sI[i][j] = xorData[6*i + j];
			}
		}

		//evalute each input box by the row and col from the bits of the i/p and get th corresponding val from the table 
		for (int i = 0; i < 8; i++) {
			int row = (2 * sI[i][0]) + (sI[i][5]);
			int col = (8 * sI[i][1]) + (4 * sI[i][2]) + (2 * sI[i][3]) + (1 * sI[i][4]);
			sO[i] = sT[i][row][col];
		}

		//turn the o/p from val int to binary
		for (int i = 0; i < 8; i++) {
			rBinary = halfByteToBinary(sO[i]);
			for (int j = 0; j < 4; j++) {
				 binaryOutputSBox[(i * 4) + j] = rBinary[j];
			}
		}
		return  binaryOutputSBox;
		/*	if (si[i][0] == 0 && si[i][5] == 0) {

			}
			else if (si[i][0] == 0 && si[i][5] == 1) {

			}
			else if (si[i][0] == 1 && si[i][5] == 0) {

			}
			else if (si[i][0] == 1 && si[i][5] == 1) {

			}*/	
	}

	void round(int r, T * binaryKeyChoiceTwo) {
		int temp[32];
		int xorOutput[48];
		//left = right
		for (int i = 0; i < 32; i++) {
			temp[i] = binaryDataLeft[i];
			binaryDataLeft[i] = binaryDataRight[i];
			
		}
		
		//printArrayChar({ evaluateOutputChar(temp) ,8});
		//cout << "	";

		//make expansion permutation
		expansionPermutation(binaryDataRight);
		
		
		//  binaryExpan xor choice2Key
		for (int i = 0; i < 48; i++) {
			xorOutput[i] = binaryExpansionPermutation[i] ^ binaryKeyChoiceTwo[i];
		}

		//reduce from 48 to 32 by sbox
		sBox(xorOutput);

		//premutation for the 32 bit
		permutation(binaryOutputSBox);

		// leftData (temp) xor the result
		for (int i = 0; i < 32; i++) {
			binaryDataRight[i] = binaryPermutation[i] ^ temp[i];
		}

		//printArrayChar({ evaluateOutputChar(binaryDataRight) ,8});
		//cout << endl;
	}
	void encrypt() {

		int tempOutSwap[64];
		int tempRoundKey[16][48];

		// make the 1st permut for key to transfer from 64 to 56 to delete the parity
		permutationChoiceOneKey();

		// make the 1st permut for plain text
		initalPermutation();
		
		//prepare the key for to be use for each round
		for (int i = 0; i < 16; i++)
		{

			permutationChoiceTwoKey(i);
			for (int j = 0; j < 48; j++) {
				tempRoundKey[i][j] = binaryPermutationChoiceTwoKey[j];
			}
		}

		for (int i = 0; i < 16; i++)
		{
			////prepare the key for to be use for each round
			//permutationChoiceTwoKey(i);
			round(i,tempRoundKey[i]);
		}
		swap({binaryDataLeft,32}, {binaryDataRight,32});
		for (int i = 0; i < 32; i++) {
			tempOutSwap[i] = binaryDataLeft[i];
			tempOutSwap[i+32] = binaryDataRight[i];
		}
		inverseInitalPermutation(tempOutSwap);
	}
	void decrypt() {
		int tempOutSwap[64];
		int * roundKey;
		int tempRoundKey[16][48];

		// make the 1st permut for key to transfer from 64 to 56 to delete the parity
		permutationChoiceOneKey();

		// make the 1st permut for cipher text
		initalPermutation();

		//prepare the key for to be use for each round
		for (int i = 0; i < 16; i++)
		{
			permutationChoiceTwoKey(i);
			for (int j = 0; j < 48; j++) {
				tempRoundKey[i][j] = binaryPermutationChoiceTwoKey[j];
			}
		}

		for (int i = 0; i < 16; i++)
		{
			//make the round algorithm
			round(i, tempRoundKey[15-i]);
		}
		swap({ binaryDataLeft,32 }, { binaryDataRight,32 });
		for (int i = 0; i < 32; i++) {
			tempOutSwap[i] = binaryDataLeft[i];
			tempOutSwap[i + 32] = binaryDataRight[i];
		}
		inverseInitalPermutation(tempOutSwap);
	}

};

void encrytFn(char* plainText,char * key) {
	DES<int> d = DES<int>(plainText, key);
	d.encrypt();
	d.evaluateOutputChar(d.getBinaryOutput().arr);
	cout << "cipher: ";
	d.printArrayChar(d.getOutChar());
}
void decrytFn(char* cipherText, char* key) {
	DES<int> d = DES<int>(cipherText, key);
	d.decrypt();
	d.evaluateOutputChar(d.getBinaryOutput().arr);
	cout << "plain: ";
	d.printArrayChar(d.getOutChar());
}


int main(int argc, char** argv) {
	char plainText0[17] = "7A6C731D22347676"; // last one for null '\0'
	char key0[17] = "1323445A6D788381";
	//char cipherText[17] = "7DB033DD14D6F975";
	//char keyD[17] = "1323445A6D788381";
	string input = "";
	string operation = "";
	char* plainText = plainText0;
	char* key= key0;
	for (int i = 0; i < argc ; i++) {
		if (i == 0) {
			input += argv[i];
		}
		if (i == 1) {
			operation += argv[i];
		}
		if (i == 2) {
			plainText = argv[i];
		}
		if (i == 3) {
			key = argv[i];
		}
	}

	if (operation == "encrypt") {
		encrytFn(plainText, key);
	}
	else if (operation == "decrypt")
	{
		decrytFn(plainText, key);
	}
	//DES<int> d = DES<int>(plainText, key);
	//cout << endl;
	//d.encrypt();
	//d.printArray(d.getBinaryOutput());
	//cout << endl;
	//d.evaluateOutputChar();
	//d.printArrayChar(d.getOutChar());
	//d.initalPermutation();
	//d.printArray(d.getBinaryIntialPermutation());
	//cout << endl;
	//d.inverseInitalPermutation(d.getBinaryIntialPermutation().arr);
	//d.printArray(d.getBinaryInverseIntialPermutation());
	//cout << endl;
	//d.permutationChoiceOneKey();
	//d.printArray( d.getBinaryPermutationChoiceOneKey());
	//cout << endl;
	//d.permutationChoiceTwoKey(Round1); //check it again the o/p
	//d.printArray(d.getBinaryPermutationChoiceTwoKey());
	//cout << endl;
	//d.sBox(d.getBinaryPermutationChoiceTwoKey().arr);
	//d.printArray(d.getBinaryOutputSBox());
	//cout << endl;
	//d.permutation(d.getBinaryOutputSBox().arr);
	//d.printArray(d.getBinaryPermutation());
	//cout << endl;
	//d.permutationChoiceTwoKey(Round2);
	//d.printArray(d.getBinaryPermutationChoiceTwoKey());
	//cout << endl;
	//d.permutationChoiceTwoKey(Round3);
	//d.printArray(d.getBinaryPermutationChoiceTwoKey());



	return 0;
}


//
//template <typename T>
//void minusOne(T* a) {
//	for (int i = 0; i < 64; i++) {
//		a[i]--;
//	}
//}
//
//template <typename T>
//T * initalPermutation(T * binary) {
//	int binaryIntialPermutation[64];
//	int initailTable[64] = {
//		58, 50, 42, 34, 26, 18, 10, 2,
//		60, 52, 44, 36, 28, 20, 12, 4,
//		62, 54, 46, 38, 30, 22, 14, 6,
//		64, 56, 48, 40, 32, 24, 16, 8,
//		57, 49, 41, 33, 25, 17, 9, 1,
//		59, 51, 43, 35, 27, 19, 11, 3,
//		61, 53, 45, 37, 29, 21, 13, 5,
//		63, 55, 47, 39, 31, 23, 15, 7
//	};
//	minusOne(initailTable);
//	for (int i = 0; i < 64; i++) {
//		binaryIntialPermutation[i] = binary[initailTable[i]];
//	}
//	return binaryIntialPermutation;
//}
//
//
//template <typename T>
//void replace (T* a,T*b) {
//	T temp  = *a;
//	*a = *b;
//	*b = temp;
//}
//
//int charToInt(char a) {
//	if (a < 58 && a > 47) {
//		a -= 48;
//	}
//	else if (a < 71 && a > 64)
//	{
//		a = (a - 65) + 10;
//	}
//	else {
//		a = -1;
//	}
//	return a;
//}
//template <typename T> 
//int * halfByteToBinary(T p){
//	int binary[4];
//	for (int i = 0; i < 4; i++) {
//		binary[i] = p & 0x8 ? 1 : 0;
//		p <<= 1;
//	}
//	return binary;
//}


//int main(int argc, char** argv) {
//	
//	char plainText[17] = "7A6C731D22347676"; // last one for null '\0'
//	char key[17] = "1323445A6D788381";
//
//	DES<int> d =  DES<int>(plainText,key);
//	d.initalPermutation();
//	d.printBinary();
//	cout << endl;
//	d.printBinaryIntialPermutation();

	//int binary[64];
	//int* rBinary;
	//int * binaryIntialPermutation;
	//int b[64];

	////turn all chars to decimal value ...
	//int i = 0;
	//while (true) {
	//	plainText[i] = charToInt(plainText[i]);
	//	i++;
	//	if(plainText[i] == '\0') {
	//		break;
	//	}
	//}
	//

	////turn all decimal value to binary ...
	//i = 0;
	//while (true) {
	//	rBinary = halfByteToBinary(plainText[i]);
	//	for (int j = 0; j < 4; j++) {
	//		binary[(i * 4) + j]= rBinary[j];
	//	}
	//	i++;
	//	if (plainText[i] == '\0') {
	//		break;
	//	}
	//}
	//binaryIntialPermutation = initalPermutation(binary);

	//for (int i = 0; i < 64; i++) {
	//	b[i] = binaryIntialPermutation[i];
	//}
	//for (int i = 0; i < 64; i++) {

	//	cout << binary[i];
	//}
	//cout << endl;
	//for (int i = 0; i < 64; i++) {

	//	cout <<b[i];
	//}
	//cout << endl<<binary[57]<<b[0];

//	return 0;
//}