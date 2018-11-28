# MyWorkspace 

## Installation
- Clone the repository
- Run `make` to generate the executable
- Run the program using `./MyWorkspace`

## Usage

### Opening Your Workspace
You may choose to create a new workspace, or load a workspace from the `preferences/workspaces.txt` preferences file.

### Desktop Syntax
Desktops are separated by the `||` delimiter, and consist of either 2 applications separated by the `|` delimiter (split left and right), or 1 application that will be made to fit the screen. Desktops may hold at most 2 applications and cannot mix Full-Screen applications with Split-Screen applications.

### Application Syntax
Applications are entered using the full name of the application as viewed in the `USER_HOME/Applications` folder. Applications can also be entered using their `alias`, if the alias exists in the `preferences/aliases.txt` preferences file. 

To make the application Full-Screen, surround it with the Full-Screen delimiters `<` and `>`, i.e: `<iTunes>`.

### Loading or Saving Your Workspace
Simple! Just follow the terminal instructions! 

### Sample Workspaces
- `Google Chrome | Visual Studio Code ||`
- `Notes | Maps || Safari || Stocks | Calendar || <iTunes> || <Mail>`

