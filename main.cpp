#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class dint
{
	public:
	int a;
	int b;
	int l;

	dint()
	{
		a = 0;
		b = 0;
		l = 0;
	}

	dint(int x, int y, int z)
	{
		a = x;
		b = y;
		l = z;
	}
};

int max(int a, int b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

vector<dint> byte_lcs(const string& left, const string& right)
{
	int i, j;
	int *clist = new int[right.length()];
	int *plist = new int[right.length()];
	int *temp;
	vector<dint> output;

	for (j = 0; j < (int)right.length(); j++)
	{
		plist[j] = 0;
	}

	for (i = 0; i < (int)left.length(); i++)
	{
		for (j = 0; j < (int)right.length(); j++)
		{
			if (left.at(i) == right.at(j))
			{
				if (j == 0)
				{
					clist[j] = 1;
				}
				else
				{
					clist[j] = plist[j-1] + 1;
				}
				cout << i << " " << j << " " << clist[j] << right.at(j) << endl;
			}
			else
			{
				if (j == 0)
				{
					clist[j] = plist[j];
				}
				else
				{
					clist[j] = max(clist[j-1], plist[j]);
				}
			}
		}
		temp = plist;
		plist = clist;
		clist = temp;
	}

	return output;
}

int main(int argc, char** argv)
{
	byte_lcs("this is not a string", "this is a better string");
}
