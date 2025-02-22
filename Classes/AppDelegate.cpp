#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

#include "AppsFlyer/AppsFlyerX.h"
#include "../cocos2d/cocos/platform/CCPlatformMacros.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
    
    
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

static void onConversionDataReceived(cocos2d::ValueMap installData) {
    CCLOG("%s", "AppDelegate.cpp got conversion data!");

    for (auto &t : installData){
        CCLOG("%s - %s", t.first.c_str(), t.second.asString().c_str());
    }
}

static void onConversionDataRequestFailure(cocos2d::ValueMap map) {
    for (auto &t : map){
        CCLOG("%s - %s", t.first.c_str(), t.second.asString().c_str());
    }
}

static void onAppOpenAttribution(cocos2d::ValueMap map) {
    for (auto &t : map){
        CCLOG("%s - %s", t.first.c_str(), t.second.asString().c_str());
    }
}

static void onAppOpenAttributionFailure(cocos2d::ValueMap map) {
    for (auto &t : map){
        CCLOG("%s - %s", t.first.c_str(), t.second.asString().c_str());
    }
}

bool AppDelegate::applicationDidFinishLaunching() {

    AppsFlyerX::stopTracking(false);

    AppsFlyerX::setIsDebug(true);
    //AppsFlyerX::setMinTimeBetweenSessions(9);
    AppsFlyerX::setAppsFlyerDevKey("H9xZweqPFhzBEtiDh2vDj");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AppsFlyerX::setAppleAppID("942960987");
#endif

    AppsFlyerX::setOnConversionDataReceived(onConversionDataReceived);
    AppsFlyerX::setOnConversionDataRequestFailure(onConversionDataRequestFailure);
    AppsFlyerX::setOnAppOpenAttribution(onAppOpenAttribution);
    AppsFlyerX::setOnAppOpenAttributionFailure(onAppOpenAttributionFailure);

    AppsFlyerX::trackEvent(AFEventPurchase, {{ "key1", cocos2d::Value("value1")},
                                             { "key2", cocos2d::Value("value2")}});
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AppsFlyerX::trackAppLaunch();
#endif

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("AppsFlyerCocos2dX", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("AppsFlyerCocos2dX");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    AppsFlyerX::didEnterBackground();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    //CCLOG("%s", "~+~+~+~+~   applicationWillEnterForeground ~+~+~+~+~");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AppsFlyerX::trackAppLaunch();
#endif

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
