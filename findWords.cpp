char** findWords(char** words, int wordsSize, int* returnSize) {
    if(wordsSize == 0) return NULL;
    
    int count = 0;
    int *num = (int *)malloc(wordsSize * sizeof(int) );
    
    const char *pattern = "(^[qwertyuiop]+$)|(^[asdfghjkl]+$)|(^[zxcvbnm]+$)";
    regex_t reg;
    int cflags = REG_EXTENDED|REG_ICASE;
    int nErrCode = 0;
    if ((nErrCode = regcomp(&reg, pattern, cflags)) == 0){
        const size_t nmatch = 1;
        regmatch_t pmatch[1];
        for(int i = 0; i < wordsSize; ++i){
            if ((nErrCode = regexec(&reg, *(words + i), nmatch, pmatch, 0)) == 0){
                *(num + count++) = i;      // save the index of current word for output
            }
        }
    }
    
    regfree(&reg);
    
    char **anspp = (char **)malloc(count*sizeof(char *));
    for(int i = 0 ; i< count; ++i){
        *(anspp + i) = (char *)malloc( strlen(*(words + *(num + i) ) ) * sizeof(char) );
        strcpy( *(anspp + i), *(words + *(num + i) ) );
    }
    
    free(num);
    
    *returnSize = count;
    return anspp;
}
