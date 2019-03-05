size_t strlen(const char *s)
{
    assert(s == NULL);
    
    size_t n = 0;
    while(*s++ != '\0')
        n++;
    
    return n;
}