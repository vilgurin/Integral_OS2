# Integral_OS2
# OS/2 Warp 4.5 INSTALLATION
1. Download iso from the web-site here: https://winworldpc.com/product/os-2-warp-4/os-2-warp-452 (Choose the English version)<br/>
2. Start Virtual Box and configure the initial parameters accordingly to your needs<br/>
3. Go to Virtual Box settings -> storage -> insert the ISO to controller IDE<br/>
4. Start VM and follow the instruction on the screen (disk swapping)<br/>
5. After the installation begins, create new bootable volume<br/>
6. Make the volume installable<br/>
7.Proceed with the installationm choosing all the required options<br/>
8.After the full installation Os/2 will open the window "Install additional options". Do not ignore!<br/>
9. IMPORTANT!!! Install OS/2 toolkit. Without the toolkit you will not be able to use WATCOM IDE.<br/>

##COMPILER INSTALLATION
1. Download WATCOM compiler from the web-site https://www.os2site.com/sw/dev/openwatcom/index.html<br/>
2. Add the zip files to an iso<br/>
3. Insert an iso into the VM<br/>
4. Open iso with watcom FROM the Os/2<br/>
5. In order to do that go to Disk D->copy all the files you need to the local directory on OS/2<br/>
6. Install WATCOM <br/>
7. You are ready to use the compiler and IDE. Just go to WATCOM IDE-><br/>
->create new project->generate source->write code->compile source-> go to directory "WATCOM/binp"-><br/>
->link the object file -> run exe file

## COMPILATION
To compile and run the prgram we used:<br/>
wpp386 main.cpp -i=C:\WATCOM\h\;C:\WATCOM\h\os2 -w4 -e25 -zq -od -d2 -5r -bt=os2 -mf<br/>
wlink main.obj<br/>
main.exe
