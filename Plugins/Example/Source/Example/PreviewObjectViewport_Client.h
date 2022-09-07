
#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

/**
ViewPort Clint
에디터에서 보여줄 Scene 을 출력할 카메라 정의
 */
class EXAMPLE_API FPreviewObjectViewport_Client
	: public FEditorViewportClient
	, public TSharedFromThis<FPreviewObjectViewport_Client>	//This 포인터도 이선언없이 사용 불가
{
public:
	FPreviewObjectViewport_Client
	(
		class FPreviewScene* InPreviewScene,						//Scene 객체(잘 사용되지 않음)
		const TSharedRef<class SMeshObject_Viewport>& InViewport	//ViewPort
	);
	~FPreviewObjectViewport_Client();

private:
	class FAdvancedPreviewScene* AdvancedPreviewScene;

};
