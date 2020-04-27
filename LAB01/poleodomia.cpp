#include <iostream>
#include <stack>
#include <utility>
//#include <fstream>

using namespace std;

long long A[1000000], RunSumPr[1000000], RunSumGr[1000000];
int Pr[1000000], Gr[1000000];

void findPrevGreaterElem(long long arr[], int n, int tempArr[]) /* first element of tempArr always 0 */
{
    stack<pair<long long, int>> myStack;
    pair<long long, int> tempPair;
    tempPair.first = arr[0];
    tempPair.second = 0;
    myStack.push(tempPair);
    for (int i = 0; i < n; i++)
    {
        while (myStack.empty() == false && myStack.top().first <= arr[i])
        {
            myStack.pop();
        }
        if (myStack.empty())
        {
            tempArr[i] = i;
        }
        else
        {
            tempArr[i] = myStack.top().second;
        }
        tempPair.first = arr[i];
        tempPair.second = i;
        myStack.push(tempPair);
    }
    return;
}

void findNextGreaterElem(long long arr[], int n, int tempArr[]) /*last element of tempArr always 0 */
{ 
    stack<pair<long long, int>> myStack;
    pair<long long, int> tempPair;
    tempPair.first = arr[n - 1];
    tempPair.second = n - 1;
    myStack.push(tempPair);
    for (int i = n - 1; i > -1; i--)
    {
        while (myStack.empty() == false && myStack.top().first <= arr[i])
        {
            myStack.pop();
        }
        if (myStack.empty())
        {
            tempArr[i] = i;
        }
        else
        {
            tempArr[i] = myStack.top().second;
        }
        tempPair.first = arr[i];
        tempPair.second = i;
        myStack.push(tempPair);
    }
    return;
}

void kindOfRunningSumForPrev(long long arr[], int Pr[], int n, long long tempArr[])
{
    tempArr[0] = arr[0];
    long long temp_res = 0;
    int prev_i = 0;
    for (int i = 1; i < n; i++)
    {
        prev_i = Pr[i];
        if (prev_i == i)
        {
            temp_res = (i + 1) * arr[i];
        }
        else
        {
            if (arr[i] < arr[i - 1])
            {
                temp_res = tempArr[i - 1] + arr[i];
            }
            else
            {
                temp_res = (i - prev_i) * arr[i] + tempArr[prev_i];
            }
        }
        tempArr[i] = temp_res;
    }
    return;
}

void kindOfRunningSumForNext(long long arr[], int Gr[], int n, long long tempArr[])
{
    tempArr[n-1] = arr[n-1];
    long long temp_res = 0;
    int next_i = 0;
    for (int i = n-2; i > -1; i--)
    {
        next_i = Gr[i];
        if (next_i == i)
        {
            temp_res = (n-i) * arr[i];
        }
        else
        {
            if (arr[i] < arr[i + 1])
            {
                temp_res = tempArr[i+1] + arr[i];
            }
            else
            {
                temp_res = (next_i - i) * arr[i] + tempArr[Gr[i]];
            }
        }
        tempArr[i] = temp_res;
    }
    return;
}

long long solver(long long RunSumPr[], long long RunSumGr[], long long arr[], int n)
{
    long long min = RunSumGr[0] + RunSumPr[0] - arr[0];
    long long temp = 0;
    for (int i = 1; i < n; i++)
    {
        temp = RunSumGr[i] + RunSumPr[i] - arr[i];
        if (temp < min)
        {
            min = temp;
        }
    }
    return min;
}

int main(/*int argc, char *argv[]*/)
{
    int n;
    /*ifstream input;
    input.open(argv[1]);
    input >> n;*/
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
        //input >> A[i];
    }
    //input.close();
    for (int i = 0; i < n; i++)
    {
        Pr[i] = 0;
        Gr[i] = 0;
        RunSumPr[i] = 0;
        RunSumGr[i] = 0;
    }
    findPrevGreaterElem(A, n, Pr);
    findNextGreaterElem(A, n, Gr);
    kindOfRunningSumForPrev(A, Pr, n, RunSumPr);
    kindOfRunningSumForNext(A, Gr, n, RunSumGr);
    long long res = solver(RunSumPr, RunSumGr, A, n);
    cout << res << endl;
    return 0;
}
