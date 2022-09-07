
#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

/**
ViewPort Clint
�����Ϳ��� ������ Scene �� ����� ī�޶� ����
 */
class EXAMPLE_API FPreviewObjectViewport_Client
	: public FEditorViewportClient
	, public TSharedFromThis<FPreviewObjectViewport_Client>	//This �����͵� �̼������ ��� �Ұ�
{
public:
	FPreviewObjectViewport_Client
	(
		class FPreviewScene* InPreviewScene,						//Scene ��ü(�� ������ ����)
		const TSharedRef<class SMeshObject_Viewport>& InViewport	//ViewPort
	);
	~FPreviewObjectViewport_Client();

private:
	class FAdvancedPreviewScene* AdvancedPreviewScene;

};
