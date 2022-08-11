

#include "StaticMesh_Detail.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#include "IDesktopPlatform.h"
#include "Interfaces/IMainFrameModule.h"	//언리얼 메인프레임 진입점
#include "DesktopPlatformModule.h"			//윈도우 핸들 접근, 파일접근
#include "Serialization/BufferArchive.h"	
#include "Misc/FileHelper.h"


#include "CStaticMesh.h"
#include "Components/StaticMeshComponent.h"

TSharedRef<IDetailCustomization> FStaticMesh_Detail::MakeInstance()
{
	return MakeShareable(new FStaticMesh_Detail());
	//기본 생성자로 ShareRef 반환
}

void FStaticMesh_Detail::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//GLog->Log(TEXT("Open Detail Tab"));
	//클릭시 디테일 창 띄워짐

	IDetailCategoryBuilder & mesh = DetailBuilder.EditCategory("Mesh");
	//Mesh라는 카테고리가 있다면 그것을 리턴 없으면 만들어서 리턴
	// => Mesh라고하는 카테고리 지역이 생성, 혹은 있는곳으로부터 편집

	//UI출력은 전부 Text로 
	mesh.AddCustomRow(FText::FromString("Color"))	//Color로 디테일 검색되도록 지정
	.NameContent()	//이름 영역이 자료형은 배열로 취급됨 
	[
		SNew(STextBlock)		//Slate 동적할당
		.Text(FText::FromString("Color"))	//제목 지정
	]
	.ValueContent()	//값 영역 (제목 오른쪽)
	.VAlign(VAlign_Center)	//수직정렬
	.MaxDesiredWidth(250)	//최대 넓이 250
	[
		SNew(SButton)	//버튼 동적할당
		.VAlign(VAlign_Center)	//수직정렬은 가운데정렬로
		.HAlign(HAlign_Fill)	//가로정렬은 꽉차게
		.OnClicked(this, &FStaticMesh_Detail::OnClicked_Paint)	//버튼을 눌렀을때의 이벤트
		.Content()	//이 해당 지역의 내용물을 설정
		[
			SNew(STextBlock)	//텍스트 블록 설정
			.Text(FText::FromString("Paint"))	//
		]
	];


	//디테일레이아웃 추가
	mesh.AddCustomRow(FText::FromString("SaveMesh"))	//Color로 디테일 검색되도록 지정(식별자)
		.NameContent()	//이름 영역이 자료형은 배열로 취급됨 
		[
			SNew(STextBlock)		//Slate 동적할당
			.Text(FText::FromString("Save"))	//제목 지정
		]
	.ValueContent()	//값 영역 (제목 오른쪽)
		.VAlign(VAlign_Center)	//수직정렬
		.MaxDesiredWidth(250)	//최대 넓이 250
		[
			SNew(SButton)	//버튼 동적할당
			.VAlign(VAlign_Center)	//수직정렬은 가운데정렬로
		.HAlign(HAlign_Fill)	//가로정렬은 꽉차게
		.OnClicked(this, &FStaticMesh_Detail::OnClicked_SaveMesh)	//버튼을 눌렀을때의 이벤트
		.Content()	//이 해당 지역의 내용물을 설정
		[
			SNew(STextBlock)	//텍스트 블록 설정
			.Text(FText::FromString("Save!"))	//
		]
		];

	DetailBuilder.GetObjectsBeingCustomized(Objects);
	//선택한 오브젝트들을 Objects로 받아옴
}

FReply FStaticMesh_Detail::OnClicked_Paint()
{
	//GLog->Log(TEXT("Paint"));

	//선택된 모든 오브젝트 이름들을 출력
	//for (TWeakObjectPtr<UObject> obj : Objects)
	//	GLog->Log(*obj->GetName());

	//선택된 오브젝트들 중 첫번째를 ACStaticMesh로 캐스팅
	ACStaticMesh* mesh = Cast<ACStaticMesh>(Objects[0]);

	//성공했다면 Paint() 호출
	if (!!mesh)
		mesh->Paint();
	//마테리얼을 랜덤컬러로 칠하는 함수

	return FReply::Handled();
	//하위 slate로 처리를 맡기지 않고 여기서 종료
	//Unhandled 다음 계층으로 처리를 넘김
}

