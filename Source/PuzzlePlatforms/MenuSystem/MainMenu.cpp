// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostGameButton != nullptr)) return false;	
	HostGameButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	
	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}

void UMainMenu::HostServer()
{	
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hosting Failed"));
	}
}
void UMainMenu::JoinServer()
{		
	UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;

		const FString& IPAddress = IPAddressField->GetText().ToString();
		MenuInterface->Join(IPAddress);		
	}	
}
void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}
void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);	
}