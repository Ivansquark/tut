# Commands

## ----------- config ---------------------------------------------------------
git config --global diff.tool vimdiff
git config --global difftool.prompt false
git config merge.conflictstyle diff3
git config --global mergetool.keepBackup false
## ----------- init -----------------------------------------------------------
git init --bare                                 # on server
git init                                        # on local
## ----------- main commands --------------------------------------------------
git status
git add -A
git commit -m "first"
git remote add origin /home/user/gitfolder
git remote add origin https://www.github.com/Ivansquark/repo
git remote add origin git.github.com:Ivansquark/repo
git push
git push --set-upstream origin master
git pull
git fetch                                       # if pull breaks => fetch, merge
git clone
git log
git log -- oneline
git diff

## ----------- Undo a commit & redo -------------------------------------------
$ git commit -m "Something terribly misguided" # (0: Your Accident)
$ git reset HEAD~                              # (1)
[ edit files as necessary ]                    # (2)
$ git add .                                    # (3)
$ git commit -c ORIG_HEAD                      # (4) + edit

### Revert to a previous commit by hash:
git-reset --hard <hash>
### Revert to previous commit:
git-reset --hard HEAD^

## ----------- branches -------------------------------------------------------
git branch
git branch --list
git branch -r                                   # remote
git branch -d <branch-name>                     # delete
git checkout <name-of-your-branch>
git checkout -b <name-of-your-branch>           # create new

git pull origin other-branch                    # another branch not in local

## ----------- compare --------------------------------------------------------
### To compare 2 revisions of a file
git diff <commit1> <commit2> <file_name>
### To compare current staged file against the repository:
git diff --staged <file_name>
### To compare current unstaged file against the repository:
git diff <file_name>


## ----------- merge conflict -------------------------------------------------
[Link](https://www.rosipov.com/blog/use-vimdiff-as-git-mergetool/)
git mergetool --tool=vimdiff
------------------------------------------
|   LOCAL     |   BASE    |   REMOTE     |
------------------------------------------
|                MERGED                  |
------------------------------------------
:resize [+-]N - resize a hor split, incr or decr height by N characters.
:vertical resize [+-]N - resize a vert split, incr or decr width by N 

] c and [ c to navigate to the next and previous diff respectively

use z o while on a fold to open it, if you want to see more context

:diffget RE

:diffg RE  " get from REMOTE
:diffg BA  " get from BASE
:diffg LO  " get from LOCAL

:wqa # with save

if you want to abort merging the current file and not mark it as resolved,
quit with :cquit 
git commit
