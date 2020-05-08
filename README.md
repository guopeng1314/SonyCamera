# SonyCamera
Windows DLL Connecting to Sony Camera via USB

1st draft of README. For now, see https://retro.kiwi/

This DLL allows an application to connect to a compatible Sony DSLR/Mirrorless camera.
Individual camera settings (Properties) can be retrieved and updated.
Images can be taken and retrieved.

This software was developed primarily for Astrophotography purposes, and a companion project ASCOMSonyCameraDriver provides a basic ASCOM Driver.  https://github.com/dougforpres/ASCOMSonyCameraDriver

This is the first c++ code I've written since 2005/2006, so please don't judge me :)

See Wiki pages for package install info

## Dependencies
https://www.libraw.org
Being used to convert received ARW files to RGGB and RGB format

https://www.libjpeg-turbo.org/
Being used to convert received JPEG files to RGB format
