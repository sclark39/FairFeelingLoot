#pragma once

#include "CoreMinimal.h"
#include "LTGenericGraphNode.h"
#include "LTGenericGraphEdge.h"
#include "GameplayTagContainer.h"
#include "LTGenericGraph.generated.h"

UCLASS()
class LTGENERICGRAPHRUNTIME_API ULTGenericGraph : public UObject
{
	GENERATED_BODY()

public:
	ULTGenericGraph();
	virtual ~ULTGenericGraph();
	
	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphNode> NodeType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphNode> RootNodeType;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph")
	TSubclassOf<ULTGenericGraphEdge> EdgeType;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraph")
	TArray<ULTGenericGraphNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "LTGenericGraph")
	TArray<ULTGenericGraphNode*> AllNodes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LTGenericGraph")
	bool bEdgeEnabled;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "LTGenericGraph")
	void GetNodesByLevel(int Level, TArray<ULTGenericGraphNode*>& Nodes);

	void ClearGraph();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph_Editor")
	bool bCanRenameNode;

	UPROPERTY(EditDefaultsOnly, Category = "LTGenericGraph_Editor")
	bool bCanBeCyclical;
#endif
};
