#include<iostream>
#include <vector>
#include <cassert>
#include <chrono>

using namespace std;

void printVect(const vector<char>& v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}

bool IsPermutation(vector<char> v, int n)
{
    vector<char> freq(v.size(), 0);
    for (int i = 0; i <= n; i++)
    {
        freq[v[i] - 'a']++;
    }

    for (unsigned int i = 0; i < freq.size(); i++)
    {
        if (freq[i] > 1)
        {
            return false;
        }
    }
    return true;
}

bool R1_Valid(vector<char> v, int n)
{
    return IsPermutation(v, n);
}

bool R2_Valid(vector<char> v, int n)
{
    if (IsPermutation(v, n) &&
        v[0] != 'a' &&
        v[1] != 'b')
    {
        return true;
    }
    return false;
}

bool Good(vector<char> v, int n)
{
    return n == v.size() - 1;
}

void R1(vector<char> x, int curLevel, int& outputCounter)
{
    //FVGB
    const char endLett = 'a' + char(x.size());
    for (char lett = 'a'; lett < endLett; lett++)
    {
        x[curLevel] = lett;
        if (R1_Valid(x, curLevel))
        {
            if (Good(x, curLevel))
            {
                printVect(x);
                cout << endl;
                outputCounter++;
            }
            else
            {
                R1(x, curLevel + 1, outputCounter);
            }
        }
    }
}

int fact(int n)
{
    if (n <= 2)
    {
        if (n == 0)
        {
            return 1;
        }
        return n;
    }
    return n * fact(n - 1);
}

int Combinari(int n, int k)
{
    int p = 1;
    for (int i = n; i >= n - k + 1; i--)
    {
        p *= i;
    }
    return p / fact(k);
}

int R2_AllDisjunct(int n, int nC)
{
    //This is used only when all condition are disjunct
    //What I want to believe is that this way, to output the direct answer, is faster than just using the general function to count
    //This function has to add up 2^nC  -1 terms, so I guess it's good? I don't even know if it's better or worse actually :(
    int sigma = 0;

    for (int k = 1; k <= nC; k++)
    {
        sigma += fact((n - k)) * Combinari(nC, k) * (k % 2 == 0 ? -1 : 1);
    }

    return fact(n) - sigma;
}

void R2(vector<char> x, int curLevel, int& outputCounter)
{
    //Optimization
    if (there is a column/line full of conditions)
    {
        outputCounter = 0;
    }
    else if (all conditions are disjunts)
    {
        outputCounter = R2_AllDisjunct(x.size(), nConditions);
    }
    else
    {
        //The sum has 2^nC   - 1 terms
        //The other problem is checking intersections between conditions
        //A good way to do this fast is memorize all the conditoins and make a graph with it, and the intersections are interpretet as edges
    }
}

int main()
{
    //Reading and initializing
    int nElements = 0;
    int nGenerated = 0;
    cin >> nElements;
    assert(0 < nElements && nElements <= 26); // to be a letter in the alphabet

    //Code
    cout << endl;

    const auto s1 = chrono::steady_clock().now();
    R2(vector<char>(nElements, 0), 0, nGenerated);
    const auto e1 = chrono::steady_clock().now();
    const auto dur1 = chrono::duration_cast<chrono::duration<double>>(e1- s1).count();

    cout << "\n\n" << "Generated_Counting: " << nGenerated << endl;

    const auto s2 = chrono::steady_clock().now();
    R2_AllDisjunct(vector<char>(nElements, 0), 0, nGenerated);
    const auto e2 = chrono::steady_clock().now();
    const auto dur2 = chrono::duration_cast<chrono::duration<double>>(e2 - s2).count();

    cout << "\n\n" << "Generated_Negated: " << nGenerated << endl;

    cout << endl << endl << "Slow: " << dur1 << endl << "Negated: " << dur2;

    cin.get();
    cin.get();
    return 0;
}