# 2FAster - Desktop (Windows)
Using 2FAster on Desktop (Windows)

### Building
1. [Build libcurl](https://medium.com/@chuy.max/compile-libcurl-on-windows-with-visual-studio-2017-x64-and-ssl-winssl-cff41ac7971d)
2. Move `/bin/libcurl.dll` to `/2FAster/2FAster`
3. Move `/lib/libcurl.lib` to `/2FAster/2FAster/lib`
4. Move `/include/` to `/2FAster/2FAster/include`
5. Use `Visual Studio` or [g++](http://www.mingw.org/) to build the project!
