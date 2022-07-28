// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleDebuggerCategory.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false; //디버그 엑터만 보려면 false;
}

FExampleDebuggerCategory::~FExampleDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FExampleDebuggerCategory::MakeInstance()
{
	//ID 작업이나 인스턴스 생성 카운딩 등 하고싶다면 여기에 정의
	return MakeShareable(new FExampleDebuggerCategory());
}

void FExampleDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	//APlayerController 해당 플레이어의 캔버스에 디버그가 출력되므로 항상 사용하는 카메라의 플레이어 컨트롤러로 온다
	//DebugActor 캔버스에서 선택한 Actor

	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);
	//부모에정의된 함수 콜
	if (!!DebugActor)//선택한 액터가 유효하면 정보 수집
	{
		DebugData.Location = DebugActor->GetActorLocation();
		DebugData.Rotation = DebugActor->GetActorRotation();
		DebugData.Forward = DebugActor->GetActorForwardVector();
	}
}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	//디버그용 캔버스를 하나 더 올림 캔버스란? DX에서 OM에서 합쳐질 2D View
	//CollectData 에서 수집한 정보 출력

	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);
	//부모에 정의된 함수 콜


	ACharacter* character = OwnerPC->GetPawn<ACharacter>();
	//플레이어 캐릭터를 가져옴
	CanvasContext.Printf(FColor::Yellow, TEXT("Character : %s"), *character->GetActorLocation().ToString());


	CanvasContext.Printf(FColor::Red, TEXT("Location : %s"), *DebugData.Location.ToString());
	CanvasContext.Printf(FColor::Green, TEXT("Rotation : %s"), *DebugData.Rotation.ToString());
	CanvasContext.Printf(FColor::Blue, TEXT("Forward : %s"), *DebugData.Forward.ToString());

}//FColor::Magenta	