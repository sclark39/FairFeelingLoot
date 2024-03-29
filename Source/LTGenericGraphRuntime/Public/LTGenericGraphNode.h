// Copyright 2021 Skyler Clark. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "LTGenericGraphNode.generated.h"

class ULTGenericGraph;
class ULTGenericGraphEdge;

UENUM()
enum class ELTGenericGraphNodeLimit : uint8
{
	Unlimited,
    Limited,
	Forbidden
};


UCLASS()
class LTGENERICGRAPHRUNTIME_API ULTGenericGraphNode : public UObject
{
	GENERATED_BODY()

public:
	ULTGenericGraphNode();
	virtual ~ULTGenericGraphNode();

	UPROPERTY(VisibleDefaultsOnly, Category = "LTGenericGraphNode")
	ULTGenericGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraphNode")
	TArray<ULTGenericGraphNode*> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraphNode")
	TArray<ULTGenericGraphNode*> ChildrenNodes;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraphNode")
	TMap<ULTGenericGraphNode*, ULTGenericGraphEdge*> Edges;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraphNode")
	virtual ULTGenericGraphEdge* GetEdge(const ULTGenericGraphNode* ChildNode) const;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraphNode")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraphNode")
	ULTGenericGraph* GetGraph() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LTGenericGraphNode")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

	//////////////////////////////////////////////////////////////////////////
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText NodeTitle;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText NodeTooltip;

	UPROPERTY(VisibleDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	TSubclassOf<ULTGenericGraph> CompatibleGraphType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FLinearColor BackgroundColor;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText ContextMenuName;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText ContextMenuCategory;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	FText ContextMenuDescription;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	ELTGenericGraphNodeLimit ParentLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor" ,meta = (ClampMin = "1",EditCondition = "ParentLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ParentLimit = 1;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor")
	ELTGenericGraphNodeLimit ChildrenLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraphNode_Editor" ,meta = (ClampMin = "1",EditCondition = "ChildrenLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ChildrenLimit = 1;
	
#endif

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent &PropertyChangedEvent ) override;

	virtual TSubclassOf<ULTGenericGraphEdge> GetEdgeType() const;

	virtual bool IsNameEditable() const;

	virtual FLinearColor GetBackgroundColor() const;

	virtual FText GetNodeTitle() const;
	virtual FText GetNodeTooltip() const;

	virtual FText GetContextMenuName() const;
	virtual FText GetContextMenuCategory() const;
	virtual FText GetContextMenuDescription() const;

	virtual void SetNodeTitle(const FText& NewTitle);

	virtual const FSlateBrush* GetNodeIcon() const;

	virtual bool CanCreateConnection(ULTGenericGraphNode* Other, FText& ErrorMessage);

	virtual bool CanCreateConnectionTo(ULTGenericGraphNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(ULTGenericGraphNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage);

	virtual void GetChildrenLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const;
	virtual void GetParentLimit(ELTGenericGraphNodeLimit &LimitType, int32 &LimitCount) const;
#endif
};
