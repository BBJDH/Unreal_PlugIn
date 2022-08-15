// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/ButtonCommand.h"

#include "StaticMesh_Detail.h"
#include "CStaticMesh_Copied.h"
#include "CViewportObject.h"
#include "ViewportEditor.h"

#include "IDesktopPlatform.h"
#include "Interfaces/IMainFrameModule.h"	//�𸮾� ���������� ������
#include "DesktopPlatformModule.h"			//������ �ڵ� ����, ��������
#include "Serialization/BufferArchive.h"
#include "LevelEditorViewport.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"			//UGameplayStatics::FinishSpawningActor

FButtonCommand::FButtonCommand()
	: TCommands
	(
		"LoadMesh",								//����̸�
		FText::FromString("Load Mesh Data"),	//��ɿ� ���� ����(�Ƚᵵ ��)
		NAME_None,								//�θ� �ִ��� ����
		FEditorStyle::GetStyleSetName()			//������ ��Ÿ�� ����(�⺻��Ÿ�Ϸ� ������)
	)
{
	Command = MakeShareable(new FUICommandList());

}

FButtonCommand::~FButtonCommand()
{
	if(Command.IsValid())
		Command.Reset();
		
	//����Ʈ�������̱⿡ �ڵ� ������ ������ �׷��� ���� �۾��� ���ش�
}


void FButtonCommand::RegisterCommands()
{
	//TCommands ���������Լ�, ���� ��ư�� � ��ư���� ��������, � �Լ��� ���ε� �Ͽ� ���������� ���� ���� 
#define LOCTEXT_NAMESPACE ""	//���ӽ����̽� ����(������ �������� ��)
	UI_COMMAND
	(
		Id,									// ����� ID(FUICommandInfo)
		"LoadMesh",							// UI�� ��Ÿ�� Ŀ�ǵ�(�츮�� �� �ĺ���)
		"Load Mesh Data",					// ��ɿ� ���� ���� 
		EUserInterfaceActionType::Button,	// ��Ÿ���� �� Ÿ��(��ư, üũ�ڽ�, ��۹�ư ��,
		FInputChord()						// ����Ű ����(����Ű))
	);

	UI_COMMAND
	(
		Id2,									// ����� ID(FUICommandInfo)
		"ViewPort",							// UI�� ��Ÿ�� Ŀ�ǵ�(�츮�� �� �ĺ���)
		"Open Viewport",					// ��ɿ� ���� ���� 
		EUserInterfaceActionType::Button,	// ��Ÿ���� �� Ÿ��(��ư, üũ�ڽ�, ��۹�ư ��,
		FInputChord()						// ����Ű ����(����Ű))
	);
	//UI_COMMAND(Id2, "MeshEditor", "Open Mesh Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
	//���⿡ �Լ������͸� ���ε�
	Command->MapAction
	(
		Id,								//UI�� ���� ���� ����(FUICommandInfo)
		FExecuteAction::CreateRaw		//��������Ʈ�� ����(Bind�� �ƴ� Create�� ���� ����, ���ӳ��� �ƴϹǷ� UFUNCTION�� �������� ����)
		(
			this,						//�� Ŭ�����ν��Ͻ��� �ִ�
			&FButtonCommand::OnClicked	//�ش��Լ��� ���ε�
		),
		FCanExecuteAction()				//��ư�� ���� �� �ְ� ����
	);
	Command->MapAction
	(
		Id2, 
		FExecuteAction::CreateRaw
		(
			this, 
			&FButtonCommand::OnClicked2
		), 
		FCanExecuteAction()
	);
}

