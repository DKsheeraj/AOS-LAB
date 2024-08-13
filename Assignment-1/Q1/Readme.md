# Building New Kernel

### Step 1: Download the kernel source from the www.kernel.org

### Step 2: Extract the kernel source and in terminal navigate to the kernel source directory
```bash
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev 
make menuconfig
```

### Step 3: In the menuconfig, select the required configuration and save the configuration
Specifically turn off the IPV6 support in the kernel configuration by navigating to the following path in the menuconfig
```bash
Networking support  --->
    Networking options  --->
        <*> The IPv6 protocol
```

<!-- Make Kernel based Virtual Machine(KVM) an inbuilt feature instead of a kernel module. -->
To make KVM an inbuilt feature instead of a kernel module, navigate to the following path in the menuconfig
```bash
Virtualization  --->
    <*> Kernel-based Virtual Machine (KVM) support
```

### Step 4: Save the configuration as .config file and exit the menuconfig

### Step 5: Need to change some part of the .config file manually. The keys section in the .config file should be changed as follows
```bash
#
# Certificates for signature checking
#
CONFIG_MODULE_SIG_KEY="certs/signing_key.pem"
CONFIG_SYSTEM_TRUSTED_KEYRING=y
CONFIG_SYSTEM_TRUSTED_KEYS=""
CONFIG_SYSTEM_EXTRA_CERTIFICATE=y
CONFIG_SYSTEM_EXTRA_CERTIFICATE_SIZE=4096
CONFIG_SECONDARY_TRUSTED_KEYRING=y
CONFIG_SYSTEM_BLACKLIST_KEYRING=y
CONFIG_SYSTEM_BLACKLIST_HASH_LIST=""
CONFIG_SYSTEM_REVOCATION_LIST=y
CONFIG_SYSTEM_REVOCATION_KEYS=""
# end of Certificates for signature checking
```

Step 6: Some Installation of required packages
```bash
sudo apt-get install libelf-dev
sudo apt install dwarves
```

