int minCostToMoveChips(int* position, int positionSize)
{
    int i, oushu = 0, jishu = 0;
    for (i = 0; i < positionSize; i++)
    {
        if (position[i] % 2 == 0) oushu++;
        else jishu++;
    }

    return oushu > jishu ? jishu : oushu;
}
