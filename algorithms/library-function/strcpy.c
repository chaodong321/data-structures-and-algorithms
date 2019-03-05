char *strcpy(char *dest, const char *src)
{
    assert(dest == NULL && src == NULL);
    char *ret = dest;
    while((*dest++=*src++)!='\0');
    return ret;
}