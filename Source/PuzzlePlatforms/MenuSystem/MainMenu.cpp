// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	ServerRowClass = ServerRowBPClass.Class;
}
bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostGameButton != nullptr)) return false;	
	HostGameButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

	if (!ensure(JoinGameButton != nullptr)) return false;
	JoinGameButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	
	if (!ensure(BackButton != nullptr)) return false;
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::HostServer()
{	
	if (MenuInterface != nullptr)
	{		
		FString CustomServerName = ServerHostName->Text.ToString();
		
		MenuInterface->Host(CustomServerName);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hosting Failed"));
	}
}
void UMainMenu::SetServerList(TArray<FServerData> ServerData)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& DataRow : ServerData)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(DataRow.Name));
		Row->HostName->SetText(FText::FromString(DataRow.HostUserName));
		FString ConnectionText = FString::Printf(TEXT("%d/%d"), DataRow.CurrentPlayers, DataRow.MaxPlayers);
		Row->Connections->SetText(FText::FromString(ConnectionText));
		Row->Setup(this, i);		
		++i;

		ServerList->AddChild(Row);		
	}	
}
void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;	
	UpdateChildren();
}
void UMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); i++)
	{
		UServerRow* Row = Cast<UServerRow>(ServerList->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

void UMainMenu::JoinServer()
{		
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index Not Set"));
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
	if (MenuInterface != nullptr)
	{
		MenuInterface->RefreshServerList();
	}
}
void UMainMenu::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(HostMenu);	
}
void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("Quit");
}