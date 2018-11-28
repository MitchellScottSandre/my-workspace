# MyWorkspace 

## Installation
- Works on macOS Mojave 10.14.1 and later
- Clone the repository
- Run `make` to generate the executable
- Run the program using `./MyWorkspace`

## Usage

### Opening Your Workspace
You may choose to create a new workspace, or load a workspace from the `preferences/workspaces.txt` preferences file.

### Desktop Syntax
Desktops are separated by the `||` delimiter, and consist of either 2 applications separated by the `|` delimiter (split left and right), or 1 application that will be made to fit the screen. Desktops may hold at most 2 applications and cannot mix Full-Screen applications with Split-Screen applications.

The last desktop doesn't need to end with the desktop delimiter.

### Application Syntax
Applications are entered using the full name of the application as viewed in the `USER_HOME/Applications` folder. Applications can also be entered using their `alias`, if the alias exists in the `preferences/aliases.txt` preferences file. 

To make the application Full-Screen, surround it with the Full-Screen delimiters `<` and `>`, i.e: `<iTunes>`.

### Loading or Saving Your Workspace
Simple! Just follow the terminal instructions! 

### Troubleshooting / More
- Want to make enter applications quicker? Add an alias to the `preferences/aliases.txt` preferences file using the syntax `ALIAS["ALIAS":"APPLICATION_NAME"]`. Yes, use quotes.
- Is an application not being positioned correctly? Check to see if its process name is different than its application name. If so, add it to the `preferences/processNames.txt` preferences file  using the syntax `PROCESS_NAME["APP_NAME":"PROCESS_NAME"]`. Yes, use quotes.
- Is a second (or third...) application window opening on a previous desktop? Check to see if new windows are opened using "New Window" or, perhaps, another phrase. If another phrase is used, add it to the `preferences/aliases.txt` preferences file using the syntax `OPEN_PHRASE["APPLICATION_NAME":"NEW_OPEN_PHERASE"]`

### Sample Workspaces
- `Google Chrome | Visual Studio Code`
- `Notes | Maps || Safari || Stocks | Calendar || <iTunes> || <Mail> ||`