void FButtonCommand::OnClicked()
{
	//GLog->Log("Clicked!!!");


	FString path;
	FPaths::GetPath(path);

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();

	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	//���� ����(�г�)������
	/*
	������ ���� ������Ʈ
	�̿� ��ũ����
	���� ������ ���� �ĺ��� �ĺ� ����
	�𸮾� ���� ��
	������ ���������� �˻�
	*/

	TArray<FString> fileNames;
	//���� ���� ���̾�α� â ����
	platform->OpenFileDialog
	(
		handle,								//������ �ڵ�
		"Open Dialog",						//â ����
		path,								//�⺻���
		"",									//�⺻ ���� �̸�
		"Mesh Binary File(*.bin)|*.bin",	//Ȯ����|���� ������Ȯ����
		EFileDialogFlags::None,				
		fileNames
	);
	if (fileNames.Num() < 1) return;


	//FBufferArchive �� TArray<uint8>�� ��� �޾Ҵ�

	FBufferArchive archive;
	//TArray<uint8> ��ӹ޾ұ� ������ ��ĳ������ ����
	FFileHelper::LoadFileToArray(archive, *fileNames[0]);
	//������������ �Ȱ��� LoadFileToArray�� ���̳ʸ� ������ �ҷ����� �Լ��̴�

	//FBufferArchive�� Write������ ��ӵǾ��ֱ⿡ FMemoryReader�� ���� Load �Ѵ�
	FMemoryReader reader = FMemoryReader(archive, true);	//true�� ���� ����

	//0���������� ����Ʈ������ �д´�
	archive.Seek(0);

	//FStaticMesh_Detail���� �����ߴ� FStaticMesh_DetailData ������

	FStaticMesh_DetailData data;	//��� �����ʿ�, ������ �����͸� ���� data ����
	reader << data;					//�𸮾��� ����� ��� ������ <<�� ���Ǹ�
									//�����ε��� �ʿ��Կ� ��������

	reader.FlushCache();	//ĳ�ø� ���� ���� �����͸� ����
	reader.Close();			//������ ������ �����ϴµ� ���Ǵ� ��� �ڵ��� �ݰ� 
							//�� �õ��� �����ϸ� true�� ��ȯ

	//������ ����� �ҷ��Դ��� Ȯ��
	GLog->Logf(TEXT("Vertex Count : %d"), data.Positions.Num());
	GLog->Logf(TEXT("Index Count : %d"), data.Indices.Num());
	GLog->Logf(TEXT("Extent : %s"), *data.Extent.ToString());
	GLog->Logf(TEXT("Radius : %f"), data.Radius);
	

	//����� �о�Դ��� �ٽ� �����ϴ� ������ ���� Ȯ��(������ ����)
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ", ");
		text.Append(data.Normals[i].ToString() + ", ");
		text.Append(data.Uvs[i].ToString() + ", ");
		text.Append(data.Colors[i].ToString() + "\r\n");
	}

	FString txtFileName = FPaths::GetBaseFilename(fileNames[0], false); //�� �ڿ� Ȯ���ڸ� �����ϰ� ������
	FString txtSaveName = txtFileName + ".csv";							//Ȯ���ڸ� ���Ƿ�.csv�� �ٲ�
	//.csv�� ���� ���� �Ǵ� �ؽ�Ʈ ����

	//SaveStringToFile(������, �������ϸ�) => �ؽ�Ʈ�� ����
	FFileHelper::SaveStringToFile(text, *txtSaveName);// txtSaveName - ������ ���� ��
	FString str;
	str = "";
	str.Append(FPaths::GetCleanFilename(txtSaveName));
	str.Append(" File Saved.");
	GLog->Log(*str);



	//����Ʈ�� �����´�FLevelEditorViewportClient(����Ʈ �ڷ���)		�����Ͱ�ü -> Ȱ��ȭ�� ����Ʈ		Ŭ���̾�Ʈ
	FLevelEditorViewportClient* client = (FLevelEditorViewportClient *)GEditor->GetActiveViewport()->GetClient();

	FVector start = client->GetViewLocation();	//ī�޶��� ��ġ ���
	FVector end = start + client->GetViewRotation().RotateVector(FVector(10000, 0, 0));
	//ī�޶� �������� 10000 ���� ������ end ���� ���


	FHitResult hitResult;
	//�����͸� ���ؼ��� ���带 ���� �� �ִ� 
	UWorld* world = GEditor->GetEditorWorldContext().World();

	//���带 ���ؼ��� ����Ʈ���̽� ȣ���� ����! �����ξ���hitResult�� ����� ���
	world->LineTraceSingleByChannel
	(
		hitResult, 
		start, 
		end, 
		ECollisionChannel::ECC_Visibility	//Visibility ä�ε� ��� �浹
	);
	if (hitResult.bBlockingHit == false) return;	//������ �ƹ��͵��׷����� ����

	GLog->Log(*hitResult.Location.ToCompactString());

	FTransform transform;
	FVector direction = (hitResult.TraceEnd - hitResult.TraceStart);	
	//����Ʈ���̽� ������ ������ �븻���͸� �����
	direction.Normalize();

	//ī�޶� ���������κ��� �浹�������Ÿ���ŭ���� actor�� �ִ�ݰ��� ���Ÿ���ŭ �������ش�
	FVector location = hitResult.TraceStart + direction * (hitResult.Distance - data.Radius);
	transform.SetLocation(location);


	//������ ������Ʈ�� ���溤�͸� ī�޶�� Yaw�� ���缭 ����
	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));


	//SpawnActorDeferred�� ���� OnConstruction ȣ������ ���� �������ش�
	//SpawnActor���� Deferred�� ����� �ֿ��غ���
	ACStaticMesh_Copied* actor = world->SpawnActorDeferred<ACStaticMesh_Copied>
	(
		ACStaticMesh_Copied::StaticClass(),									//UClass Ÿ�� ���÷���, �����̶�� LoadClass�� ���� ������ �ҷ��� ���
		transform,															//���� ����
		nullptr,															//������
		nullptr,															//������(�޼����� �������ִ� ���)
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn	//���� ����
	);

	//SpawnActorDeferred �� ������ ����
	actor->SetPositions(data.Positions);
	actor->SetIndices(data.Indices);
	actor->SetNormals(data.Normals);
	actor->SetUvs(data.Uvs);
	actor->SetColors(data.Colors);

	//SpawnActorDeferred�� ���� ���� �� �ش� ����, Ȯ����ġ�� FinishSpawningActor ���� �ʿ��ϴ�
	//actor->FinishSpawning(transform);�� ����� ����
	UGameplayStatics::FinishSpawningActor(actor, transform);
}

void FButtonCommand::OnClicked2()
{
	GLog->Log("Viewport");
	FViewportEditor::OpenWindow(NewObject<UCViewportObject>());

}
