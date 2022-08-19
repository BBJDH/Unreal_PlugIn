
#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

/**
 * 
 */
class EXAMPLE_API FPreviewObjectViewport_Client
	: public FEditorViewportClient
	, public TSharedFromThis<FPreviewObjectViewport_Client>	//This 포인터도 이선언없이 사용 불가
{
public:
	FPreviewObjectViewport_Client
	(
		class FPreviewScene* InPreviewScene,
		const TSharedRef<class SMeshObject_Viewport>& InViewport
	);
	~FPreviewObjectViewport_Client();

private:
	class FAdvancedPreviewScene* AdvancedPreviewScene;

};
