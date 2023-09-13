[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class AER_ToggleDebugModeToolbarAction : SCR_BaseToggleToolbarAction
{
	protected bool m_bIsDebugModeEnabled;
	
	//------------------------------------------------------------------------------------------------
	override bool IsServer()
	{
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShown(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformed(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void Perform(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition,int flags, int param = -1)
	{		
		if (m_bIsDebugModeEnabled)
		{
			m_bIsDebugModeEnabled = false;
			Print("AER Debug Mode disabled");
		}
		else
		{
			m_bIsDebugModeEnabled = true;			
			Print("AER Debug Mode enabled");
		}

		Toggle(m_bIsDebugModeEnabled, m_bIsDebugModeEnabled);
	}

	//------------------------------------------------------------------------------------------------
	override void Track()
	{
		
	}
	
	//------------------------------------------------------------------------------------------------
	override void Untrack()
	{
		
	}
}