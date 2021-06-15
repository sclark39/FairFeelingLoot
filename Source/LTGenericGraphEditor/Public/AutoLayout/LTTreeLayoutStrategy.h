// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LTAutoLayoutStrategy.h"
#include "LTTreeLayoutStrategy.generated.h"

UCLASS()
class LTGENERICGRAPHEDITOR_API ULTTreeLayoutStrategy : public ULTAutoLayoutStrategy
{
	GENERATED_BODY()
public:
	ULTTreeLayoutStrategy();
	virtual ~ULTTreeLayoutStrategy();

	virtual void Layout(UEdGraph* EdGraph) override;

protected:
	void InitPass(ULTGenericGraphNode* RootNode, const FVector2D& Anchor);
	bool ResolveConflictPass(ULTGenericGraphNode* Node);

	bool ResolveConflict(ULTGenericGraphNode* LRoot, ULTGenericGraphNode* RRoot);

	void GetLeftContour(ULTGenericGraphNode* RootNode, int32 Level, TArray<UEdNode_LTGenericGraphNode*>& Contour);
	void GetRightContour(ULTGenericGraphNode* RootNode, int32 Level, TArray<UEdNode_LTGenericGraphNode*>& Contour);
	
	void ShiftSubTree(ULTGenericGraphNode* RootNode, const FVector2D& Offset);

	void UpdateParentNodePosition(ULTGenericGraphNode* RootNode);
};
