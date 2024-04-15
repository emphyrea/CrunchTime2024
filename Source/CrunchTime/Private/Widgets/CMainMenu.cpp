// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CMainMenu.h"
#include "Components/Button.h"
#include "Framework/CGameInstance.h"

void UCMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	LoginBtn->OnClicked.AddDynamic(this, &UCMainMenu::LoginBtnClicked);
	CGameInst=GetGameInstance<UCGameInstance>();
}

void UCMainMenu::LoginBtnClicked()
{
	if (CGameInst)
	{
		CGameInst->Login();
	}
}
