// Copyright 2021 Skyler Clark. All Rights Reserved.

#include "LTGenericGraphAssetEditor/SEdNode_LTGenericGraphNode.h"
#include "LTGenericGraphEditorPCH.h"
#include "LTGenericGraphAssetEditor/Colors_LTGenericGraph.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "SGraphPin.h"
#include "GraphEditorSettings.h"
#include "LTGenericGraphAssetEditor/EdNode_LTGenericGraphNode.h"
#include "LTGenericGraphAssetEditor/LTGenericGraphDragConnection.h"
#include "IDocumentation.h"

#include "LTGenericGraphEditorStrings.h"

#define LOCTEXT_NAMESPACE "EdNode_LTGenericGraph"

//////////////////////////////////////////////////////////////////////////
class SLTGenericGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SLTGenericGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		this->SetCursor(EMouseCursor::Default);

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr);

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);

		SBorder::Construct(SBorder::FArguments()
			.BorderImage(this, &SLTGenericGraphPin::GetPinBorder)
			.BorderBackgroundColor(this, &SLTGenericGraphPin::GetPinColor)
			.OnMouseButtonDown(this, &SLTGenericGraphPin::OnPinMouseDown)
			.Cursor(this, &SLTGenericGraphPin::GetPinCursor)
			.Padding(FMargin(5.0f))
		);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return IsHovered() ?
			FLinearColor::White : 
			LTGenericGraphColors::Pin::Default;
	}

	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}

	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<class SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins) override
	{
		FLTGenericGraphDragConnection::FDraggedPinTable PinHandles;
		PinHandles.Reserve(InStartingPins.Num());
		// since the graph can be refreshed and pins can be reconstructed/replaced 
		// behind the scenes, the DragDropOperation holds onto FGraphPinHandles 
		// instead of direct widgets/graph-pins
		for (const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
		{
			PinHandles.Add(PinWidget->GetPinObj());
		}

		return FLTGenericGraphDragConnection::New(InGraphPanel, PinHandles);
	}

};


//////////////////////////////////////////////////////////////////////////
void SEdNode_LTGenericGraphNode::Construct(const FArguments& InArgs, UEdNode_LTGenericGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	SetCursor(EMouseCursor::CardinalCross);
	InNode->SEdNode = this;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEdNode_LTGenericGraphNode::UpdateGraphNode()
{
	const FMargin NodePadding = FMargin(5);
	const FMargin NamePadding = FMargin(2);

	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush *NodeTypeIcon = GetNodeIcon();

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SVerticalBox> NodeBody;
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0.0f)
			.BorderBackgroundColor(this, &SEdNode_LTGenericGraphNode::GetBorderBackgroundColor)
			[
				SNew(SOverlay)

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)

					// Input Pin Area
					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(LeftNodeBox, SVerticalBox)
					]

					// Output Pin Area	
					+ SVerticalBox::Slot()
					.FillHeight(1)
					[
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(8.0f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("Graph.StateNode.ColorSpill"))
					.BorderBackgroundColor(TitleShadowColor)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.Visibility(EVisibility::SelfHitTestInvisible)
					.Padding(6.0f)
					[
						SAssignNew(NodeBody, SVerticalBox)
									
						// Title
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)

							// Error message
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SAssignNew(ErrorText, SErrorText)
								.BackgroundColor(this, &SEdNode_LTGenericGraphNode::GetErrorColor)
								.ToolTipText(this, &SEdNode_LTGenericGraphNode::GetErrorMsgToolTip)
							]

							// Icon
							+SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							[
								SNew(SImage)
								.Image(NodeTypeIcon)
							]
										
							// Node Title
							+ SHorizontalBox::Slot()
							.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									SAssignNew(InlineEditableText, SInlineEditableTextBlock)
									.Style(FAppStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
									.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
									.OnVerifyTextChanged(this, &SEdNode_LTGenericGraphNode::OnVerifyNameTextChanged)
									.OnTextCommitted(this, &SEdNode_LTGenericGraphNode::OnNameTextCommited)
									.IsReadOnly(this, &SEdNode_LTGenericGraphNode::IsNameReadOnly)
									.IsSelected(this, &SEdNode_LTGenericGraphNode::IsSelectedExclusively)
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								[
									NodeTitle.ToSharedRef()
								]
							]
						]					
					]
				]
			]
		];

	// Create comment bubble
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	if (!SWidget::GetToolTip().IsValid())
	{
		TSharedRef<SToolTip> DefaultToolTip = 
			IDocumentation::Get()->CreateToolTip(
				TAttribute< FText >(this, &SEdNode_LTGenericGraphNode::GetNodeTooltip),
				NULL, 
				GraphNode->GetDocumentationLink(), 
				GraphNode->GetDocumentationExcerptName());
		SetToolTip(DefaultToolTip);
	}

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}


