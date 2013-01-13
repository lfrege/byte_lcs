#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class dint
{
	public:
	int a;
	int b;
	int l;
	char c;

	dint()
	{
		a = 0;
		b = 0;
		l = 0;
		c = ' ';
	}

	dint(int x, int y, int z, char ch)
	{
		a = x;
		b = y;
		l = z;
		c = ch;
	}

	bool operator<(const dint& rhs) const
	{
		if (l < rhs.l)
		{
			return true;
		}
		else if (l > rhs.l)
		{
			return false;
		}
		else
		{
			if (b < rhs.b)
			{
				return true;
			}
			else if (b < rhs.b)
			{
				return false;
			}
			else
			{
				if (a < rhs.a)
				{
					return true;
				}
				else if (a < rhs.a)
				{
					return false;
				}
				else
				{
					return false;
				}
			}
		}
	}

	bool operator==(const dint& rhs) const
	{
		if (l == rhs.l && b == rhs.b && a == rhs.a)
		{
			return true;
		}
		return false;
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

vector<dint> reduce(const vector<dint>& temp)
{
	vector<dint> output;
	vector<dint> input = temp;
/*
	int lastx = input[input.size()-1].a + 1;
	int lasty = input[input.size()-1].b + 1;
*/
	int lastx = -1;
	int lasty = -1;
	int i;

	sort(input.begin(), input.end());

	for (i = 0; i < (int)input.size(); i++)
	{
		cout << input[i].a << "\t" << input[i].b << "\t" << input[i].l << "\t" << input[i].c; 
		if (input[i].a > lastx && input[i].b > lasty)
		{
			output.push_back(input[i]);
			lastx = input[i].a;
			lasty = input[i].b;
			cout << "\t" << input[i].c; 
		}
		cout << endl; 
	}

	return output;
}

vector<dint> overlap_list(const string& left, const string& right)
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
				output.push_back(dint(i,j,clist[j],right.at(j)));
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
	reduce(overlap_list("this is not a string", "this is a better string"));
}
