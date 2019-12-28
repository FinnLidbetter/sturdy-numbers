# sturdy-numbers
Command line interface for timing algorithms related to sums of digits of multiples of natural numbers.


## How to work with GitHub -- branching, making changes, pull requests, issues, etc.

Since there will be multiple people working on multiple files, a few guidelines
should help keep things running smoothly.

First, here is GitHub's description of this workflow model:
https://help.github.com/categories/collaborating-with-issues-and-pull-requests/
That has a lot of details, so here is a summary.

### GitHub setup

1. Clone the repository to where you want to work on it, e.g. your own
   computer. From the command line of your computer, enter something like
    ```
    git clone https://github.com/FinnLidbetter/sturdy-numbers
    ```

### Normal workflow

1. Make sure you are on your master branch, and it's up to date.
    ```
    git checkout master
    git pull
    ```

2. Create a new branch to contain all the changes in one "idea". Give the
   branch a descriptive name:
    ```
    git checkout -b add-bfs-algorithm
    ```
3. Make your changes, and test them. For all changed and new files, you will
   need to `git add` them (e.g. `git add new_or_changed_file.txt`). After
   you've made all changes and added all the files you want to commit, commit
   them (`git commit`) and describe your changes clearly but succinctly in the
   log.
4. Push your local branch to a branch on GitHub so you can create a pull
   request:
    ```
    git push --set-upstream origin username-factorialfun-initial-upload
    ```
   (If you have already issued this command for a branch, you can leave off
   everything after "push".)
5. Create a Pull Request (PR). Go to https://github.com/FinnLidbetter/sturdy-numbers,
   where you should see a big green button that says "Compare &amp; pull request"
   (for the branch you just pushed). Click that, and create the pull request.
6. After successful review, the PR should be merged (preferably by someone else
   who approves of it).  This causes your changes to be merged into the master
   branch.  Also, GitHub has a "Squash and Merge" option, which makes all the
   commits in the PR to appear as just one commit to `master`, making it look
   like just one set of changes.  After a merge to `master`, you (and everyone
   else) will want to sync your local repository with `master`:
   ```
   git checkout master
   git pull
   ```
   And then if you're working on a branch and you want that branch to also have
   the changes (so that it builds on top of current `master`, which makes it
   easier to ensure that your new branch can be merged into `master` later),
   you can/should use:
   ```
   git checkout your_branch
   git rebase master
   ```
   which will make it look like your work comes after, rather than in parallel
   to, the most recent changes to `master`. This makes `master` appear to be a
   linear set of changes, making it easier to understand.

7. If the review of the PR finds that changes are needed, you can add commits
   to the same branch used to create the PR, or edit them (usually paired with
   some use of `git rebase`, but that's a bit more advanced). The commits,
   after being pushed to GitHub, will appear as part of the PR automatically.

### When you find bugs/issues

1. Create an issue in GitHub (at https://github.com/FinnLidbetter/sturdy-numbers/issues).
   Try to be as clear as possible when describing it.
