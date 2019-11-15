<img src="https://www.appsflyer.com/wp-content/uploads/2016/11/logo-1.svg"  width="200">

# Cocos2dX And​​roid集成指南


##  Integration:
How to integrate the AppsFlyer SDK into your Cocos2d-x Android project.

如何将AppsFlyer SDK集成到您的Cocos2d-x Android项目中。

### 1. 将SDK添加到您的项目

Throughout this guide, we assume that you are using `Android Studio` for development.

Take the files from the `AppsFlyer` [folder](/Classes/AppsFlyer) and add them to your Android project under `Classes` folder.

![add-to-android-mk](https://github.com/AppsFlyerSDK/AppsFlyerCocos2dX/blob/development/Resources/add-android-files.png?raw=true)

### 2.  添加C ++源文件定义
Add the paths of the AppsFlyer C++ files to the `LOCAL_SRC_FILES` section in your `Android.mk` file if you use `PROP_BUILD_TYPE=ndk-build`
```mk
../../../Classes/AppsFlyer/AppsFlyerXAndroid.cpp \
../../../Classes/AppsFlyer/AppsFlyerProxyX.cpp \
../../../Classes/AppsFlyer/AppsFlyerX.cpp
```

![add-android-files](https://github.com/AppsFlyerSDK/AppsFlyerCocos2dX/blob/development/Resources/add-to-android-mk.png?raw=true)

For `cmake` a.e. `PROP_BUILD_TYPE=cmake` use:

For example in `CMakeLists.txt`:

```mk
# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppsFlyer/AppsFlyerX.cpp
     Classes/AppsFlyer/AppsFlyerXAndroid.cpp
     Classes/AppsFlyer/AppsFlyerProxyX.cpp
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppsFlyer/AppsFlyerX.h
     Classes/AppsFlyer/AppsFlyerXAndroid.h
     Classes/AppsFlyer/AppsFlyerProxyX.h
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
     )
```

![add-android-files](https://github.com/AppsFlyerSDK/AppsFlyerCocos2dX/blob/development/Resources/add-to-android-cmake.png?raw=true)



### 3. 将AppsFlyer库添加到您的项目
We prefer to use `gradle` - as the easiest way to stay up to date. Please add the following lines to your gradle app dependencies:

```
implementation 'com.appsflyer:af-android-sdk:4.9.0@aar'
```

For Google Install Referrer, please, add also:

```
implementation 'com.android.installreferrer:installreferrer:1.0'
implementation 'com.android.support:appcompat-v7:28.0.0'
``` 


As alternative way, take the latest `appsflyer-SDK.jar` library and copy it to your project's `libs` folder.

### 4. 添加权限

In the Package Explorer, open the `AndroidManifest.xml` file of your Android project. Add the `uses-permission` tag for `INTERNET` if it's not already present.

```xml
<uses-permission android:name="android.permission.INTERNET" />
```
