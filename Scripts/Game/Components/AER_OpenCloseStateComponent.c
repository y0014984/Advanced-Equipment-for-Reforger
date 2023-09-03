[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_OpenCloseStateComponentClass : ScriptComponentClass
{
}

class AER_OpenCloseStateComponent : ScriptComponent
{
	protected bool m_bIsOpen = true;
	
	//------------------------------------------------------------------------------------------------
	void ToggleOpenCloseState()
	{
		AER_PowerStateComponent powerState = AER_PowerStateComponent.Cast(GetOwner().FindComponent(AER_PowerStateComponent));
		
		if (m_bIsOpen && (powerState.GetPowerState() == EPowerState.ON)) // open && on --> clsed && standby
		{
			m_bIsOpen = false;
			powerState.Standby();
			return;
		}
		
		if (m_bIsOpen && (powerState.GetPowerState() == EPowerState.STANDBY)) // open && standby --> closed && standby
		{
			m_bIsOpen = false;
			return;
		}
		
		if (m_bIsOpen && (powerState.GetPowerState() == EPowerState.OFF)) // open && off --> closed and off
		{
			m_bIsOpen = false;
			return;
		}

		if (!m_bIsOpen && (powerState.GetPowerState() == EPowerState.STANDBY)) // closed && standby --> open && on
		{
			m_bIsOpen = true;
			powerState.TurnOn();
			return;
		}
		
		if (!m_bIsOpen && (powerState.GetPowerState() == EPowerState.OFF)) // closed && off --> open && off
		{
			m_bIsOpen = true;
			return;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsOpen()
	{
		return m_bIsOpen;
	}
}
