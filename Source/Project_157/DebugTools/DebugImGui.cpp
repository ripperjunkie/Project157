#include "DebugImGui.h"
#include <imgui.h>

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_157/Interfaces/Project_157DebugInfo.h"

DebugImGui::DebugImGui()
{
	owner = nullptr;
}

void DebugImGui::DrawInfo()
{
	if(!owner)
	{
		return;
	}
	const FString objectName = owner->GetName();
	ImGui::Begin(TCHAR_TO_UTF8(*FString("Debug Info: " + objectName)), nullptr, ImGuiWindowFlags_None);
	if(IProject_157DebugInfo* debugInfo = Cast<IProject_157DebugInfo>(owner))
	{		
		ImGui::LabelText(TCHAR_TO_UTF8(*FString::SanitizeFloat(debugInfo->GetCharacterMovementComponent()->MaxWalkSpeed)), "Max Walk speed: ");		
		ImGui::LabelText(TCHAR_TO_UTF8(*FString::SanitizeFloat(debugInfo->GetCharacterMovementComponent()->Velocity.Size())), "current velocity: ");		
	}
	ImGui::End();
}
