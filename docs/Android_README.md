<img src="https://www.appsflyer.com/wp-content/uploads/2016/11/logo-1.svg"  width="200">

# Cocos2dX And​​roid集成指南


##  集成:

如何将AppsFlyer SDK集成到您的Cocos2d-x Android项目中。

### 1. 将SDK添加到您的项目

在本指南中，我们假设您使用Android Studio进行开发。

Take the files from the `AppsFlyer` [folder](/Classes/AppsFlyer) and add them to your Android project under `Classes` folder.

从“ AppsFlyer” [文件夹]（/ Classes / AppsFlyer）中获取文件，然后将其添加到“ Classes”文件夹下的Android项目中。

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

例如在`CMakeLists.txt`中：

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

我们更喜欢使用`gradle`-作为保持最新状态的最简单方法。请在您的gradle应用依赖项中添加以下几行：

```
implementation 'com.appsflyer:af-android-sdk:4.9.0@aar'
```

For Google Install Referrer, please, add also:

对于Google Install Referrer，请同时添加：

```
implementation 'com.android.installreferrer:installreferrer:1.0'
implementation 'com.android.support:appcompat-v7:28.0.0'
``` 

或者，使用最新的`appsflyer-SDK.jar`库并将其复制到项目的`libs`文件夹中。

### 4. 添加权限

在Package Explorer中，打开您的Android项目的`AndroidManifest.xml`文件。如果尚不存在，请为“ INTERNET”添加“ uses-permission”标签。

```xml
<uses-permission android:name="android.permission.INTERNET" />
```
