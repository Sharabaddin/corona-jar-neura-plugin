# TemplateProject

> --------------------- ------------------------------------------------------------------------------------------
> __Revision__          [REVISION_LABEL](REVISION_URL)
> __Keywords__          iOS, Android, tvOS, Windows, macOS
> __See also__          
> --------------------- ------------------------------------------------------------------------------------------

## Overview

You should start all new Corona projects by copying this project.

This project allows you to:

* develop cross-platform Corona Enterprise apps
* create plugins for Corona Enterprise

## Code Walkthrough

### iOS and tvOS

Both `ios` and `tvos` folders contain projects `Plugin` and `App`. `App` contains sample Corona Enterprise app with linked Corona Plugin inside `Plugin` project. Plugin is called `'plugin.library'`. `App` projects contain implementation of the `CoronaDelegate` protocol. In particular it has the method `willLoadMain:` which is your opportunity to modify the Lua state prior to execution of `main.lua`.

Hitting ▶ to run a the `App` project with Xcode would run project with Lua code inside `Corona` folder.

### macOS

Folders contain sample plugin for macOS Simulator and Desktop app. Note that plugin is a combination of compiled Lua and C++ code. To debug it, you can set up Executable: press "Edit Scheme" (`⌘<`), and select `Corona Simulator.app` from Applications folder.

* custom build phase would copy plugin so it can be tested in Corona Simulator
* custom build rule compiles Lua files in project so they can be used in C/C++

### Windows

Folders contain sample plugin for Windows Simulator and Desktop app. Note that plugin is a combination of compiled Lua and C++ code. Review project properties to change plugin name or location of Corona Simulator.
In order for Windows teplate to work, copy this folder (`App`) next to unpacked CoronaEnterprise folder. Folder structure should be like follows:

```
Projects\
├── CoronaEnterprise\
│   ├── Corona\
│   ├── ProjectTemplates\
│   ├── README.html
│   └── ...
└── MyApp\    <-- copy of CoronaEnterprise\ProjectTemplates\App
    ├── android
    ├── Corona
    ├── ...
    └── win32
        ├── Plugin.sln
        ├── Plugin.vcxproj
        └── ...
```

Open Plugin.sln and run it. This should build a sample plugin, copy it to Corona plugin folder and start Corona Simulator

### Android

* The Android "Application" class is overridden in this application so that a CoronaRuntimeListener can be set up before a Corona activity has been displayed.  This listener detects when a Corona runtime has been loaded, started, suspended, resumed, and exiting.  The listener's onLoaded() method is the application's opportunity to add its own custom Lua API to the Corona project.  See source file "CoronaApplication.java" on how to implement this.
* Lua functions are implemented in Java by using the "com.naef.jnlua.NamedJavaFunction" interface.  All source files ending with "*LuaFunction.java" in this sample project implement this interface.  They demonstrate how to use a LuaState object to perform fundamental operations such as fetching argument values, returning values, working with tables/arrays, and calling Lua functions from Java.
* Source file "AsyncCallLuaFunction.java" demonstrates how to safely call a Lua function from another thread.  This is important if you want to set up an asynchronous Lua function that accepts a Lua callback to be called from another thread once the asynchronous operation has ended.
* 3rd party libraries such as InMobi and inneractive have been excluded from this project.  This reduces the size of the resulting APK file.  Attempting to use these libraries from Lua will cause an exception to be thrown which will crash the application.
