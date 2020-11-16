## How to build apps
```
$ Log to Ubuntu server
$ sudo git clone https://github.com/jacekdzija/cpp_linux.git 
$ cd cpp_linux
$ sudo chmod +x install.sh
$ sudo ./install.sh
$ cd out
```
#$ How to run
```
$ sudo ./Program1 cmd.txt
or 
$ sudo ./Program1
```
## supported cmd
* cmd format = <CMD_NAME><SPACE><Number1><SPACE><NumberN>
* cmd format = RENDER<SPACE><ImageName.bmp>
* cmd format = NEWIMAGE
* cmd format = EXIT

## example cmds 
* SET_WIDTH W
* SET_HEIGHT H
* DRAW_RECTANGLE X,Y,W,H
* DRAW_TRIANGLE X1,Y1,X2,Y2,X3,Y3
* RENDER NAME
* NEWIMAGE
* EXIT
