#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <unordered_map>

class Soundex
{

    public:

    const std::string NotADigit{"*"};

    std::string Encode(const std::string& word) const
    {
        return ZeroPad(UpperFront(Head(word)) + Tail(EncodedDigits(word)));
    }

    std::string EncodedDigit(char letter) const
    {
        auto encodings = std::unordered_map<char, std::string>{
            {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
            {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
            {'d', "3"}, {'t', "3"},
            {'l', "4"},
            {'m', "5"}, {'n', "5"},
            {'r', "6"}
            };
        auto it = encodings.find(std::tolower(letter)); 
        return it == encodings.end() ? NotADigit : it->second;
    } 
    
    private:
    
    std::string UpperFront(const std::string& word) const
    {
        return std::string(1, std::toupper(static_cast<unsigned char>(word.front())));
    }

    std::string LastDigit(const std::string& encoding) const
    {
        if(encoding.empty())
        {
            return NotADigit;
        }
        return std::string(1, encoding.back());
    }

    std::string ZeroPad(const std::string& word) const
    {
        auto zerosNeeded = MaxCodeLength - word.length();
        return word + std::string(zerosNeeded, '0');
    }

    std::string Tail(const std::string& word) const
    {
        return word.substr(1);
    }

    std::string Head(const std::string& word) const
    {
        return word.substr(0, 1);
    }

    std::string EncodedDigits(const std::string& word) const
    {
        auto encoding = std::string();
        EncodeHead(encoding, word);
        EncodeTail(encoding, word);
        return encoding;
    }

    void EncodeHead(std::string& encoding, const std::string& word) const
    {
        encoding += EncodedDigit(word.front());
    }

    void EncodeTail(std::string& encoding, const std::string& word) const
    {
        for(auto i = 1; i < word.length(); i++)
        {
            if(!IsComplete(encoding))
            {
                EncodeLetter(encoding, word[i], word[i - 1]);
            } 
        }
    }

    void EncodeLetter(std::string& encoding, char letter, char lastLetter) const
    {
        auto digit = EncodedDigit(letter);
        if(digit != NotADigit && 
        (digit != LastDigit(encoding) || IsVowel(lastLetter)))
        {
            encoding += digit; 
        }
    }

    bool IsVowel(char letter) const
    {
        return std::string("aeiouy").find(std::tolower(letter)) != std::string::npos;
    }

    bool IsComplete(const std::string& encoding) const
    {
        return encoding.length() == MaxCodeLength;
    }

    const size_t MaxCodeLength = 4;
};


class SoundexEncoding : public testing::Test
{

    public:
    Soundex soundex;

};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    ASSERT_EQ(soundex.Encode("A"), std::string("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_EQ(soundex.Encode("I"), std::string("I000"));
}

TEST_F(SoundexEncoding, ReplaceConsonatsWithAppropriateDigits)
{
    ASSERT_EQ(soundex.Encode("Ax"), std::string("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
    ASSERT_EQ(soundex.Encode("A#"), std::string("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_EQ(soundex.Encode("Acdl"), std::string("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_EQ(soundex.Encode("Dcdlb").length(), 4);
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
    ASSERT_EQ(soundex.Encode("BaAeEiIoOuUhHyYcdl"), "B234");
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    ASSERT_EQ(soundex.EncodedDigit('b'), soundex.EncodedDigit('f'));
    ASSERT_EQ(soundex.EncodedDigit('c'), soundex.EncodedDigit('g'));
    ASSERT_EQ(soundex.EncodedDigit('d'), soundex.EncodedDigit('t'));
    ASSERT_EQ(soundex.Encode("Abfcgdt"), "A123");
}

TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
    ASSERT_THAT(soundex.Encode("abcd"), testing::StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonant)
{
    ASSERT_THAT(soundex.Encode("BCDL"), testing::Eq(soundex.Encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicate1st)
{
    ASSERT_THAT(soundex.Encode("Bbcd"), testing::Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingSeparatedByVowels)
{
    ASSERT_THAT(soundex.Encode("Jbob"), testing::Eq("J110"));
}