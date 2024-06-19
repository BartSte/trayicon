# README

## Table of contents

<!--toc:start-->
- [Summary](#summary)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Troubleshooting](#troubleshooting)
<!--toc:end-->

## Summary

`trayicon` is a simple program that displays an icon in the system tray for a
given command. The icon can be used to restart or quit the command. It is also
possible to set a custom icon for the command.

## Installation

### Precompiled

You can install `trayicon` by downloading the precompiled binaries from the
[latest github release](https://github.com/BartSte/trayicon/releases/latest).
For windows, a standalone executable is provided. For linux, a tarball is
provided that contains an executable and required system libraries. A bash
script is used to start the program. MacOS is not supported at the moment.

### From source

Building from source is straightforward as the only dependency is `Qt6`. A
`setup` script is provided that installs Qt6 for you. You need to make sure that
you set an environment variable `QT_INSTALLER_JWT_TOKEN` with a valid token
as is explained in the [Qt documentation](https://doc.qt.io/qt-6/get-and-install-qt-cli.html).
The detailed steps are provided below. MacOS is not supported at the moment.

#### Linux

> The `setup` script only supports Arch Linux and Ubuntu 22.04. If you are
> using a different distribution, you need to install the dependencies
> yourself.

- Tested on Arch Linux and Ubuntu 22.04, with gcc 14 and clang 17.

- Run the `./scripts/setup` script to install Qt6. You can choose to install the
  `--static` Qt libraries (default) if you want to build a standalone
  executable, or the `--shared` libraries if you want use dynamic linking. The
  latter is faster, as it just downloads the libraries, instead of building
  them from source.

- Run the `./scripts/configure` script to configure the build.

- Run the `cmake --build build --target package` command to build the program
  and create a tarball with the executable and required libraries.

#### Windows

- Tested on Windows 11, with MSVC 2022.

- Run the `.\scripts\setup.ps1` script to install Qt6. You can choose to
  install the `--static` Qt libraries (default) if you want to build a
  standalone executable, or the `--shared` libraries if you want use dynamic
  linking. The latter is faster, as it just downloads the libraries, instead of
  building them from source.

- Run the `.\scripts\configure.ps1` script to configure the build.

- Run the `cmake --build build --config Release` command to build the program
  and create an executable.

## Usage

Run the `trayicon` program as follows:

```sh
trayicon [options] -- "command"
```

For example:

```sh
trayicon --icon /path/to/icon.png -- "my_command --option=value arg1"
```

This will start the `my_command --option=value arg1` command and display an
icon in the system tray.

For more information, run:

```sh
trayicon --help
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE)
file for details.

## Troubleshooting

If you encounter any issues, please report them on the issue tracker at:
[trayicon issues](https://github.com/BartSte/trayicon/issues)
