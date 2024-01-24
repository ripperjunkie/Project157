#include "DebugImGui.h"
#include <imgui.h>


#include "GameFramework/CharacterMovementComponent.h"
#include "Project_157/Components/Project_157InventoryComponent.h"
#include "Project_157/Components/Project_157WeaponComponent.h"
#include "Project_157/Interfaces/Project_157DebugInfo.h"

static bool _debugAiming = false;
static bool _debugShooting = false;
static bool _debugMelee = false;
static bool _debugCrouching = false;
static bool _debugDriving = false;
static bool _debugSprinting = false;
static bool _debugItemEquipped = false;


DebugImGui::DebugImGui()
{
}


void DebugImGui::DrawInfo(UObject* Owner)
{
	if(!Owner)
	{
		return;
	}
	
	// debug Player
	const FString objectName = Owner->GetName();
	ImGui::Begin( TCHAR_TO_UTF8(*FString("Debug Info: " + objectName) ), nullptr, ImGuiWindowFlags_None);
	if(IProject_157DebugInfo* debugInfo = Cast<IProject_157DebugInfo>(Owner))
	{		
		ImGui::LabelText(TCHAR_TO_UTF8(
			*FString::SanitizeFloat(debugInfo->Debug_GetCharacterMovementComponent()->MaxWalkSpeed))
			, "Max Walk speed: ");
		
		ImGui::LabelText(TCHAR_TO_UTF8(
			*FString::SanitizeFloat(debugInfo->Debug_GetCharacterMovementComponent()->Velocity.Size())),
			"current velocity: ");

		// debug character states
		if (ImGui::CollapsingHeader("States"))
		{
			// Aiming
			_debugAiming = debugInfo->Debug_CharacterState(EProject_157ActionState::Aiming);
			ImGui::Checkbox(" Aiming", &_debugAiming);
			
			// Shooting
			_debugShooting = debugInfo->Debug_CharacterState(EProject_157ActionState::Shooting);
			ImGui::Checkbox(" Shooting", &_debugShooting);

			// Melee			
			_debugMelee = debugInfo->Debug_CharacterState(EProject_157ActionState::Melee);
			ImGui::Checkbox(" Melee", &_debugMelee);
			
			// Crouching			
			_debugCrouching = debugInfo->Debug_CharacterState(EProject_157ActionState::Crouching);
			ImGui::Checkbox(" Crouching", &_debugCrouching);
			
			// Sprinting			
			_debugSprinting = debugInfo->Debug_CharacterState(EProject_157ActionState::Sprinting);
			ImGui::Checkbox(" Sprinting", &_debugSprinting);
			
			// ItemEquipped
			_debugItemEquipped = debugInfo->Debug_CharacterState(EProject_157ActionState::ItemEquipped);
			ImGui::Checkbox(" ItemEquipped", &_debugItemEquipped);

			// Driving
			_debugDriving = debugInfo->Debug_CharacterState(EProject_157ActionState::Driving);
			ImGui::Checkbox("Driving", &_debugDriving);
		}

		// debug inventory
		if(UProject_157InventoryComponent* inventory = Cast<UProject_157InventoryComponent>(debugInfo->Debug_GetInventoryComponent()))
		{
			if (ImGui::CollapsingHeader("Inventory"))
			{

				for (auto& item : inventory->GetCurrentItems())
				{
					// show item name in a collapsing header
					if (ImGui::CollapsingHeader( TCHAR_TO_UTF8(*item->GetName() ) ) )
					{
						// show more details about ite
						ImGui::Text(item->ItemData.ItemSK ? TCHAR_TO_UTF8(*item->ItemData.ItemSK->GetName()) : "no ItemSK");
						ImGui::Text(item->ItemData.AnimInstance ? TCHAR_TO_UTF8(*item->ItemData.AnimInstance->GetName()) : "no AnimInstance");
						ImGui::Text(TCHAR_TO_UTF8(*item->ItemData.ItemName));
						ImGui::Text(TCHAR_TO_UTF8(*item->ItemData.RelativeLocation.ToString()));
						ImGui::Text(TCHAR_TO_UTF8(*item->ItemData.RelativeRotation.ToString()));
					}
				}		
			}
		}
	}
	ImGui::End();
}
