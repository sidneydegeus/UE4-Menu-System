// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

bool UInGameMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(InGameMenu_ResumeButton != nullptr)) return false;
	InGameMenu_ResumeButton->OnClicked.AddDynamic(this, &UInGameMenu::Resume);

	if (!ensure(InGameMenu_QuitToMainMenuButton != nullptr)) return false;
	InGameMenu_QuitToMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitToMainMenu);

	if (!ensure(InGameMenu_ExitGameButton != nullptr)) return false;
	InGameMenu_ExitGameButton->OnClicked.AddDynamic(this, &UInGameMenu::ExitGame);

	return true;
}

void UInGameMenu::Resume() {
	TearDownWidget();
}

void UInGameMenu::QuitToMainMenu() {
	if (UGameInstance* const GameInstance = GetGameInstance()) {
		GameInstance->ReturnToMainMenu();
	}
	else {
		UWorld* const World = GetWorld();
		GEngine->HandleDisconnect(World, World->GetNetDriver());
	}
}

void UInGameMenu::ExitGame() {
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}