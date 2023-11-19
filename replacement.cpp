#include <bits/stdc++.h>
#define ll long long
#define po push_back


using namespace std;

class pageReplacement
{
private:
    vector<ll> seq = {6, 1, 1, 2, 0, 3, 4, 6, 0, 2, 1, 2, 1, 2, 0, 3, 2, 1, 4, 0};

public:
    void fifo();
    void optimal();
    void lru();
};

void pageReplacement ::fifo()
{
    vector<vector<ll>> frame(4, vector<ll>(21, -1)); // 0-based indexing
    ll ptr = 0, hits = 0, miss = 0;
    string s = "";
    for (ll i = 0; i < 20; i++)
    {
        ll cur = seq[i], flg = 0;
        if (i > 0)
        {
            for (ll j = 0; j < 4; j++)
            {
                frame[j][i] = frame[j][i - 1];
            }
        }
        for (ll j = 0; j < 4; j++)
        {
            if (frame[j][i] == cur)
            {
                flg = 1;
                break;
            }
        }
        if (flg)
        {
            hits++;
            s += 'H';
            continue;
        }
        miss++;
        s += 'M';
        frame[ptr][i] = cur;
        ptr = (ptr + 1) % 4;
    }

    cout << "********* Frame state After FIFO processing **********\n\n";
    ll fcnt = 0;
    for (ll i = 0; i < 4; i++)
    {
        cout << "Frame" << fcnt << " -> ";
        fcnt++;
        for (ll j = 0; j < 20; j++)
        {
            (frame[i][j] < 0) ? cout << '$' << " | " : cout << frame[i][j] << " | ";
        }
        cout << '\n';
    }
    cout << "\nStatus -> ";
    for (auto it : s)
    {
        cout << it << " | ";
    }
    cout << '\n';
    cout << "\nTotal Hits -> " << hits << '\n';
    cout << "Total Miss -> " << miss << '\n';
    cout << "Hits Ratio -> " << ((hits * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";
    cout << "Miss Ratio -> " << ((miss * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";

    return;
}

void pageReplacement ::optimal()
{
    vector<vector<ll>> frame(3, vector<ll>(20, -1));
    ll hits = 0, miss = 0;
    string s = "";
    for (ll i = 0; i < 20; i++)
    {
        ll cur = seq[i], flg = 0;
        if (i > 0)
        {
            for (ll j = 0; j < 3; j++)
            {
                frame[j][i] = frame[j][i - 1];
            }
        }
        for (ll j = 0; j < 3; j++)
        {
            if (frame[j][i] == cur)
            {
                flg = 1;
                break;
            }
        }
        if (flg)
        {
            hits++;
            s += 'H';
        }
        else
        {
            miss++;
            s += 'M';
            multiset<ll> ds;
            for (ll j = 0; j < 3; j++)
            {
                ds.insert(frame[j][i]);
            }
            for (ll k = i; k < 20; k++)
            {
                if (ds.count(seq[k]))
                {
                    ds.erase(seq[k]);
                }
                if (ds.size() == 1)
                {
                    break;
                }
            }
            ll toreplace = *ds.begin(), ptrR = 0;
            for (ll ptr = 0; ptr < 3; ptr++)
            {
                if (frame[ptr][i] == toreplace)
                {
                    ptrR = ptr;
                    break;
                }
            }
            frame[ptrR][i] = seq[i];
            ds.clear();
        }
    }

    cout << "********* Frame state After OPTIMAL processing **********\n\n";
    ll fcnt = 0;
    for (ll i = 0; i < 3; i++)
    {
        cout << "Frame" << fcnt << " -> ";
        fcnt++;
        for (ll j = 0; j < 20; j++)
        {
            (frame[i][j] < 0) ? cout << '#' << " | " : cout << frame[i][j] << " | ";
        }
        cout << '\n';
    }
    cout << "\nStatus -> ";
    for (auto it : s)
    {
        cout << it << " | ";
    }
    cout << '\n';
    cout << "\nTotal Hits -> " << hits << '\n';
    cout << "Total Miss -> " << miss << '\n';
    cout << "Hits Ratio -> " << ((hits * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";
    cout << "Miss Ratio -> " << ((miss * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";

    return;
}

void pageReplacement ::lru()
{
    vector<vector<ll>> frame(4, vector<ll>(20, -1));
    ll hits = 0, miss = 0;
    string s = "";
    for (ll i = 0; i < 20; i++)
    {
        ll cur = seq[i], flg = 0;
        if (i > 0)
        {
            for (ll j = 0; j < 4; j++)
            {
                frame[j][i] = frame[j][i - 1];
            }
        }
        for (ll j = 0; j < 4; j++)
        {
            if (frame[j][i] == cur)
            {
                flg = 1;
                break;
            }
        }
        if (flg)
        {
            hits++;
            s += 'H';
        }
        else
        {
            miss++;
            s += 'M';
            multiset<ll> ds;
            for (ll j = 0; j < 4; j++)
            {
                ds.insert(frame[j][i]);
            }
            for (ll k = i; k >= 0; k--)
            {
                if (ds.count(seq[k]))
                {
                    ds.erase(seq[k]);
                }
                if (ds.size() == 1)
                {
                    break;
                }
            }
            ll toreplace = *ds.begin(), ptrR = 0;
            for (ll ptr = 0; ptr < 4; ptr++)
            {
                if (frame[ptr][i] == toreplace)
                {
                    ptrR = ptr;
                    break;
                }
            }
            frame[ptrR][i] = seq[i];
            ds.clear();
        }
    }

    cout << "********* Frame state After LRU processing **********\n\n";
    ll fcnt = 0;
    for (ll i = 0; i < 4; i++)
    {
        cout << "Frame" << fcnt << " -> ";
        fcnt++;
        for (ll j = 0; j < 20; j++)
        {
            (frame[i][j] < 0) ? cout << '#' << " | " : cout << frame[i][j] << " | ";
        }
        cout << '\n';
    }
    cout << "\nStatus -> ";
    for (auto it : s)
    {
        cout << it << " | ";
    }
    cout << '\n';
    cout << "\nTotal Hits -> " << hits << '\n';
    cout << "Total Miss -> " << miss << '\n';
    cout << "Hits Ratio -> " << ((hits * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";
    cout << "Miss Ratio -> " << ((miss * 1.0) / (1.0 * (hits + miss))) * 100.0 << "%\n";

    return;
}

int main()
{
    pageReplacement obj;
    obj.fifo();
    cout << "\n\n";
    obj.optimal();
    cout << "\n\n";
    obj.lru();
    return 0;
}

/*

********* Frame state After FIFO processing **********

Frame0 -> 6 | 6 | 6 | 6 | 6 | 3 | 3 | 3 | 3 | 3 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 
Frame1 -> $ | 1 | 1 | 1 | 1 | 1 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 4 | 0 | 0 | 0 | 0 | 0 | 0 | 
Frame2 -> $ | $ | $ | 2 | 2 | 2 | 2 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 3 | 3 | 3 | 3 | 3 | 
Frame3 -> $ | $ | $ | $ | 0 | 0 | 0 | 0 | 0 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 4 | 4 | 

Status -> M | M | H | M | M | M | M | M | H | M | M | H | H | H | M | M | H | H | M | H | 

Total Hits -> 8
Total Miss -> 12
Hits Ratio -> 40%
Miss Ratio -> 60%


********* Frame state After OPTIMAL processing **********

Frame0 -> 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 0 | 
Frame1 -> # | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 3 | 3 | 3 | 3 | 3 | 
Frame2 -> # | # | # | 2 | 2 | 3 | 4 | 4 | 4 | 4 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 4 | 4 | 

Status -> M | M | H | M | M | M | M | H | H | M | M | H | H | H | H | M | H | H | M | M | 

Total Hits -> 9
Total Miss -> 11
Hits Ratio -> 45%
Miss Ratio -> 55%


********* Frame state After LRU processing **********

Frame0 -> 6 | 6 | 6 | 6 | 6 | 3 | 3 | 3 | 3 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 
Frame1 -> # | 1 | 1 | 1 | 1 | 1 | 4 | 4 | 4 | 4 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 
Frame2 -> # | # | # | 2 | 2 | 2 | 2 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 6 | 3 | 3 | 3 | 3 | 0 | 
Frame3 -> # | # | # | # | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 4 | 4 | 

Status -> M | M | H | M | M | M | M | M | H | M | M | H | H | H | H | M | H | H | M | M | 

Total Hits -> 8
Total Miss -> 12
Hits Ratio -> 40%
Miss Ratio -> 60%

*/