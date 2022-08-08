// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleDebuggerCategory.h"
#include "CanvasItem.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false; //����� ���͸� ��°��� ������ true;
}

FExampleDebuggerCategory::~FExampleDebuggerCategory()
{
	
}

TSharedRef<FGameplayDebuggerCategory> FExampleDebuggerCategory::MakeInstance()
{
	//ID �۾��̳� �ν��Ͻ� ���� ī��� �� �ϰ�ʹٸ� ���⿡ ����
	return MakeShareable(new FExampleDebuggerCategory());
}

void FExampleDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	//APlayerController �ش� �÷��̾��� ĵ������ ����װ� ��µǹǷ� �׻� ����ϴ� ī�޶��� �÷��̾� ��Ʈ�ѷ��� �´�
	//DebugActor ĵ�������� ������ Actor

	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);
	//�θ����ǵ� �Լ� ��
	//if (DebugActor==nullptr)return;//������ ���Ͱ� ��ȿ�ϸ� ���� ����

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
		FVector end = start + player->GetActorForwardVector() * 1e+4f; // 10000 ��ŭ �������� LineTrace

		FCollisionQueryParams params;
		params.AddIgnoredActor(player);
		//FCollisionQueryParams: LineTrace�� ���� �߰������� ���� �ڷ���


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
	//����׿� ĵ������ �ϳ� �� �ø� ĵ������? DX���� OM���� ������ 2D View
	//CollectData ���� ������ ���� ���

	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);
	//�θ� ���ǵ� �Լ� ��

	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 215), FLinearColor(0, 0, 0, 0.2f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	//DirectX�� Blend ����
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