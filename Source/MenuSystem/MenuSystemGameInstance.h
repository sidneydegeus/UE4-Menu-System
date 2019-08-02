// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MainMenuInterface.h"
#include "MenuSystemGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEM_API UMenuSystemGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()
	
// Variables
protected:
	UPROPERTY(EditDefaultsOnly)
		FString HostMap;

private:
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

// Functions
public:
	UMenuSystemGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
		void LoadInGameMenu();

	UFUNCTION(Exec)
		void Host() override;

	UFUNCTION(Exec)
		void Join(const FString& Address) override;
};
