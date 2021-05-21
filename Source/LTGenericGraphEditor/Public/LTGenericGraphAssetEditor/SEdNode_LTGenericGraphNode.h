#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UEdNode_LTGenericGraphNode;

class LTGENERICGRAPHEDITOR_API SEdNode_LTGenericGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdNode_LTGenericGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdNode_LTGenericGraphNode* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual bool IsNameReadOnly() const override;

	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	virtual FSlateColor GetBorderBackgroundColor() const;
	virtual FSlateColor GetBackgroundColor() const;

	virtual EVisibility GetDragOverMarkerVisibility() const;

	virtual const FSlateBrush* GetNodeIcon() const;

	FText GetNodeTooltip() const;

protected:
};

