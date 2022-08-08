// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleDebuggerCategory.h"
#include "CanvasItem.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false; //디버그 엑터만 출력값을 보려면 true;
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
	//if (DebugActor==nullptr)return;//선택한 액터가 유효하면 정보 수집

	ACharacter* player = OwnerPC->GetPawn<ACharacter>();
	//Character
	{
		PlayerPawnData.Name = player->GetName();
		PlayerPawnData.Location = player->GetActorLocation();
		PlayerPawnData.Forward = player->GetActorForwardVector();

	}

	//Forward
	{

		FHitResult hitResult;

		FVector start = player->GetActorLocation();
		FVector end = start + player->GetActorForwardVector() * 1e+4f; // 10000 만큼 전방으로 LineTrace

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);
		//FCollisionQueryParams: LineTrace에 관한 추가정보를 적을 자료형


		player->GetWorld()->LineTraceSingleByChannel
		(
			hitResult,
			start,
			end,
			ECollisionChannel::ECC_Visibility,
			params
		);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
		else
		{
			ForwardActorData.Name = "";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;
		}

	}
	if (!!DebugActor)
	{
		SelectedActorData.Name = DebugActor->GetName();
		SelectedActorData.Location = DebugActor->GetActorLocation();
		SelectedActorData.Forward = DebugActor->GetActorForwardVector();
	}
	else
	{
		SelectedActorData.Name = "";
		SelectedActorData.Location = FVector::ZeroVector;
		SelectedActorData.Forward = FVector::ZeroVector;
	}


}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	//디버그용 캔버스를 하나 더 올림 캔버스란? DX에서 OM에서 합쳐질 2D View
	//CollectData 에서 수집한 정보 출력

	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);
	//부모에 정의된 함수 콜

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.2f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	//DirectX의 Blend 설정
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, TEXT("  --  Player Pawn  --"));
	CanvasContext.Printf(FColor::White, TEXT("  Name : %s"), *PlayerPawnData.Name);
	CanvasContext.Printf(FColor::White, TEXT("  Location : %s"), *PlayerPawnData.Location.ToString());
	CanvasContext.Printf(FColor::White, TEXT("  Forward : %s"), *PlayerPawnData.Forward.ToString());

	CanvasContext.Printf(FColor::Green, TEXT("  --  Forward Actor  --"));
	CanvasContext.Printf(FColor::White, TEXT("  Name : %s"), *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, TEXT("  Location : %s"), *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, TEXT("  Forward : %s"), *ForwardActorData.Forward.ToString());

	CanvasContext.Printf(FColor::Green, TEXT("  --  Selected Actor  --"));
	CanvasContext.Printf(FColor::White, TEXT("  Name : %s"), *SelectedActorData.Name);
	CanvasContext.Printf(FColor::White, TEXT("  Location : %s"), *SelectedActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, TEXT("  Forward : %s"), *SelectedActorData.Forward.ToString());
}