FReply FStaticMesh_Detail::OnClicked_SaveMesh()
{
	ACStaticMesh* meshActor = Cast<ACStaticMesh>(Objects[0]);
	//선택한 첫번째 지정
	if (meshActor == nullptr) return FReply::Handled();

	/*
	선택한 자료형이 ACStaticMesh임이 확인되었다
	저장 절차를 시작하자
	렌더링 정보를 불러오기위해
	Static Mesh로 캐스팅
	*/
	UActorComponent * actorComponent = meshActor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	//리턴형이 ActorComponent 이다
	//다시 캐스팅해준다
	UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(actorComponent);

	if(meshComponent == nullptr) 	return FReply::Unhandled();	// 다음에서 처리할 수 있게 패스!

	UStaticMesh* mesh = meshComponent->GetStaticMesh();		//여기에 렌더 정보가 있다!
	FStaticMeshRenderData * renderData =  mesh->RenderData.Get(); //RenderData은 UniquePtr이다

	if(renderData->LODResources.Num()<1) return FReply::Unhandled();
	//렌더링 정보가 없다는것을 의미 LOD 배열이 비어있다는것을 판단 한 것

	//렌더링 정보가 유효 하다면 가장 정밀한 0번 LOD 정보를 복사

	FStaticMeshLODResources& lod = renderData->LODResources[0];
	FPositionVertexBuffer& vb = lod.VertexBuffers.PositionVertexBuffer;
	//각 정점들의 위치, 컬러정보, 등등
	FStaticMeshVertexBuffer& meshVB = lod.VertexBuffers.StaticMeshVertexBuffer;
	//노멀벡터, UV, 탄젠트벡터(노멀맵)

	FColorVertexBuffer& colorVB = lod.VertexBuffers.ColorVertexBuffer;
	FRawStaticIndexBuffer& ib = lod.IndexBuffer;

	if (vb.GetNumVertices() < 1) return FReply::Unhandled();
	if (ib.GetNumIndices() < 1) return FReply::Unhandled();
	//정점 배열이나 인덱스 배열이 1보다 작으면 그릴 정보가 없다는 의미로 해석

	uint32 vertexCount = vb.GetNumVertices();	//정점 개수
	int32 indexCount = ib.GetNumIndices();		//인덱스 수 /3 하면 폴리곤 수

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);
	GLog->Logf(TEXT("Index Count : %d"), indexCount);


	FString path;
	FPaths::GetPath(path);	//현재 파일 경로를 가져옴


	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	//MainFrame -> 에디터 창 전체(언리얼의 뼈대)

	void* handle =  mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	/*
	 mainFrame.GetParentWindow() 메인 에디터 화면
	 >GetNativeWindow()->GetOSWindowHandle() 통해 핸들을 가져옴
	//핸들이란? 윈도우에서 그 프로그램의 시작 주소이자 윈도우에서 프로그램을 식별하는 ID
	WHAND는 void*
	*/


	IDesktopPlatform * platform = FDesktopPlatformModule::Get();
	//가장 상위(패널)윈도우
	/*
	컴파일 게임 프로젝트
	이외 스크립팅
	현재 엔진에 대한 식별자 식별 가능
	언리얼 빌드 툴
	파일이 정상적인지 검사
	*/
	TArray<FString> fileNames;

	//쓰기전용으로 저장 다이얼로그 생성
	platform->SaveFileDialog
	(
		handle,								//포커스를 묶어둘 핸들 모달(modaless?)
		"Save Dialog",						//띄워질 창 제목
		path,								//불러와질 경로
		"FileName",							//기본 파일 이름
		"Mesh Binary File(*.bin)|*.bin",	//(확장자 설명) |실제로 필터링될 확장자들 표시
		EFileDialogFlags::None,				//쓰레드 지원유무(다이얼로그 열릴때 동시에 접근하는 쓰레드)
		fileNames							//지정된 파일목록(TArray<FString> 으로 리턴)
	);
	//와일드 문자열?
	if (fileNames.Num() < 1) return FReply::Unhandled();//다음 패널로 전달
	//언핸들 할지 핸들 할지


	//GLog->Log(path);
	//버블링 터널링 정리



	//데이터 하나씩 저장 시작
	FStaticMesh_DetailData data;
	TArray<FColor> colors;
	colorVB.GetVertexColors(colors);
	//컬러를 먼저 빼주고 버텍스 수만큼 값이 유효하도록 할당
	//for문으로 같이 넣기 위함

	if (colors.Num() < 1)	//해당 정점의 컬러가 존재하지 않는다면 정점 수만큼 컬러를 할당
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor(0, 0, 0, 255));
	}


	/*
	부피를 구하기 위한 절차
	*/
	FVector minBounds = FVector(MAX_FLT, MAX_FLT, MAX_FLT);
	FVector maxBounds = FVector(-MAX_FLT, -MAX_FLT, -MAX_FLT);

	for (uint32 i = 0; i < vertexCount; i++)
	{

		FVector position = vb.VertexPosition(i);

		//정점의 최소값 업데이트
		if (position.X < minBounds.X)	minBounds.X = position.X;
		if (position.Y < minBounds.Y)	minBounds.Y = position.Y;
		if (position.Z < minBounds.Z)	minBounds.Z = position.Z;

		//정점의 최대값 업데이트
		if (position.X > maxBounds.X)	maxBounds.X = position.X;
		if (position.Y > maxBounds.Y)	maxBounds.Y = position.Y;
		if (position.Z > maxBounds.Z)	maxBounds.Z = position.Z;

		data.Positions.Add(vb.VertexPosition(i));	//버텍스 번호에 있는 버텍스 포지션
		data.Normals.Add(meshVB.VertexTangentZ(i));	// 노멀추가, Z는 노멀 X는 탄젠트백터, y는 바이탄젠트
		data.Uvs.Add(meshVB.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);

	}

	//각가의 축으로 양 끝단의 거리를 계산, 부피로 넣음
	float x = FMath::Abs(minBounds.X - maxBounds.X);
	float y = FMath::Abs(minBounds.Y - maxBounds.Y);
	float z = FMath::Abs(minBounds.Z - maxBounds.Z);

	//부피 입력
	data.Extent = FVector(x, y, z);

	//각 축중에 가장 큰 길이축을 Radius에 넣음
	data.Radius = FMath::Max(x, y);
	data.Radius = FMath::Max(data.Radius, z);

	GLog->Logf(TEXT("x : %0.1f, y : %0.1f, z : %0.1f"), x, y, z);
	GLog->Logf(TEXT("Radius : %f"), data.Radius);


	//인덱스 가져오기 
	TArray<uint32> indices;
	//반환 TArray<uint32>
	ib.GetCopy(indices);
	//포인터로 인덱스 삽입, 몇개를, 0번부터
	//Add함수가 없어서 포인터로 넣는 Insert 사용
	data.Indices.Insert((int32*)indices.GetData(), indexCount,0);


	FBufferArchive buffer;		//FArchive로부터 상속받았으므로 <<연산자 오버로딩 유효
	buffer << data;				//연산자 오버로딩된 함수 호출

	//.Bin 파일로 저장 함수
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);
	/*
	SaveString - 텍스트로 저장
	ArrayFile - 바이너리로 저장
	*/
	//파일을 다루는 함수들이 내장,  

	//캐시로 다 밀어서 쓰고 항상 버퍼는 비워준다
	//파일스트림에 쌓여있는 데이터가 있으면 같이 들어가지므로 파일이 깨진다
	buffer.FlushCache();	//캐시에 있는 데이터를 다 스트림으로 민다(파일내보내기)
	buffer.Empty();			//스트림 클리어




	/*
	이번엔 문자열로 저장하는 절차 시작
	
	*/
	FString str;
	
	str.Append(FPaths::GetCleanFilename(fileNames[0])); // 해당경로에서 딱 맨끝 파일명만 리턴
	str.Append(" File Saved.");
	GLog->Log(*str);

	//텍스트 파일로 쓰기 위해
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

	//텍스트로 저장
	FFileHelper::SaveStringToFile(text, *txtSaveName);// txtSaveName - 저장할 파일 명

	str = "";
	str.Append(FPaths::GetCleanFilename(txtSaveName));
	str.Append(" File Saved.");
	GLog->Log(*str);


	return FReply::Handled();
}