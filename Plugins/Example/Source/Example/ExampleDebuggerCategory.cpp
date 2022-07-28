// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleDebuggerCategory.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
	bShowOnlyWithDebugActor = false; //����� ���͸� ������ false;
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
	if (!!DebugActor)//������ ���Ͱ� ��ȿ�ϸ� ���� ����
	{
		DebugData.Location = DebugActor->GetActorLocation();
		DebugData.Rotation = DebugActor->GetActorRotation();
		DebugData.Forward = DebugActor->GetActorForwardVector();
	}
}

void FExampleDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	//����׿� ĵ������ �ϳ� �� �ø� ĵ������? DX���� OM���� ������ 2D View
	//CollectData ���� ������ ���� ���

	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);
	//�θ� ���ǵ� �Լ� ��


	ACharacter* character = OwnerPC->GetPawn<ACharacter>();
	//�÷��̾� ĳ���͸� ������
	CanvasContext.Printf(FColor::Yellow, TEXT("Character : %s"), *character->GetActorLocation().ToString());


	CanvasContext.Printf(FColor::Red, TEXT("Location : %s"), *DebugData.Location.ToString());
	CanvasContext.Printf(FColor::Green, TEXT("Rotation : %s"), *DebugData.Rotation.ToString());
	CanvasContext.Printf(FColor::Blue, TEXT("Forward : %s"), *DebugData.Forward.ToString());

}//FColor::Magenta	