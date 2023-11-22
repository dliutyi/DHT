#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PNGEncoderTests)
	{
	public:
		TEST_METHOD(EncodePNG)
		{
			byte_seq expected =
			{
				0b10001001, 0b01010000, 0b01001110, 0b01000111, 0b00001101, 0b00001010, 0b00011010, 0b00001010,
				0b00000000, 0b00000000, 0b00000000, 0b00001101, 0b01001001, 0b01001000, 0b01000100, 0b01010010,
				0b00000000, 0b00000000, 0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001,
				0b00000001, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011001, 0b00100010, 0b01001101,
				0b11011010, 0b00000000, 0b00000000, 0b00000000, 0b00010011, 0b01001001, 0b01000100, 0b01000001,
				0b01010100, 0b00001000, 0b10011001, 0b01100011, 0b11111000, 0b10101111, 0b11000101, 0b10110101,
				0b01010111, 0b01010011, 0b01110011, 0b11100111, 0b01111111, 0b01011100, 0b00000000, 0b00000000,
				0b10011011, 0b00001111, 0b00011011, 0b11100011, 0b11001111, 0b00011110, 0b11111011, 0b01010000,
				0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01001001, 0b01000101, 0b01001110, 0b01000100,
				0b10101110, 0b01000010, 0b01100000, 0b10000010
			};

			byte_seq initial =
			{
				0b11111111, 0b00101010, 0b00001010, 0b10111101, 0b00101001, 0b00101001, 0b10111001, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
			};

			PNGEncoder pngEncoder;
			byte_seq output = pngEncoder.Process("1337", initial);

			Assert::IsTrue(expected.size() == output.size());
			for (int i = 0; i < expected.size(); ++i) {
				Assert::IsTrue(expected[i] == output[i]);
			}
		}
	};
}