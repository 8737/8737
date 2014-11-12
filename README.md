## Installation and create account
1. Sign up an account on http://github.com
2. Go to https://help.github.com/articles/set-up-git/ and follow *Setting up Git*
  1. Download and install git
  2. On Windows, open **Git Shell** from your desktop; On Mac, open **Terminal** application
  3. On command line, type `git config —global user.name "Your name"`
  4. then type `git config --global user.email "The email you signed up on github.com"`
3. Tell Bennett your github user ID so he can add you to our team

## Access team software:
1. Open **Git Shell** for Windows, or **Terminal** for Mac
2. Go to your *FTC* folder. For example, if you have *C:\FTC* on Windows, type `cd C:\FTC`
3. Go to https://github.com/8737/8737 and click on the copy icon next to *HTTPS clone URL* so you don’t need to type the URL in the next step
4. Type `git clone https://github.com/8737/8737.git` to clone our master codes on your machine. Now you should see there is a *8737* folder under the *FTC* folder. We call *8737* a **repository**. You should run our robot with the codes in this folder.
6. Whenever you want to sync with our master codes, type `git pull` and you will have our latest master codes

**NOTE:** There are three copies of the master codes for you now:
* **Remote master** on github.com
* **Local master** on your machine (in a hidden folder under *8737*)
* **Working copy** of the master in *8737* folder that you can change - but *NOT RECOMMENDED*

## Create a code branch
Branches are used to develop new features (or fix bugs) isolated from each other. The master branch is the default branch when you create a repository. Create other branches to add or change codes without affecting master codes. We will merge branches back to the master branch after code review and testing.

1. Open **Git Shell** for Windows, or **Terminal** for Mac
2. Go to your local repository. For example, if you have *C:\FTC* on Windows, type `cd C:\FTC\8737`
3. Make sure you are in the master. Type `git status` and you should see *On branch master*
4. If not, type `git checkout master`
5. Create a branch off the master. Name this branch something meaningful and prefix with your name. For example, type `git checkout -b BennettAutoFromCenter` and now we just created a branch called *BennettAutoFromCenter* and switched to this branch

**NOTE:** You just added a *local BennettAutoFromCenter branch* which is actually a clone of master to start with. The *working copy* is now matching the branch. 

**NOTE:** The *working copy* is always in the *8737* folder. You may create many branches, but there is only one working folder. You switch between master and branches. The *8737* folder is always matching your current branch. To list all local branches, you can type
```
git branch
```
Your current branch has a star next to it.

## Add/Change/Commit codes:
You can modify code in any files and you can add files as needed just like how you normally work. Whenever you think it is a good time to take a snapshot of your code, you can perform the following steps. We call each snapshot a **commit**. In general, you want to commit your code changes whenever you fix a bug, add a small feature or make any meaningful progress. It is easier for other people to review code changes if a commit is short and has a clear purpose.

1. Open **Git Shell** for Windows, or **Terminal** for Mac
2. Go to your local repository. For example, if you have *C:\FTC* on Windows, type `cd C:\FTC\8737`
3. Type `git status` and you will see files that has been modified and also new (untracked) files
4. Type `git diff` and you will see what code has been added or removed for *existing files*. New files are not shown with this command.
5. To see the modification of one particular file, for example, *robotMain.c*, type `git diff robotMain.c`
6. It’s always a good idea to review the code yourself one more time to make sure all changes are what you want.
7. To include all modified and new files to the next commit, type `git add .`. The period represents current folder.
8. To add files individually, for example, *robotMain.c*, type `git add robotMain.c`
9. Type `git status` again and you will see file names in *green*, which indicates that code changes in these files will be committed. If you read any other tutorials, people say that these *green* files are **staged** for **commit**.
10: To commit the code changes, type `git commit -m “Cap the max motor value”`. The message between quotes should summarize your code changes. 
11. Rinse and repeat. Work on your next goal to complete a task, modify codes or add files. Repeat 1 - 10.
 

**NOTE:** Remember that before you *commit* your code changes, these changes are in your *working copy* only. It is not even saved in your *local branch*, let alone the *local master* or *remote master*. After the commit, your changes are now saved in your *local branch*.

**TIP:**  For some reason, you want to revert all your changes and start over from your previous commit, you can type `git checkout .`. All of your changes so far will be gone! Make sure you really want to do so.
