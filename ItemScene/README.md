[![Build status](https://ci.appveyor.com/api/projects/status/o5tgk5n932v448vb?svg=true)](https://ci.appveyor.com/project/Wohlstand/itemscene)

# ItemScene
A small custom implementation of item scene to replace heavy and unoptimized QGraphicsScene in the PGE Editor

Target features in comparison with QGraphicsScene:
* Completely specific to PGE Editor's features set
* Fast feed-back and quick animation processing with no matter number of elements (QGraphicsScene lags if 20000~40000 elements are stored. New class doesnt lags while over 1000000 elements are placed on scene!)
* Correct processing of context menu without any bugs
* Ability to globally disable element dragging while placing / erasing  / drag-scrolling
* Accurate and quick camera positioing without any workarounds
* Support of multi-threading while building in-scene data (therefore possible to draw "loading" without spawning extra dialog boxes and without freezing entire application)
* Better processing zoom anchor (unlike QGraphicsScene, anchor by mouse will work when mouse is inside viewport, and will work from viewport center if mouse outsode (off-screen))

# Download
[Working demo for Win32 can be got here](http://wohlsoft.ru/docs/_laboratory/_Builds/win32/item-scene/item-scene-demo-win32.zip)

# Controlling
* Arrow keys (Scroll camera left-right-up-down)
* Ctrl+left mouse click - toggle selection of single element
* Shift+left mouse hold and move - additive rectangular selection (without dragging elements)
* Ctrl+Shift + left mouse hold and move - reversive rectangular selection
* Mouse wheel - scroll vertically
* Ctrl + Mouse wheel - scroll horizontally
* Alt + Mouse wheel - zoom in/out

# Building from sources
```bash
git clone https://github.com/WohlSoft/ItemScene.git
```
* This demo can be built on almost any platform supported by Qt (Linux, Windows, Mac OS X).
* You are required to have [latest Qt 5 package which you can take here](https://www.qt.io/download-open-source/)
Just open the ItemScene.pro in the Qt Creator and process the build.

