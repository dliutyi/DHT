#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ValidatorTests)
	{
	public:

		TEST_METHOD(ValidateCorrectValue)
		{
			byte_seq expected = { 1, 2, 3, 4 };

			Validator validator;
			byte_seq output = validator.Process("1234", {});

			Assert::IsTrue(expected[0] == output[0]
				&& expected[1] == output[1]
				&& expected[2] == output[2]
				&& expected[3] == output[3]);
		}

		TEST_METHOD(ValidationExceptionWhenMoreDigits)
		{
			Validator validator;
			Assert::ExpectException<std::exception>([&]() { validator.Process("12345", {}); });
		}

		TEST_METHOD(ValidationExceptionWhenIncorrectID)
		{
			Validator validator;
			Assert::ExpectException<std::exception>([&]() { validator.Process("abc", {}); });
		}
	};
}