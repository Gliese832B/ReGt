/*
 *  App.h
 *  Created by Seth Robinson on 3/6/09.
 *  For license info, check the license.txt file that should have come with this.
 *
 */

#pragma once
#include "ItemInfo.h"
#include "BaseApp.h"
#include "enet/enet.h"
#include "ENetClient.h"


class App: public BaseApp
{
public:
	
	App();
	virtual ~App();
	
	virtual bool Init();
	virtual void Kill();
	virtual void Draw();
	virtual void OnScreenSizeChange();
	virtual void OnEnterBackground();
	virtual void OnEnterForeground();
	virtual bool OnPreInitVideo();
	virtual void Update();
	void OnExitApp(VariantList *pVarList);
	
	
	//we'll wire these to connect to some signals we care about
	void OnAccel(VariantList *pVList);
	void OnArcadeInput(VariantList *pVList);
	VariantDB db;
	Console* console = new Console;
	ENetClient* client = new ENetClient;
	std::string GetSmartFileName(std::string* a, std::string a2, std::string a3);
	std::string GetCachedFileName(std::string* a, std::string a2, std::string a3);
	

	ItemInfoManager* ItemManager = new ItemInfoManager;
private:

	bool m_bDidPostInit;
	Surface m_surf; //for testing
};


App * GetApp();
const char * GetAppName();
const char * GetBundlePrefix();
const char * GetBundleName();
