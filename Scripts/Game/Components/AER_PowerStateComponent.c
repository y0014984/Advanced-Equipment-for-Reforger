[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_PowerStateComponentClass : ScriptComponentClass
{
}

enum EPowerState
{
	OFF,
	STANDBY,
	ON
}

class AER_PowerStateComponent : ScriptComponent
{
	protected EPowerState m_ePowerState = EPowerState.OFF;
	
	//------------------------------------------------------------------------------------------------
	void TurnOn()
	{
		m_ePowerState = EPowerState.ON;
	}
	
	//------------------------------------------------------------------------------------------------
	void TurnOff()
	{
		m_ePowerState = EPowerState.OFF;
	}
	
	//------------------------------------------------------------------------------------------------
	void Standby()
	{
		m_ePowerState = EPowerState.STANDBY;
	}
	
	//------------------------------------------------------------------------------------------------
	EPowerState GetPowerState()
	{
		return m_ePowerState;
	}
}
