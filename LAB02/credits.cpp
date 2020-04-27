#include <iostream>

using namespace std;
int A[500000];
int a[500000];
int b[500000];
int endWise[500000];
int startWise[500000];
int arm[500000];
int brm[500000];

int ceilElementEndWise(int a[], int start, int end, int key)
{
    while (end - start > 1)
    {
        int mid = start + (end - start) / 2;
        if (A[a[mid]] >= key)
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    return end;
}

int ceilElementStartWise(int a[], int start, int end, int key)
{
    while (end - start > 1)
    {
        int mid = start + (end - start) / 2;
        if (A[a[mid]] <= key)
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    return end;
}

void longestIncreasingSubsequenceEndWise(int input[], int start, int end)
{
    int len = 1;

    a[0] = start;
    endWise[0] = 1;

    for (int i = start + 1; i < end; i++)
    {
        if (input[i] <= input[a[start]])
        {
            a[start] = i;
            endWise[i] = 1;
        }
        else if (input[i] > input[a[len - 1]])
        {
            a[len++] = i;
            endWise[i] = len;
        }
        else
        {
            int pos = ceilElementEndWise(a, -1, len - 1, input[i]);
            endWise[i] = endWise[a[pos - 1]] + 1;
            a[pos] = i;
        }
    }
}

void longestIncreasingSubsequenceStartWise(int input[], int start, int end)
{
    int len = 1;

    b[0] = end - 1;
    startWise[end - 1] = 1;

    for (int i = end - 2; i > start - 1; i--)
    {
        if (input[i] >= input[b[start]])
        {
            b[start] = i;
            startWise[i] = 1;
        }
        else if (input[i] < input[b[len - 1]])
        {
            b[len++] = i;
            startWise[i] = len;
        }
        else
        {
            int pos = ceilElementStartWise(b, -1, len - 1, input[i]);
            startWise[i] = startWise[b[pos - 1]] + 1;
            b[pos] = i;
        }
    }
}

int solver(int arr[], int N)
{
    longestIncreasingSubsequenceEndWise(arr, 0, N);
    longestIncreasingSubsequenceStartWise(arr, 0, N);
    
    int max_val = 0;
    
    arm[0] = endWise[0];
    max_val = arm[0];
    for (int i = 1; i < N; i++)
    {
        if (endWise[i] > max_val)
            max_val = endWise[i];
        arm[i] = max_val;
    }

    brm[N - 1] = startWise[N-1];
    max_val = brm[N - 1];
    for (int i = N - 2; i >= 0; i--)
    {
        if (startWise[i] > max_val)
            max_val = startWise[i];
        brm[i] = max_val;
    }
    
    max_val = brm[N - 1];
    int temp;
    for (int i = 0; i < N - 1; i++)
    {
        temp = arm[i] + brm[i + 1];
        if (temp > max_val)
            max_val = temp;
    }
    return max_val;
}

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int res = solver(A, N);
    cout << res << endl;
    return 0;
}
