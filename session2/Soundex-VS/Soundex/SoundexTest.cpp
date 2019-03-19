#include "pch.h"
#include "Soundex.h"

class SoundexEncoding : public testing::Test
{
protected:
	Soundex soundex;

};

TEST_F(SoundexEncoding, GivenAnObjectContstructedFromSoundexWhenEncodeIsCalledWithAOneLetterWordThenReturnWholeOfWordWithZeroPadding)
{
	ASSERT_EQ(soundex.Encode("A"), "A000");
}

TEST_F(SoundexEncoding, GivenAnObjectConstructedFromSoundexWhenEncodeIsCalledWithAWordThenConsonatLettersMustBeReplacedWithProperDigits)
{
	ASSERT_EQ(soundex.Encode("Ab"), "A100");
}

TEST_F(SoundexEncoding, GivenAnObjectConstructedFromSoundexWhenEncodeIsCalledWithAnEmptyArgumentThenMustReturenEmptyString)
{
	ASSERT_EQ(soundex.Encode(""), "");
}

TEST_F(SoundexEncoding, GivenAnObjectConstructedFromSoundexWhenEncodeIsCalledWithAWordThenMustReturnProperCode)
{
	ASSERT_EQ(soundex.Encode("Abcd"), "A123");
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetic)
{
	ASSERT_EQ(soundex.Encode("A#"), "A000");
}

TEST_F(SoundexEncoding, CombinesAdjacentlyDuplicatedDigits)
{
	ASSERT_EQ(soundex.Encode("Abfcjdd"), "A123");
}

TEST_F(SoundexEncoding, DoesntCombineAdjacentlyDuplicatedDigitsWhen)
{
	ASSERT_EQ(soundex.Encode("Abfcjdd"), "A123");
}