#pragma once
#include "CommonDefinition.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "IOSHelper/GameKitHelper.h"
#import "IOSHelper/IAPShare.h"
#import "IOSHelper/Reachability.h"
#import "IOSHelper/ProgressHUD.h"
#endif

NS_CSC_BEGIN
class CSC_IOSHelper : public Node
{
public:
	CSC_IOSHelper();
	// singlar
	static CSC_IOSHelper* getInstance();
	virtual bool init() override;

public:
	// Game Center
	static void GameCenter_authenticateLocalUser(); // login
	static bool GameCenter_isAuthenticated();

	static void GameCenter_showLeaderboard(const char* id);
	static void GameCenter_retriveScoreFromLeaderboard(const char* id);
	static void GameCenter_reportScoreForLeaderboard(const char* id, const int score);

	static void GameCenter_showAchievements();
	static void GameCenter_checkAndUnlockAchievement(const char* id);
	static void GameCenter_unlockAchievementPercent(const char* id, double percent);
	static void GameCenter_resetAchievements();

	// IAP
	static void IAP_initWithProductSet(vector<string>* products); // init

	static void IAP_requestAllPurchasedProducts(bool isTest);
	static void IAP_requestAllPurchasedProductsWithCallback(bool isTest, const function<void()> &func);

	static int IAP_getProductsCount();
	static const char* IAP_getProductID(int index);
	static const char* IAP_getProductTitle(int index);
	static const char* IAP_getProductDescription(int index);
	static const char* IAP_getProductPrice(int index);

	static bool IAP_isPurchased(const char* id);
	static void IAP_purchaseProduct(bool isTest, const char* id);
	static void IAP_restorePurchase(); // restore 

private:
	static void waitingTimeOut(float dt);
};
NS_CSC_END