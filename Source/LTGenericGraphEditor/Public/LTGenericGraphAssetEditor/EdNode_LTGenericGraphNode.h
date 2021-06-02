#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "LTGenericGraphNode.h"
#include "EdNode_LTGenericGraphNode.generated.h"

class UEdNode_LTGenericGraphEdge;
class UEdGraph_LTGenericGraph;
class SEdNode_LTGenericGraphNode;


UCLASS(MinimalAPI)
class UEdNode_LTGenericGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_LTGenericGraphNode();
	virtual ~UEdNode_LTGenericGraphNode();

	UPROPERTY(VisibleAnywhere, Instanced, Category = "LTGenericGraph")
	ULTGenericGraphNode* LTGenericGraphNode;

	void SetLTGenericGraphNode(ULTGenericGraphNode* InNode);
	UEdGraph_LTGenericGraph* GetLTGenericGraphEdGraph();

	SEdNode_LTGenericGraphNode* SEdNode;

	virtual FString GetDocumentationExcerptName() const override;
	virtual FText GetTooltipText() const override;

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	virtual FLinearColor GetBackgroundColor() const;
	virtual const FSlateBrush* GetNodeIcon() const;

	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

	virtual bool CanDuplicateNode() const override;
	virtual bool CanUserDeleteNode() const override;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;

#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif

};
