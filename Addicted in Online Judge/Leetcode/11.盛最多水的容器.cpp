int maxArea(int* height, int heightSize)
{
    int i, j, min, max = 0;
    if (heightSize == 2) return height[0] > height[1] ? height[1] : height[0];

    for (i = 1; i < heightSize; i++)
    {
        for (j = 0; j < i; j++)
        {
            min = height[i] > height[j] ? height[j] : height[i];
            max = max > min * (i - j) ? max : min * (i - j);
        }
    }
    
    return max;
}
