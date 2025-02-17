// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameMode.h"
#include "Blueprint\UserWidget.h"
#include "Widgets\MainLobbyWidget.h"
#include "UObject\ConstructorHelpers.h"

void AShootingGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Start GameMode BeginPlay"));

	if (TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UI/Widgets/BP_MainLobbyWidget.BP_MainLobbyWidget_C")))
	{
		FString CurrentLevel = GetWorld()->GetMapName();
		CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		if (CurrentLevel != "LobbyLevel") return;

		UE_LOG(LogTemp, Warning, TEXT("Load Widget"));
		UMainLobbyWidget* StartMenu = CreateWidget<UMainLobbyWidget>(GetWorld(), WidgetClass);
		if (StartMenu)
		{
			UE_LOG(LogTemp, Warning, TEXT("UI"));
			StartMenu->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				UE_LOG(LogTemp, Warning, TEXT("Connecting PC InputMode"));
				PC->SetInputMode(FInputModeUIOnly());
				PC->bShowMouseCursor = true;
			}
		}
	}
}