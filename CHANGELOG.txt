# Changelog
## v1.4.3.1 (The first GitHub release)
19.04.2025
### Fixes
* Replaced `or`s with `||`.
* Updated Discord tag.

## v1.4.3.0
24.09.2022
### Changes
* Added --omit-prefix flag. See usage tip.
### Fixes
* Fixed 8 bit TGAs not having 8 bits of alpha in the header.
* Conversion from regular TGA to CIU now removes any unnecessary data, like the footer.


## v1.4.2.1
28.08.2022
### Fixes
* Fixed one byte loss when converting 24 bit TGAs (starfield6) (Introduced in 1.4).
* Fixed the last file always getting ignored.
* Fixed help screen trying to be shown when there's only one file in the files list, resulting in this file being ignored and app doing nothing.

## v1.4.2
27.08.2022
### Changes
* They.

## v1.4.1
27.08.2022
### Changes
* -f, --force [ciu|normal|auto] flags for forcing CIUed, un-CIUed TGAs conversion (if recognition fails).
* --folder [path] flag for overriding output folder. "--folder no" to undo.
### Fixes
* Pause is alive again. -k for pause (exe name arg is supported).
* No more "using namespace std;".
* Typos, rewrote the help.

## v1.4
24.08.2022
* Pause is dead.
* 24 bit TGAs (starfield6) no longer have 8 bits of alpha in the header when in fact there is no bits per pixel left (GIMP fix).
