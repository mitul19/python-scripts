double add(double x, double y)
{
    return x + y;
}

double add(double a, double b, double c)
{
    return a + b + c;
    // alternatively: return add(add(a,b),c);
}

bool test(bool x)
{
    return x;
}

bool test(double x)
{
    return x > 0;
}