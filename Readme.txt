# XCode configuration

## add -fobjc-arc for IAPHelper and IAPShare

## add SystemConfigurate.framework
## change CSC_IOSHelper.cpp to CSC_IOSHelper.mm

## build openssl libs and add libcrypto.a & libssl.a to Linked Frameworks and Libraries of Xcode
## Maybe need to remove these two libs from cocos2d_libs in external/curl/prebuild


# use git subtree command to add this in the project

## git remote add -f CSCClass https://github.com/reallycsc/CSCClass.git

## git subtree add --prefix=Classes/CSCClass CSCClass master

## git fetch CSCClass master

## git subtree pull --prefix=Classes/CSCClass CSCClass master

## git subtree push --prefix=Classes/CSCClass CSCClass master