#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>
#include<time.h>
#include<grp.h>
#include<limits.h>
#include<pwd.h>

#define intl long long int 

#define LEN 1024
extern intl stdin_fd;
extern intl stdout_fd;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void pwd(intl n,char home_dir[]);

void printprompt(intl n,char home_dir[]);

void changedir(char arr[][LEN],char home_dir[],intl k);

void lskrle(char arr[][LEN],intl k,char home_dir[]);

intl execcmd(char arr[][LEN],intl k);

void pinfo(char arr[][LEN],intl k,char home_dir[]);

void chkbg();

intl exec_cmd();

intl solve_piping(char eachcmd[]);

intl solve_redir(char arr[]);

void jobsinf();

intl findpid(intl k);

void killjob(intl jn,intl sn);

void overkill();	

void remfromlist(intl pd1);
