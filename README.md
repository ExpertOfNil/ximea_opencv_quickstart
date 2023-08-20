# Ximea and OpenCV Quickstart

This repository is meant to aid in getting up and running with computer vision
projects using Ximea cameras and OpenCV.

## Prerequisites

```bash
sudo apt update
sudo apt install build-essential linux-headers-"$(uname -r)"
```

## Install OpenCV

Unless you need a custom build of OpenCV, you can install it via:

```bash
sudo apt install libopencv-dev
```

## Install the Ximea API

Download the XIMEA Linux Software Package:

```bash
wget https://www.ximea.com/downloads/recent/XIMEA_Linux_SP.tgz
```

Untar:

```bash
tar xzf XIMEA_Linux_SP.tgz
cd package
```

Start install script:

```bash
./install
```

_Note_: For PCIe cameras, start the script with option `-pcie`

xiAPI will be compiled into `/usr/lib/libm3api.so`.  Examples, including
`xiApiPlusOcv` sources can be found in `/opt/XIMEA`.

_Note_: Linux has a really small (16MB) usb buffer limit by default.  This may
cause crashes during camera use.

Increase the USB Buffer Size in Linux:

```bash
sudo tee /sys/module/usbcore/parameters/usbfs_memory_mb >/dev/null <<<0
```

Alternatively, you can change it using `xiApi`:

Change the buffer commit count to 32:

```cpp
xiSetParamInt(handle, XI_PRM_ACQ_TRANSPORT_BUFFER_COMMIT, 32);
```

Change the buffer size to the maximum:

```cpp
xiGetParamInt(handle, XI_PRM_ACQ_TRANSPORT_BUFFER_SIZE XI_PRM_INFO_MAX, &buffer_size);
xiSetParamInt(handle, XI_PRM_ACQ_TRANSPORT_BUFFER_SIZE, buffer_size);
```

## Build and Compile

_Note_: This was created for the monochrome xiC cameras.  If a color camera is
being used, some adjustments will need to be made.

From the root directory:

```bash
mkdir build
cd build
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make
```

Executables are placed in the `bin` folder.
