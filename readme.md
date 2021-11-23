#Virtual shell:

-This is a C-program which on execution shows a shell like environment where we can execute basic commands like cd,ls,echo,pwd and many user-defined command pinfo,jobs,kjob,fg,bg,setenv,unsetenv etc.

-Also you can run a process foreground and background by just entering '&' at the end of your process if you want to execute in background.

-Also you can make a process running in foreground to go to background by pressing Ctrl+z and you can terminate it by pressing Ctrl+c.

-It also can take multiple commands at same time if they are separated by semi-colon.

-Here tilda ~ represents the directory where your executable file is stored.

-It can also handle piping and redirection separately and combined.

#Running the Shell:

-First cd into the directory where all the files are stored

-After that type 'make' in your terminal which will compile all the files and make an executable file for that named as 'shell'

-After that type 'make clean' to remove all .o(object files) which are created when we are compiling using make.

#Working:

-For executing 'shell' from where ever you are you just have to give relative path to the executable file.

-On execution You will first see a line which is somewhat similar to prompt of your terminal which has this type of structure:
<username@systemname:currentworkingdirectory>

-'ls','cd','echo','pinfo','pwd','history' commands ignores '&'

-ls will shows directory in green color and files in white color

-On executing 'cd' the current working directory in our prompt changes and the path to our current working direcory is relative to ~ if it resides anywhere in ~ otherwise is relative to root of your system.

Options for respective commands:

-cd,ls:  ~/path/to/any/direcory ./path/to/any/directory/ ../path/to/any/directory <Directory_	present_inside_our_cwd>

-ls:	any of the appropriate flags("-a","-l","-la","-al","-a -l")

-pinfo <pid> (optional)
	prints pid,Process Status,Memory,Executable path wrt ~ if possible
-history <num> (optional)
	it shows maximum 10 commands or if num is given than it will show last num commands executed.

-setenv var <value>:
	It will set the value if given to the var and make var the environment variable.

-unsetenv var:
	It will unset the environment variable var.

-jobs:
	It will show all the jobs that are created and right now they are not terminated, they are whether sleeping,stopped or running.

-kjob <jobnumber> <signalnumber>:
	It will send the specified signalnumber to the jobnumber specified.

-fg <jobnumber>:
	It will bring the job specified by jobnumber to foreground if that job exists.

-bg <jobnumber>:
	It will changed the status of a job stopped in background to running in background(sleeping).

-overkill:
	It will kill all the background processes.

-Ctrl+z:
	It will change the status of currently running job to stop and push it in background.

-Ctrl+c:
	It will terminate any foreground process running over our shell(it will not terminate our shell).

--Up arrow key:
	On pressing upper arrow key k times and pressing enter it will execute kth job that has been executed before this job.

	(k<=10)

-If you want to execute any process in the background say emacs than type 'emacs &' in the space provided than you will get a line saying 'emacs with pid xyz gets opened in the background'

-If any background process exited normally than on pressing entering whereever you are you will get a message saying that that process exited normally with pid xyz

-If any background process is closed by killing it than on pressing enter you will get a message saying that that process with pid xyz is killed by a signal

-If you want to run any process foreground than simply don't type & in the last, if you do this than prompt will not be printed unitl you don't close that process

-For exiting the shell you have to type quit and press enter

#Description of each File:

-functions.h:
	This file is included in all the files as it contains all the headers which are required and also all the function's prototype and some variable definition.
	It also contains some color coding which will be required in differentiating directories and files.

-run.c:
	It is the main file as it contains the main function and on entering each command it will call different functions which are in different files
	It also has a function named maketilda which will helps to store our home directory as we have to display our cwd in prompt relative to our home directory

-functions.c:
	This file contain function display which will help us in displaying the prompt in correct way.

-cd.c:
	This file contains the function changedir which will change your current working directory to your desired existing directory

-ls.c:
	This file contains the function lskrle which will shows you the content of your desired directory depending on the flags given

-pinfo.c:
	This file contains the function pinfo which will tell about our shell if you don't give any pid or will tell about that process of which pid you give

-fgbg.c:
	This file contains the function execcmd which will helps us in opening any process in foreground or background

-chkbg.c:
	This file contains the function chkbg which will check if there is any process in the background whose status got changed If any thing of this type happend it will print the message describing which process exits for that you have to press enter once.
	
-Makefile:
	This file helps in compiling all the .c files together so we don't have to write them again and again.We have to simply write make and this will compile them all.

-piping.c:
	This file contains the code which can break the command with respect to piping and send the remaining command to redir.c

-redir.c:
	This file contains the code which can break the command which comes from piping.c in simple commands which changes the our input and output mode from stdin,stdout respectively if they are required to change.

-findpid.c:
	This file contains the function which can return the pid of the given job number.

-jobs.c:
	This file contains the code which can handle jobs command which prints all the jobs that are running.

-kill.c:
	This file contains the code which if given the job number can kill the process.

#Warning:
	If you accidentally press tab and now you want to go back don't press backspace it will create mess.For this simply press enter and type whatever you want again.
