// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "OnlineSubsystem.h"
#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:

	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	
	virtual void Init();	
	
	UFUNCTION(exec)
	virtual void Host() override;
	
	UFUNCTION(exec)
	virtual void Join(const FString& Address) override;

	UFUNCTION(exec)
	virtual void LeaveServer() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);

	void CreateSession();
};
