// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleDebuggerCategory.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
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
	//FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	//if (!!DebugActor)
	//{
	//	Data.Location = DebugActor->GetActorLocation();
	//	Data.Rotation = DebugActor->GetActorRotation();
	//	Data.Forward = DebugActor->GetActorForwardVector();
	//}
}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	//FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	//CanvasContext.Printf(FColor(255, 0, 0), L"Location : %s", *Data.Location.ToString());
	//CanvasContext.Printf(FColor(0, 255, 0), L"Rotation : %s", *Data.Rotation.ToString());
	//CanvasContext.Printf(FColor(0, 0, 255), L"Forward : %s", *Data.Forward.ToString());

	//ACharacter* character = OwnerPC->GetPawn<ACharacter>();
	//CanvasContext.Printf(FColor(255, 0, 255), L"Character : %s", *character->GetActorLocation().ToString());
}