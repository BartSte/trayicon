# README

This readme describes how to create a tray icon for kmonad on Windows.

[demo]()

## Installation

Copy the files in this directory to any folder on your computer. This should be
the following files: `kmonad.ico`, `start.vbs`, and `config.kbd`. Next, download
standalone executables of `trayicon` and `kmonad` from the following sources:

- [trayicon](https://github.com/BartSte/trayicon/releases/latest)
- [kmonad](https://github.com/kmonad/kmonad/releases/latest)

Place both executables in the same folder as the other files.

## Configuration

Open the `start.vbs` file in a text editor and follow the instructions in the
file to configure how trayicon is executed. The `config.kbd` file is an empty
kmonad configuration file that you can replace with your own.

## Run

Double-click the `start.vbs` file to start trayicon. This will start kmonad in
the background and display an icon in the system tray. Right-click the icon to
restart or quit kmonad.
