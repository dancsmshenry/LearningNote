bool judgeCircle(char * moves)
{
    int i, h = 0, s = 0, n = strlen(moves);
    
    for (i = 0; i < n; i++)
    {
        if (moves[i] == 'U') h++;
        else if (moves[i] == 'D') h--;
        else if (moves[i] == 'L') s++;
        else if (moves[i] == 'R') s--;
    }

    if (h == 0 && s == 0) return true;
    else return false;
}
