// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystemGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"


UMenuSystemGameInstance::UMenuSystemGameInstance(const FObjectInitializer & ObjectInitializer) {
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MainMenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UMenuSystemGameInstance::Init() {
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuClass->GetName());
}


void UMenuSystemGameInstance::LoadMainMenu() {
	if (!ensure(MainMenuClass != nullptr)) return;
	UMainMenu* MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->Setup();
	MainMenu->SetMainMenuInterface(this);
}

void UMenuSystemGameInstance::LoadInGameMenu() {
	if (!ensure(InGameMenuClass != nullptr)) return;
	UInGameMenu* InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;

	InGameMenu->Setup();
	InGameMenu->SetMainMenuInterface(this);
}

void UMenuSystemGameInstance::Host() {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel(HostMap + "?listen");
}

void UMenuSystemGameInstance::Join(const FString& Address) {
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}