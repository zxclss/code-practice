// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
public:
    vector<int> specialSort(int N) {
        vector<int> res;
        for (int i = 1; i <= N; i ++ )
        {
            int l = 0, r = res.size();
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (compare(i, res[mid])) r = mid; else l = mid + 1;
            }
            res.push_back(i);
            for (int j = res.size() - 1; j > l; j -- ) swap(res[j - 1], res[j]);
        }
        return res;
    }
};