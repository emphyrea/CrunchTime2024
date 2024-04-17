// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CMainMenu.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Framework/CGameInstance.h"

void UCMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	LoginBtn->OnClicked.AddDynamic(this, &UCMainMenu::LoginBtnClicked);
	CreateSessionBtn->OnClicked.AddDynamic(this, &UCMainMenu::CreateSessionBtnClicked);
	CreateSessionBtn->SetIsEnabled(false);
	SessionNameText->OnTextChanged.AddDynamic(this, &UCMainMenu::SessionNameTextChanged);
	FindSessionBtn->OnClicked.AddDynamic(this, &UCMainMenu::FindSessionBtnClicked);
	CGameInst=GetGameInstance<UCGameInstance>();
}

void UCMainMenu::SessionNameTextChanged(const FText& NewText)
{
	CreateSessionBtn->SetIsEnabled(!NewText.IsEmpty());
}

void UCMainMenu::LoginBtnClicked()
{
	if (CGameInst)
	{
		CGameInst->Login();
	}
}

void UCMainMenu::CreateSessionBtnClicked()
{
	if (CGameInst)
	{
		CGameInst->CreateSession(FName{SessionNameText->GetText().ToString()});
	}
}

void UCMainMenu::FindSessionBtnClicked()
{
	if (CGameInst)
	{
		CGameInst->FindSessions();
	}
}
