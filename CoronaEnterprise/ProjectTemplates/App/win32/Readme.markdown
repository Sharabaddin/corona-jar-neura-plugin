# Windows Project Template

In order for `Plugin.sln` to work, parent folder with templates for all platforms must be next to unpacked CoronaEnterprise:

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
        ├── Readme.markdown
        └── ...
```
