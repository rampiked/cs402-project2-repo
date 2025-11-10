# UIC CS 402 Fall 2025
Github repository for projects and any other code used/needed for the class. The assignments/other code in this repository are separated using git branches.

## How to use this repository
1. Fork or clone this repository. You will need to add this repository to your Github for version control and submission of projects. You have 2 options for this.
    - **Fork the repository.** While logged into Github, navigate to the repository and simply fork it to your own Github.
    - **Clone the repository.** Alternatively, you can clone this repository to your local machine, then create a new Github repository and add your local repository to the created Github repo.
2. Have the repository on your local machine. If you fork the repository, you simply need to clone the repo to your local machine. If you first cloned the repo then uploaded it to Github, you already have it on your local machine.
3. Fetch changes. Run the command `git fetch` to ensure you have all of the changes from this repository, including new branches.
4. Switch to the appropriate branch. This repository will separate projects, in-class code, etc., using git branches to keep things separate. Once you have cloned the repository, you can switch branches to the appropriate project/assignment/etc., and get started working. To see which branches are available, run the command `git branch -v -a`. Then, to swithc branches, run `git switch <branch_name>`, where `<branch_name>` is the name of the branch you want to switch to.

## Example Usage
Let us say you are going to work on `project-1`. Follow these steps.
1. Fork/clone the repository.
2. Clone the repository to your local machine.
3. Enter the cloned repository, then run the command `git fetch`.
3. In the repository, switch branches. Using the command line, this can be done by invoking the command `git branch -v a` to make sure `project-1` is a branch, then by running the command `git switch project-1`.
4. You can now track all of your changes to your `project-1` using this branch.
