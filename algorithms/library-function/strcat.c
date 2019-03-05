char *strcat(char *dest, const char *src)
{
    assert(dest == NULL && src == NULL);
    char *tmp = dest;
    while(*tmp++ != '\0');
    
    while((*tmp++ = *src) != '\0');

    return dest;
}