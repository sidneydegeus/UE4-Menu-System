// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!bAddDynamicsMainMenu()) return false;
	if (!bAddDynamicsJoinMenu()) return false;

	return true;
}

void UMainMenu::HostServer() {
	if (MainMenuInterface != nullptr) {
		MainMenuInterface->Host();
	}
}

void UMainMenu::JoinServer() {
	if (MainMenuInterface != nullptr) {
		if (!ensure(IPAddressTextBox != nullptr)) return;
		const FString& Address = IPAddressTextBox->GetText().ToString();
		MainMenuInterface->Join(Address);
	}
}

void UMainMenu::ExitGame() {
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UMainMenu::OpenMainMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::OpenJoinMenu() {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

bool UMainMenu::bAddDynamicsMainMenu() {
	if (!ensure(MainMenu_HostButton != nullptr)) return false;
	MainMenu_HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(MainMenu_JoinButton != nullptr)) return false;
	MainMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(MainMenu_ExitGameButton != nullptr)) return false;
	MainMenu_ExitGameButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

bool UMainMenu::bAddDynamicsJoinMenu() {
	if (!ensure(JoinMenu_JoinButton != nullptr)) return false;
	JoinMenu_JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(JoinMenu_BackButton != nullptr)) return false;
	JoinMenu_BackButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;
}