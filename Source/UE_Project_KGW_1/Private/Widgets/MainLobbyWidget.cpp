// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainLobbyWidget.h"
#include "Components\Button.h"
#include "PlayerGameFramework\PlayableController.h"

void UMainLobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UE_LOG(LogTemp, Display, TEXT("Main Widget Native"));
	
	bIsFocusable = true;

	if (StartButton && !StartButton->OnClicked.IsBound())
	{
		UE_LOG(LogTemp, Display, TEXT("StartButton Bound"));
		StartButton->OnClicked.AddDynamic(this, &UMainLobbyWidget::OpenInGameLevel);
	}

	if (OptionButton && !OptionButton->OnClicked.IsBound())
	{
		UE_LOG(LogTemp, Display, TEXT("OptionButton Bound"));
		OptionButton->OnClicked.AddDynamic(this, &UMainLobbyWidget::OpenOptionMenu);
	}

}

void UMainLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainLobbyWidget::OpenInGameLevel()
{
	FString LevelName = TEXT("/Game/Levels/StartLevel");

	if (APlayableController* PC = Cast<APlayableController>(GetOwningPlayer()))
	{
		if (PC)
		{
			RemoveFromParent();
			PC->ClientTravel(LevelName, ETravelType::TRAVEL_Absolute);
			PC->SetInputMode(FInputModeGameOnly());
			PC->bShowMouseCursor = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Playable Controller Not Found!"));
	}

	/* TODO:
	현재는 Replication 적용하지 않은 상태
	Replicated 추가시 매치매이킹 시스템 구현
	1. 서버에 큐 참가 요청
	2. 해당 큐에 일정 인원이 모이면 매치 생성
	3. 서버에서 해당 매칭 완료 결과를 클라이언트에 전달
	--Case : 클라이언트 (로비 UI 내 ) --
	4. 클라이언트는 메시지를 응답받고 게임으로 이동. (ClientTravel)
	--Case : 서버 (게임 세션 생성, 전환)
	4. 새 게임 서버 생성 (ServerTravel)
	5. 클라이언트들에게 새로운 게임 서버로 이동 명령(ClientTravel)

	현재는 로직 구현을 우선순위로 한 싱글플레이 전용으로 구현

	*/
}

void UMainLobbyWidget::OpenOptionMenu()
{
}
