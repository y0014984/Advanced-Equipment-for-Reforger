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
	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "Power state of entity (on, off, standby)", params: "", enums: ParamEnumArray.FromEnum(EPowerState), category: "Advanced Equipment")]
	protected EPowerState m_ePowerStateWE;	
	
	[RplProp()]
	protected EPowerState m_ePowerState;
	
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
