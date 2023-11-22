#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(EncoderTests)
	{
	public:
		TEST_METHOD(EncodeTheSequence)
		{
			byte_seq expected =
			{
				0b11111111, 0b00101010, 0b00001010, 0b10111101, 0b00101001, 0b00101001, 0b10111001, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
				0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
			};

			byte_seq initial = { 1, 3, 3, 7 };

			Encoder encoder;
			byte_seq output = encoder.Process("1337", initial);

			Assert::AreEqual(expected.size(), output.size());
			for (int i = 0; i < expected.size(); ++i) {
				Assert::AreEqual(expected[i], output[i]);
			}
		}
	};
}