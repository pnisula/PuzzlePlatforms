// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:	
	void SetMenuInterface(IMenuInterface* MenuInterface);
	void Setup();	
protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostGameButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButton;

	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void JoinServer();

	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	IMenuInterface* MenuInterface;
};