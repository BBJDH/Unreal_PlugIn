// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/ButtonCommand.h"

#include "StaticMesh_Detail.h"
#include "CStaticMesh_Copied.h"
#include "CViewportObject.h"
#include "ViewportEditor.h"

#include "IDesktopPlatform.h"
#include "Interfaces/IMainFrameModule.h"	//언리얼 메인프레임 진입점
#include "DesktopPlatformModule.h"			//윈도우 핸들 접근, 파일접근
#include "Serialization/BufferArchive.h"
#include "LevelEditorViewport.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"			//UGameplayStatics::FinishSpawningActor

FButtonCommand::FButtonCommand()
	: TCommands
	(
		"LoadMesh",								//명령이름
		FText::FromString("Load Mesh Data"),	//명령에 대한 설명(안써도 됨)
		NAME_None,								//부모가 있는지 유무
		FEditorStyle::GetStyleSetName()			//에디터 스타일 지정(기본스타일로 지정함)
	)
{
	Command = MakeShareable(new FUICommandList());

}

FButtonCommand::~FButtonCommand()
{
	if(Command.IsValid())
		Command.Reset();
		
	//스마트포인터이기에 자동 해제가 되지만 그래도 해제 작업을 해준다
}


void FButtonCommand::RegisterCommands()
{
	//TCommands 순수가상함수, 실제 버튼이 어떤 버튼으로 보여질지, 어떤 함수를 바인드 하여 동작할지에 대한 정보 
#define LOCTEXT_NAMESPACE ""	//네임스페이스 열기(원래는 국가명이 들어감)
	UI_COMMAND
	(
		Id,									// 명령의 ID(FUICommandInfo)
		"LoadMesh",							// UI에 나타날 커맨드(우리가 쓸 식별자)
		"Load Mesh Data",					// 명령에 대한 설명 
		EUserInterfaceActionType::Button,	// 나타나게 할 타입(버튼, 체크박스, 토글버튼 등,
		FInputChord()						// 단축키 정의(단축키))
	);

	UI_COMMAND
	(
		Id2,									// 명령의 ID(FUICommandInfo)
		"ViewPort",							// UI에 나타날 커맨드(우리가 쓸 식별자)
		"Open Viewport",					// 명령에 대한 설명 
		EUserInterfaceActionType::Button,	// 나타나게 할 타입(버튼, 체크박스, 토글버튼 등,
		FInputChord()						// 단축키 정의(단축키))
	);
	//UI_COMMAND(Id2, "MeshEditor", "Open Mesh Editor", EUserInterfaceActionType::Button, FInputChord());
#undef LOCTEXT_NAMESPACE
	//여기에 함수포인터를 바인딩
	Command->MapAction
	(
		Id,								//UI에 대한 정보 연결(FUICommandInfo)
		FExecuteAction::CreateRaw		//델리게이트와 동일(Bind가 아닌 Create를 통해 연결, 게임내가 아니므로 UFUNCTION도 선언하지 않음)
		(
			this,						//이 클래스인스턴스에 있는
			&FButtonCommand::OnClicked	//해당함수를 바인딩
		),
		FCanExecuteAction()				//버튼이 눌릴 수 있게 설정
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
	//가장 상위(패널)윈도우
	/*
	컴파일 게임 프로젝트
	이외 스크립팅
	현재 엔진에 대한 식별자 식별 가능
	언리얼 빌드 툴
	파일이 정상적인지 검사
	*/

	TArray<FString> fileNames;
	//파일 열기 다이얼로그 창 생성
	platform->OpenFileDialog
	(
		handle,								//윈도우 핸들
		"Open Dialog",						//창 제목
		path,								//기본경로
		"",									//기본 파일 이름
		"Mesh Binary File(*.bin)|*.bin",	//확장자|실제 보여질확장자
		EFileDialogFlags::None,				
		fileNames
	);
	if (fileNames.Num() < 1) return;


	//FBufferArchive 는 TArray<uint8>을 상속 받았다

	FBufferArchive archive;
	//TArray<uint8> 상속받았기 때문에 업캐스팅이 가능
	FFileHelper::LoadFileToArray(archive, *fileNames[0]);
	//저장했을때와 똑같이 LoadFileToArray는 바이너리 파일을 불러오는 함수이다

	//FBufferArchive는 Write까지만 상속되어있기에 FMemoryReader로 만들어서 Load 한다
	FMemoryReader reader = FMemoryReader(archive, true);	//true면 원본 유지

	//0번지점부터 바이트단위로 읽는다
	archive.Seek(0);

	//FStaticMesh_Detail에서 선언했던 FStaticMesh_DetailData 가져옴

	FStaticMesh_DetailData data;	//헤더 선언필요, 렌더링 데이터를 받을 data 선언
	reader << data;					//언리얼은 입출력 모두 방향이 <<로 사용되며
									//오버로딩이 필요함에 유의하자

	reader.FlushCache();	//캐시를 비우고 내부 데이터를 해제
	reader.Close();			//데이터 저장을 지원하는데 사용되는 모든 핸들을 닫고 
							//이 시도가 성공하면 true를 반환

	//데이터 제대로 불러왔는지 확인
	GLog->Logf(TEXT("Vertex Count : %d"), data.Positions.Num());
	GLog->Logf(TEXT("Index Count : %d"), data.Indices.Num());
	GLog->Logf(TEXT("Extent : %s"), *data.Extent.ToString());
	GLog->Logf(TEXT("Radius : %f"), data.Radius);
	

	//제대로 읽어왔는지 다시 저장하는 절차를 통해 확인(엑셀로 저장)
	FString text;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		text.Append(data.Positions[i].ToString() + ", ");
		text.Append(data.Normals[i].ToString() + ", ");
		text.Append(data.Uvs[i].ToString() + ", ");
		text.Append(data.Colors[i].ToString() + "\r\n");
	}

	FString txtFileName = FPaths::GetBaseFilename(fileNames[0], false); //맨 뒤에 확장자만 제거하고 가져옴
	FString txtSaveName = txtFileName + ".csv";							//확장자만 임의로.csv로 바꿈
	//.csv는 엑셀 지원 되는 텍스트 파일

	//SaveStringToFile(데이터, 저장파일명) => 텍스트로 저장
	FFileHelper::SaveStringToFile(text, *txtSaveName);// txtSaveName - 저장할 파일 명
	FString str;
	str = "";
	str.Append(FPaths::GetCleanFilename(txtSaveName));
	str.Append(" File Saved.");
	GLog->Log(*str);



	//뷰포트를 가져온다FLevelEditorViewportClient(뷰포트 자료형)		에디터객체 -> 활성화된 뷰포트		클라이언트
	FLevelEditorViewportClient* client = (FLevelEditorViewportClient *)GEditor->GetActiveViewport()->GetClient();

	FVector start = client->GetViewLocation();	//카메라의 위치 기록
	FVector end = start + client->GetViewRotation().RotateVector(FVector(10000, 0, 0));
	//카메라 전방으로 10000 길이 움직인 end 지점 기록


	FHitResult hitResult;
	//에디터를 통해서도 월드를 얻어올 수 있다 
	UWorld* world = GEditor->GetEditorWorldContext().World();

	//월드를 통해서도 라인트레이스 호출이 가능! 만들어두었던hitResult에 결과를 기록
	world->LineTraceSingleByChannel
	(
		hitResult, 
		start, 
		end, 
		ECollisionChannel::ECC_Visibility	//Visibility 채널들 모두 충돌
	);
	if (hitResult.bBlockingHit == false) return;	//없으면 아무것도그려지지 않음

	GLog->Log(*hitResult.Location.ToCompactString());

	FTransform transform;
	FVector direction = (hitResult.TraceEnd - hitResult.TraceStart);	
	//라인트레이스 방향을 가지는 노말벡터를 만든다
	direction.Normalize();

	//카메라 쏜지점으로부터 충돌된지점거리만큼에서 actor의 최대반경을 뺀거리만큼 움직여준다
	FVector location = hitResult.TraceStart + direction * (hitResult.Distance - data.Radius);
	transform.SetLocation(location);


	//스폰시 오브젝트의 전방벡터를 카메라와 Yaw만 맞춰서 설정
	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));


	//SpawnActorDeferred를 통해 OnConstruction 호출전에 값을 세팅해준다
	//SpawnActor보다 Deferred를 더욱더 애용해보자
	ACStaticMesh_Copied* actor = world->SpawnActorDeferred<ACStaticMesh_Copied>
	(
		ACStaticMesh_Copied::StaticClass(),									//UClass 타입 리플렉션, 게임이라면 LoadClass를 통해 에셋을 불러서 사용
		transform,															//생성 지점
		nullptr,															//소유자
		nullptr,															//전파자(메세지를 전달해주는 대상)
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn	//생성 조건
	);

	//SpawnActorDeferred 의 정보를 세팅
	actor->SetPositions(data.Positions);
	actor->SetIndices(data.Indices);
	actor->SetNormals(data.Normals);
	actor->SetUvs(data.Uvs);
	actor->SetColors(data.Colors);

	//SpawnActorDeferred의 값으 세팅 후 해당 액터, 확정위치로 FinishSpawningActor 콜이 필요하다
	//actor->FinishSpawning(transform);도 사용해 보자
	UGameplayStatics::FinishSpawningActor(actor, transform);
}

void FButtonCommand::OnClicked2()
{
	GLog->Log("Viewport");
	FViewportEditor::OpenWindow(NewObject<UCViewportObject>());

}
