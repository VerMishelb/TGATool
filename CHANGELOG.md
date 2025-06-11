# Changelog
## v1.4.4.1
00.00.2025
sha256: ``
* [*] Recognises the image flip bit again to make the output consistent across different apps (e.g. Krita which sets it to 1).
* [-] Added monochrome conversion option from UVE Preload splitter to eliminate the 2nd app if you only need to read the image. Though, you should use the splitter for most textures anyway because it's handy.

## v1.4.4.0
12.06.2025
sha256: `a9b5b4066906d70f419871cd5b3b2e52baade319a01a47313409a71a544eab5b`
* Moved to C++23 (previously used C++17) and std::print, which is the only way to successfully print UTF-8 text to the Windows 7 command prompt.
* Added clang-format.
#### Changes
* Sane UTF-8 support for Windows command prompt. Please report weird or incorrect behaviour, especially on older systems.
* Reworked pauses.
    * -k flag is no longer accepted for exe name arguments, use --keep instead. -k still works as a regular argument if you run TGATool via a shortcut.
    * New pause default behaviour (flag --keep-on-error): the window automatically closes on success and remains if there were errors.
    * New flag --no-keep which removes the pauses completely. Can be used for calling TGATool from other apps.
#### Fixes
* Fixed RLE check not being treated as an error.

## v1.4.3.1
19.04.2025
sha256: `433f699ff92968f3c0366707ae86ab74d7306f4cc526b4b13e3d0426990cfc53`
* The first GitHub release. Functionally identical to 1.4.3.0.
* Project was moved to CMake instead of the VS solution.
#### Fixes
* Replaced `or`s with `||`.
* Updated Discord tag.
* Corrected credits.

## v1.4.3.0
24.09.2022
sha256: `0765ccb32d2ceb57829b2261c62e09b4083bb61768b370d13c6a1070f7c02f7e`
#### Changes
* Added --omit-prefix flag. See usage tip.
#### Fixes
* Fixed 8 bit TGAs not having 8 bits of alpha in the header.
* Conversion from regular TGA to CIU now removes any unnecessary data, like the footer.

## v1.4.2.1
28.08.2022
sha256: `83a4843c9fa231b9b21315a4bb4c3c65613302e0ae443bffbc2b4a91f382b57b`
#### Fixes
* Fixed one byte loss when converting 24 bit TGAs (starfield6) (Introduced in 1.4).
* Fixed the last file always getting ignored.
* Fixed help screen trying to be shown when there's only one file in the files list, resulting in this file being ignored and app doing nothing.

## v1.4.2
27.08.2022
sha256: `e862d63649a1da3f2bc7c1d6c320e96ec97074ba274a0965a10dcfac8d1293a6`
#### Changes
* Minor credits changes.

## v1.4.1
27.08.2022
sha256: `ac418d438f234ce1937ab366a2c53f56d0d86710b53e7d2deaea9621fb16828e`
#### Changes
* -f, --force <ciu | normal | auto> flags for forcing CIUed, un-CIUed TGAs conversion (if recognition fails).
* --folder <path> flag for overriding output folder. "--folder no" to undo.
#### Fixes
* Pause is alive again. -k for pause (exe name arg is supported).
* No more "using namespace std;".
* Typos, rewrote the help.

## v1.4
24.08.2022
sha256: `d1c358f26d2fa03c0408b3585fb6a89f24361e5ed9d072a551649271eb0f9eb8`
* Pause is dead.
* 24 bit TGAs (starfield6) no longer have 8 bits of alpha in the header when in fact there is no bits per pixel left (GIMP fix).

## v1.3
06.06.2021
sha256: `839f0b5ae5bbcfe67e79ae6338097752a4cc4ce8cf395463c86f3ecebd8d2477`
Change log lost to time.

## v1.2
22.10.2020
sha256: `456105ebe4a6881baa8e7db11d1beea1ef3e0cee65270115be66c27b3b5a81c4`
* Fixed mode detection (`mode` to `colours` typo). It no longer throws "bad colour depth" error on 24 bit TGAs.

## v1.1
20.07.2020
sha256: `8394374a2620188283b79f3b96edc070524dcb4cbeffd928eae7ba35e6df536a`
* Rewrote new name definition a bit, so "bubble.tga" now turns to "bubble_f.tga" or "bubble_c.tga" instead of "bubble.tga_f.tga"
* Added displaying of new file path.

## v1.0
03.07.2020
sha256: `dada4d33b8e6ac73462114ba0f24c12f8e8eb0669a8150067a1db220c2db351f`
* Initial release.