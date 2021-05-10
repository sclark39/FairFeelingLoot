#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EdNode_LTGenericGraphEdge.generated.h"

class ULTGenericGraphNode;
class ULTGenericGraphEdge;
class UEdNode_LTGenericGraphNode;

UCLASS(MinimalAPI)
class UEdNode_LTGenericGraphEdge : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_LTGenericGraphEdge();

	UPROPERTY()
	class UEdGraph* Graph;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "LTGenericGraph")
	ULTGenericGraphEdge* LTGenericGraphEdge;

	void SetEdge(ULTGenericGraphEdge* Edge);

	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UEdNode_LTGenericGraphNode* Start, UEdNode_LTGenericGraphNode* End);

	UEdNode_LTGenericGraphNode* GetStartNode();
	UEdNode_LTGenericGraphNode* GetEndNode();
};
