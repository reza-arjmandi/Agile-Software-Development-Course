#include "pch.h"
#include "IPConverter.h"

class IPConverterTest : public testing::Test
{
protected:
	std::unique_ptr<IPConverter> m_IPConverter;

	void SetUp() override
	{
		m_IPConverter = std::make_unique<IPConverter>();
	}
};

TEST_F(IPConverterTest, Construction)
{
}

TEST_F(IPConverterTest, GivenAStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedAValidIntegerIP_TestCase1)
{
	//Given
	auto ipStr = std::string("192.168.43.1");
	auto expectedIpInt = 3232246529;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);
	
	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedAValidIntegerIP_TestCase2)
{
	//Given
	auto ipStr = std::string("172.168.43.200");
	auto expectedIpInt = 2896702408;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedAValidIntegerIP_TestCase3)
{
	//Given
	auto ipStr = std::string("0.0.0.0");
	auto expectedIpInt = 0;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedAValidIntegerIP_TestCase4)
{
	//Given
	auto ipStr = std::string("255.255.255.255");
	auto expectedIpInt = 4294967295;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedAValidIntegerIP_TestCase5)
{
	//Given
	auto ipStr = std::string("1.2.3.4");
	auto expectedIpInt = 16909060;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnEmptyStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne)
{
	//Given
	auto ipStr = std::string("");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase1)
{
	//Given
	auto ipStr = std::string("1.2");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase2)
{
	//Given
	auto ipStr = std::string("1.2.3");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase3)
{
	//Given
	auto ipStr = std::string("1");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase4)
{
	//Given
	auto ipStr = std::string("1.2.3.4.5");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase5)
{
	//Given
	auto ipStr = std::string("...");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase6)
{
	//Given
	auto ipStr = std::string("256.0.257.1");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase7)
{
	//Given
	auto ipStr = std::string("256.0.25756");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase8)
{
	//Given
	auto ipStr = std::string("256.0.25756.5689.45876");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase9)
{
	//Given
	auto ipStr = std::string("250.-10.1.0");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}

TEST_F(IPConverterTest, GivenAnInvalidStringIP_WhenStrToLongIntCalledWithIt_ThenExpectRetreivedMinusOne_TestCase10)
{
	//Given
	auto ipStr = std::string("Invalid.Ip.Address.");
	auto expectedIpInt = -1;

	//When
	auto ipInt = m_IPConverter->StrToLongInt(ipStr);

	//Then
	ASSERT_EQ(ipInt, expectedIpInt);
}