FText SEdNode_LTGenericGraphNode::GetNodeTooltip() const
{
	if (GraphNode != NULL)
	{
		FText TooltipText = GraphNode->GetTooltipText();

		if (TooltipText.IsEmpty())
		{
			TooltipText = GraphNode->GetNodeTitle(ENodeTitleType::FullTitle);
		}

		return TooltipText;
	}
	else
	{
		return NSLOCTEXT("GraphEditor", "InvalidGraphNode", "<Invalid graph node>");
	}
}


void SEdNode_LTGenericGraphNode::CreatePinWidgets()
{
	UEdNode_LTGenericGraphNode* StateNode = CastChecked<UEdNode_LTGenericGraphNode>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SLTGenericGraphPin, MyPin);


			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SEdNode_LTGenericGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility( TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced) );
	}

	TSharedPtr<SVerticalBox> PinBox;
	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		PinBox = LeftNodeBox;
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		PinBox = RightNodeBox;
		OutputPins.Add(PinToAdd);
	}

	if (PinBox)
	{
		PinBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			//.Padding(6.0f, 0.0f)
			[
				PinToAdd
			];
	}
}

bool SEdNode_LTGenericGraphNode::IsNameReadOnly() const
{
	UEdNode_LTGenericGraphNode* EdNode_Node = Cast<UEdNode_LTGenericGraphNode>(GraphNode);
	check(EdNode_Node != nullptr);

	if (EdNode_Node->LTGenericGraphNode == nullptr)
		return true;

	ULTGenericGraph* LTGenericGraph = EdNode_Node->LTGenericGraphNode->Graph;
	check(LTGenericGraph != nullptr);

	return (!LTGenericGraph->bCanRenameNode || !EdNode_Node->LTGenericGraphNode->IsNameEditable()) || SGraphNode::IsNameReadOnly();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdNode_LTGenericGraphNode::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnNameTextCommited(InText, CommitInfo);

	UEdNode_LTGenericGraphNode* MyNode = CastChecked<UEdNode_LTGenericGraphNode>(GraphNode);

	if (MyNode != nullptr && MyNode->LTGenericGraphNode != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("LTGenericGraphEditorRenameNode", GGS_RENAME_NODE));
		MyNode->Modify();
		MyNode->LTGenericGraphNode->Modify();
		MyNode->LTGenericGraphNode->SetNodeTitle(InText);
		UpdateGraphNode();
	}
}

FSlateColor SEdNode_LTGenericGraphNode::GetBorderBackgroundColor() const
{
	UEdNode_LTGenericGraphNode* MyNode = CastChecked<UEdNode_LTGenericGraphNode>(GraphNode);
	return MyNode ? MyNode->GetBackgroundColor() : LTGenericGraphColors::NodeBorder::HighlightAbortRange0;
}

FSlateColor SEdNode_LTGenericGraphNode::GetBackgroundColor() const
{
	return LTGenericGraphColors::NodeBody::Default;
}

EVisibility SEdNode_LTGenericGraphNode::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}

const FSlateBrush* SEdNode_LTGenericGraphNode::GetNodeIcon() const
{
	UEdNode_LTGenericGraphNode* MyNode = CastChecked<UEdNode_LTGenericGraphNode>(GraphNode);
	return MyNode ? MyNode->GetNodeIcon() : FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}

#undef LOCTEXT_NAMESPACE
