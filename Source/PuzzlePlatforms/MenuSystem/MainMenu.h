// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUserName;
};
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerData);

	void SelectIndex(uint32 Index);
protected:
	virtual bool Initialize() override;

private:

	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostGameButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void JoinServer();
	
	UFUNCTION()
	void OpenMainMenu();
	
	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void QuitGame();

	TOptional<uint32> SelectedIndex;

	void UpdateChildren();
};