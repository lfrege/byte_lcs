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
	bool done;

	dint()
	{
		a = 0;
		b = 0;
		l = 0;
		c = ' ';
		done = false;
	}

	dint(int x, int y, int z, char ch)
	{
		a = x;
		b = y;
		l = z;
		c = ch;
		done = false;
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
	int maxl=0;
	vector<dint> output;
	vector<dint> input = temp;
	vector<int> stack;
	bool foundone;
	bool exitloop = false;

	int i;

	sort(input.begin(), input.end());

	for (i = 0; i < (int)input.size(); i++)
	{
		if (input[i].l > maxl)
		{
			maxl = input[i].l;
		}
	}

	while (!exitloop)
	{
		if (stack.empty())
		{
			for (i = 0; i < (int)input.size(); i++)
			{
				if (!input[i].done)
				{
					stack.push_back(i);
					i = input.size();
				}
			}
		}

		foundone = false;

		for (i = stack.back(); i < (int)input.size()
			&& input[i].l <= input[stack.back()].l + 1; i++)
		{
			if (!input[i].done
				&& input[i].a > input[stack.back()].a
				&& input[i].b > input[stack.back()].b
				&& input[i].l > input[stack.back()].l)
			{
				foundone = true;
				stack.push_back(i);
				i = input.size();
			}
		}

		if (!foundone)
		{
			input[stack.back()].done = true;
			stack.pop_back();
		}
		if ((int)stack.size() == maxl)
		{
			exitloop = true;
		}
	}

	for (i = 0; i < (int)stack.size(); i++)
	{
		output.push_back(input[stack[i]]);
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

string hexPair(int input)
{
	string output;
	int low = input & 0xf;
	int high = (input & 0xf0) >> 4;

	cerr << endl << endl << low << endl << endl;

	if (high <= 9){output += (char)(high + '0');}
	else {output += (char)(high + 'A' - 10);}
	if (low <= 9){output += (char)(low + '0');}
	else {output += (char)(low + 'A' - 10);}

	return output;
}

string HTMLSafe(char ch)
{
	string output;

	if (ch == ' ' || ch == '\t') { output = ch; }
	else if (ch == '<') { output = "&lt;"; }
	else if (ch == '>') { output = "&gt;"; }
	else if (ch == '&') { output = "&amp;"; }
	else if (ch >= ']' && ch <= '~') { output = ch; }
	else if (ch >= '!' && ch <= '[') { output = ch; }
	else
	{
		output = "\\x" + hexPair(ch);
	}
	return output;
}

string HTMLSafe(const string& input)
{
	string output;
	int i;

	for (i = 0; i < (int)input.length(); i++)
	{
		output += HTMLSafe(input.c_str()[i]);
	}

	return output;
}

string inverseColoredLCS(const vector<dint>& lcs, const string& left, const string& right)
{
	int i = 0;
	string leftsub, rightsub; 
	string output;

	output += HTMLSafe(lcs[0].c);
	for (i = 1; i < (int)lcs.size(); i++)
	{
		leftsub = HTMLSafe(left.substr(lcs[i-1].a + 1, lcs[i].a - lcs[i-1].a - 1));
		rightsub = HTMLSafe(right.substr(lcs[i-1].b + 1, lcs[i].b - lcs[i-1].b - 1));
		if (lcs[i].a != lcs[i-1].a + 1 && lcs[i].b != lcs[i-1].b + 1)
		{
			if (leftsub != rightsub)
			{
				output += "<font color=\"green\">" + rightsub + "</font>";
				output += "<font color=\"red\">" + leftsub + "</font>";
			}
		}
		else if (lcs[i].a != lcs[i-1].a + 1)
		{
			output += "<font color=\"red\">" + leftsub + "</font>";
		}
		else if (lcs[i].b != lcs[i-1].b + 1)
		{
			output += "<font color=\"green\">" + rightsub + "</font>";
		}
		output += HTMLSafe(lcs[i].c);
	}

	return output;
}

bool readAll(const string& filename, string& output)
{
	char buffer[501];
	ifstream ifs;
	ifs.open(filename.c_str());

	if (ifs.is_open())
	{
		do
		{
			ifs.read(buffer, 500);
			output += buffer;
		} while(!ifs.eof() && !ifs.bad());

		return true;
	}
	else
	{
		cerr << "Error: could not read from file: " << filename << endl;
		return false;
	}
}

int main(int argc, char** argv)
{
	string a;
	string b;

	if (argc != 3)
	{
		cerr << "Error: requires 2 file names" << endl;
		return -1;
	}
	else if (!readAll(argv[1], a))
	{
		return -1;
	}
	else if (!readAll(argv[2], b))
	{
		return -1;
	}

	vector<dint> lcs = reduce(overlap_list(a,b));

	cout << inverseColoredLCS(lcs, a, b) << endl;

	return 0;
}
