#include <iostream>
#include <cstdint>

using namespace std;

int32_t wordCount(char *s)
{
	int32_t isPrevChar = 0;
	int32_t wordCnt = 0;
	int32_t i = 0;
	
	while(s[i] != '\0')
	{
		if (s[i] != ' ')
		{
			isPrevChar = 1;
			i++;
		}
		else
		{
			if (isPrevChar)
				wordCnt++;
			isPrevChar = 0;
			
			while(s[i] == ' ') i++;
		}
	}
	return (wordCnt + isPrevChar);
}

bool areAnagrams(char *s1, char *s2)
{
	int32_t h[26] = {0};
	
	int32_t i = 0;
	
	while (s1[i] != '\0')
	{
		h[s1[i] - 'a']++;
		i++;
	}
	
	i = 0;
	while(s2[i] != '\0')
	{
		h[s2[i] - 'a']--;
		if (h[s2[i] - 'a'] < 0) return false;
		i++;
	}

	for (i = 0; i < 26; i++)
	{
		if (h[i]) return false;
	}
	return true;
}

void Perm1(char *s, int pos)
{
	static int marker[10] = {0};
	static char R[10] = {0};
	
	if (s[pos] == '\0')
	{
		R[pos] = '\0';
		cout << "Perm 1 : \"" << R << "\"" << endl;
		return;
	}
	
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (marker[i] == 0)
		{
			R[pos] = s[i];
			marker[i] = 1;
			Perm1(s, pos+1);
			marker[i] = 0;
		}
	}
}

void Perm2(char *s, int l, int h)
{	
	if (l == h)
	{
		cout << "Perm 2 : \"" << s << "\"" << endl;
		return;
	}
	
	for (int i = l; i <= h; i++)
	{
		swap(s[l], s[i]);
		Perm2(s, l+1, h);
		swap(s[l], s[i]);
	}
}

int32_t main()
{
	char s[] = "ABC";
	
	cout << "Input String : \"" << s << "\"" << endl;
	
	Perm1(s, 0);
	
	cout << endl;

	Perm2(s, 0, 2);

/* Anagrams

	char s1[] = "structure";
	char s2[] = "cturestru";
	
	cout << "Input String1 : \"" << s1 << "\"" << endl;
	cout << "Input String2 : \"" << s2 << "\"" << endl;
	
	cout << "Strings are : " << (areAnagrams(s1, s2) ? "Anagrams" : "Not Anagrams" ) << endl;
*/
	
// Word Count
	
//	char s[] = "    Hello,     World!   Good    Morning....";
//	cout << "Input String : \"" << s << "\"" << endl;
	
//	cout << "Word Count : " << wordCount(s) << endl;
	
	return 0;
}
