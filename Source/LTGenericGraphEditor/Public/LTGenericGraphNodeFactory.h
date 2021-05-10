#pragma once
#include <EdGraphUtilities.h>
#include <EdGraph/EdGraphNode.h>

class FGraphPanelNodeFactory_LTGenericGraph : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};