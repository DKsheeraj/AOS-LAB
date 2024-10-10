# Custom Embedded Linux for Raspberry Pi 
## Download the latest stable Buildroot tarball from the official Buildroot website.
```bash
tar -xvf buildroot-<version>.tar.gz
cd buildroot-<version>
```
##  Configure Buildroot for Raspberry Pi 3
```bash
make  raspberrypi4_64_defconfig
```
## Configure Buildroot
```bash
make menuconfig
```
1. Display names in system banner
   ```bash
   System configuration --->
     System banner
   ```
2. Enabling nano text editor
   ```bash
   Target Packages --->
     Text editors and viewers --->
       nano
3. Set root password
   ```bash
   System configuration --->
     Root password
   ```
4. Enabling SSH server capabilities
   ```bash
   Target Packages --->
     Networking Applications --->
       openssh
   ```
5. Enabling network utilities by selecting Net-tools
   ```bash
   Target Packages --->
     Networking Applications --->
       net-tools
   ```
6. Save and Exit
   
