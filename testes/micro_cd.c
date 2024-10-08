#include <stdio.h> // printf
#include <unistd.h> // getcwd() chdir()
#include <stdlib.h> // malloc free

//printar o pwd atual
//todo printar o oldpwd atual
//mudar o pwd 
//todo mudar o oldpwd 
//printar o novo pwd
//todo printar o novo oldpwd
int main()
{
    char *pwd = getcwd(NULL, 0);
    if (!pwd) //getpwd failed
        return -1;
    
    printf("PWD=%s\n", pwd);

    if (chdir("..") != 0)
    {
        free(pwd);
        return -2;
    }

    free(pwd); // get rid of the old
    pwd = getcwd(NULL, 0); // get the new
    if (!pwd)
        return -3;

    printf("PWD=%s\n", pwd);

    free(pwd);
    return 0;
}