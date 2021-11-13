# Prototyping Arduino and AWS
This repositories intention is to get a depth sight into everything discoverd while playing around with Arduinos, other microcontrollers and IoT Cloud Systems.

> Have a look at the [Docs](https://ece-iot.github.io/Prototyping/)

## Structure 

The repository is structured into different development sections.

### [/code](code/)

Here every piece of code is situated. Every sub-directory represents an own [PlatformIO](https://platformio.org), Python for AWS, etc project. 

**PlatformIO**

If the sub-directory represents a PlatformIO project the structure should **always** be the following:

- sub-dir
  - .pio (auto-generated)
  - .vscode (partially auto-generated)
  - code 
  - data
  - scripts
  - secrets
  - platformio.ini

This structure ensures that the process of compilation with PlatformIO works properly.

### [/docs](docs/)

This folder contains the doc files for the **github pages** of this project. **It shall not** be modified by hand, because it will be auto-generated by a script

### [/scripts](scripts/)

Here all the essential scripts for setting up new projects within the repository or generating the docs are stored!

## Setup

In order to get everything running the first step after cloning the repository is to install all python modules

```shell
pip3 install -r requirements.txt
```

## Embedded development

### `C++` Development

The process of development takes place in the mentioned sub folder structure. Open the certain sub category in an own VSCode Window, this ensures that PlatformIO will detect the right `.ini` file 

### Usage of Authentication files

If there is the need of using SPIFFs on the `ESP32` all files need to be converted to **binary** format. In order to convert the `.pem`, `.key` or `.crt` files correctly the python script `generate-certs.py` can be utilized. 

Process of conversion:

1. create (if not already existing) the directory `/data` in your file-tree
2. add the device-key, the private-key and the rootCA file to the `/data` directory 
3. run the script with `generate-certs.py`
4. use PlatformIO to upload `/data` to the *ESP32*
