#include<stdio.h>
#include<unistd.h>
#include<pwd.h>
#include<stdlib.h>
#include<shadow.h>
#include<stdbool.h>
#include<string.h>
int main()
{
	char *uname,*pass,*encrypt;
	struct passwd *pwd;
	struct spwd *spw;
	bool authOK;
	long unameLEN;
	size_t len;
	unameLEN=sysconf(_SC_LOGIN_NAME_MAX);
	uname=malloc(unameLEN);
	printf("username :");
	fgets(uname,unameLEN,stdin);
	len=strlen(uname);
	if(uname[len-1]=='\n')
		uname[len-1]='\0';
	pwd=getpwnam(uname);
	if(pwd==NULL)
	{
		printf("couldn't find a reacord of user:%s\n",uname);
		exit(0);
	}
	spw=getspnam(pwd->pw_name);
	if(spw==NULL)
	{
		printf("no propper root permittion switch to root to see hash password\n");
		exit(0);
	}
	else
	{
		pwd->pw_passwd=spw->sp_pwdp;
		pass=getpass("password :");
		if(pass==NULL)
		{
			printf("you didn't enterd any password\n");
			exit(0);
		}
		encrypt=crypt(pass,pwd->pw_passwd);
		authOK=strcmp(encrypt,pwd->pw_passwd)==0;
		if(!authOK)
		{
			printf("wrong password\n");
			exit(0);
		}
		printf("+++++successfully authenticated++++++\n");
		exit(0);
	}
}

		



