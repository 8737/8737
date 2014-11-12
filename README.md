## Installation and Account
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

