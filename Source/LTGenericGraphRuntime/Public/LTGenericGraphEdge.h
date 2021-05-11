#pragma once

#include "CoreMinimal.h"
#include "LTGenericGraphNode.h"
#include "LTGenericGraphEdge.generated.h"

class ULTGenericGraph;

UCLASS()
class LTGENERICGRAPHRUNTIME_API ULTGenericGraphEdge : public UObject
{
	GENERATED_BODY()

public:
	ULTGenericGraphEdge();
	virtual ~ULTGenericGraphEdge();

	UPROPERTY(VisibleAnywhere, Category = "LTGenericGraphNode")
	ULTGenericGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraphEdge")
	ULTGenericGraphNode* StartNode;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraphEdge")
	ULTGenericGraphNode* EndNode;

	UFUNCTION(BlueprintPure, Category = "LTGenericGraphEdge")
	ULTGenericGraph* GetGraph() const;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	bool bShouldDrawTitle = false;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText NodeTitle;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphEdge")
	FLinearColor EdgeColour = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

#if WITH_EDITOR
	virtual FText GetNodeTitle() const { return NodeTitle; }
	FLinearColor GetEdgeColour() { return EdgeColour; }

	virtual void SetNodeTitle(const FText& NewTitle);
#endif
	
};
