# SmartOpen 

## Installation
// TODO:

## Usage

### Creating Your Workspace

##### Desktop Syntax
-

##### Application Syntax

### Saving Your Workspace 
// TODO: 

TODO:
- [ ] check if application is already open
- [ ] entity and value
- [ ] proper code citation
- [ ] sort imports alphabetically
- [ ] clean up code. comments
- [ ] open safari/chrome/firefox to specific url page
//TextEdit: make new document
//GoogleChrome: make new window

tell application "System Events"
	tell application process "Dock"
		tell list 1
			tell UI element "Visual Studio Code"
				perform action "AXShowMenu"
				tell menu "Visual Studio Code"
					tell menu item "New Window"
						perform action "AXPress"
					end tell
				end tell
			end tell
		end tell
	end tell
end tell