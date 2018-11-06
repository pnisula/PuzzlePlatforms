// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostGameButton != nullptr)) return false;

	HostGameButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	return true;
}
void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}
void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Hosting Server"));
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
		UE_LOG(LogTemp, Warning, TEXT("Hosting Started"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hosting Failed"));
	}
}
void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining Server"));
}
