# README

WORK IN PROGRESS

## Description

Use the command line interface to:

- Set a command that runs your application.
- Set an icon for your application (optional).

Next, this program will display an icon in the system tray. You can use the icon
restart or quit the application.

## Installation

### From source

#### Windows

##### MinGW

- Use windeployqt add all libs etc.

## TODO:

- [ ] the program + args split is not working. Move to 1 command on the cli and
  pass it to QProcess::startCommand.
- [ ] windows pipeline fails. Maybee use ninja + msvc? Is this possible?
