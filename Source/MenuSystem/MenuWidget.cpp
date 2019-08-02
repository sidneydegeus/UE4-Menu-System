// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMainMenuInterface(IMainMenuInterface* MainMenuInterface) {
	this->MainMenuInterface = MainMenuInterface;
}

void UMenuWidget::Setup() {
	this->AddToViewport();
	this->bIsFocusable = true;

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

void UMenuWidget::TearDownWidget() {
	RemoveFromViewport();
	auto* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	auto* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly inputMode;
	PlayerController->SetInputMode(inputMode);
	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) {
	TearDownWidget();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}