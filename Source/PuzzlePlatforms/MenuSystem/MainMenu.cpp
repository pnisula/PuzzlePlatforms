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
void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
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
void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	//UE_LOG(LogTemp, Warning, TEXT("LEVEL WAS REMOVED FROM WORLD"));
		
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;	
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;		
}
