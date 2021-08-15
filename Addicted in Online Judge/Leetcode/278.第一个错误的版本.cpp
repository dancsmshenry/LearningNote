// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) 
{
    int mid, left = 1, right = n;
    
    while (right - left > 0)
    {
        mid = left + (right- left) / 2;
        if (isBadVersion(mid) == true) right = mid;
        else left = mid + 1;
    }

    return left;
}
