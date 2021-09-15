int search(int* nums, int numsSize, int target)
{
    int mid, left = 0, right = numsSize - 1;
    if (numsSize <= 0) return -1;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > nums[left])
        {
            if (target > nums[mid] || target <= nums[left]) left = mid + 1;
            else right = mid - 1;
        }
        else
        {
            if (target > nums[mid] && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }

    return -1;
}

int search(int* nums, int numsSize, int target)
{
    int mid, left = 0, right = numsSize - 1;
    if (numsSize <= 0) return -1;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] > nums[left])
        {
            if (target > nums[mid] || target <= nums[left]) left = mid + 1;
            else right = mid - 1;
        }
        else
        {
            if (target > nums[mid] && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }

    return -1;
}

int search(int* nums, int numsSize, int target)
{
    int mid, left = 0, right = numsSize - 1;
    if (numsSize <= 0) return -1;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] >= nums[left])
        {
            if (target >= nums[left] && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        else
        {
            if (target > nums[mid] && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }

    return -1;
}//ֻ������������� 
