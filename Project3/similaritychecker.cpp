#include <string>
#include <stdexcept>
#include <set>

using namespace std;

class SimilarityChecker
{
public:
	const int MAX_LENGTH_RESULT = 60;
	const int MAX_ALPHA_RESULT = 40;

	int checkLength(const string& a, const std::string& b)
	{
		size_t bigger = a.length();
		size_t smaller = b.length();

		if (bigger < smaller) swap(bigger, smaller);

		if (checkZero(bigger, smaller)) return length_result = 0;
		if (checkMax(bigger, smaller)) return length_result = MAX_LENGTH_RESULT;
		return calculateLengthResult(MAX_LENGTH_RESULT, bigger, smaller);
	}


	int checkAlpha(const string& a, const std::string& b)
	{
		assertSmallLetter(a, b);

		set<char> sa;
		set<char> sb;
		makeSetAandB(a, b, sa, sb);

		int sameCnt = getSameCnt(sa, sb);
		int totalCnt = getTotalCnt(sa, sb, sameCnt);

		return calculateAlphaResult(MAX_ALPHA_RESULT, totalCnt, sameCnt);
	}

	void checkAll(const string& a, const std::string& b)
	{
		checkLength(a, b);
		checkAlpha(a, b);
	}

	int getLengthResult()
	{
		return length_result;
	}

	int getAlphaResult()
	{
		return alpha_result;
	}

	int getResult()
	{
		return getLengthResult() + getAlphaResult();
	}

private:
	int length_result = 0;
	int alpha_result = 0;

	bool checkZero(size_t bigger, size_t smaller)
	{
		return bigger == 0 || smaller == 0 || bigger >= smaller * 2;
	}

	bool checkMax(size_t bigger, size_t smaller)
	{
		return bigger == smaller;
	}

	void makeSetAandB(const string& a, const std::string& b, set<char>& sa, set<char>& sb)
	{
		for (const auto& ch : a)
		{
			sa.insert(ch);
		}

		for (const auto& ch : b)
		{
			sb.insert(ch);
		}
	}

	int getSameCnt(set<char> sa, set<char> sb)
	{
		int sameCnt = 0;
		for (const auto& ch_b : sa)
		{
			auto it = sb.find(ch_b);
			if (it != sb.end()) sameCnt++;
		}
		return sameCnt;
	}

	int getTotalCnt(set<char> sa, set<char> sb, int sameCnt)
	{
		return sa.size() + sb.size() - sameCnt;
	}

	bool isSmallLetter(const string& a, const string& b)
	{
		for (auto const& ch : a)
		{
			if (ch >= 'A' && ch <= 'Z') continue;
			return true;
		}

		for (auto const& ch : b)
		{
			if (ch >= 'A' && ch <= 'Z') continue;
			return true;
		}
		return false;
	}

	void assertSmallLetter(const string& a, const std::string& b)
	{
		if (isSmallLetter(a, b))
		{
			throw std::invalid_argument("�ҹ��� ���Ե�");
		}
	}

	int calculateLengthResult(const int MAX, size_t bigger, size_t smaller)
	{
		return length_result = MAX - ((bigger - smaller) * MAX / smaller);
	}

	int calculateAlphaResult(const int MAX, int totalCnt, int sameCnt)
	{
		return alpha_result = sameCnt * MAX / totalCnt;
	}
};
