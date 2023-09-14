[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_PowerStateComponentClass : ScriptComponentClass
{
}

class AER_PowerStateComponent : ScriptComponent
{
	[RplProp(), Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "Power state of entity (on, off, standby)", params: "", enums: ParamEnumArray.FromEnum(EPowerState), category: "Advanced Equipment")]
	protected EPowerState m_ePowerState;
	
	[Attribute("0", desc: "Array of Power State names", category: "Advanced Equipment")]
	protected ref array<ref AER_PowerStateName> m_aPowerStateNames;
	
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
	
	//------------------------------------------------------------------------------------------------
	void SetPowerState(EPowerState powerState)
	{
		m_ePowerState = powerState;
	}
	
	//------------------------------------------------------------------------------------------------
	int GetPowerStateNames(notnull array<ref AER_PowerStateName> powerStateNames)
	{
		//SetPowerStateNames();
		
		powerStateNames.Clear();
		foreach (AER_PowerStateName powerStateName: m_aPowerStateNames)
			powerStateNames.Insert(powerStateName);
		
		return powerStateNames.Count();
	}
}

enum EPowerState
{
	OFF,
	STANDBY,
	ON
}

[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(EPowerState, "m_ePowerState")]
class AER_PowerStateName
{
	[Attribute(desc: "Power State type", uiwidget : UIWidgets.ComboBox, enums: ParamEnumArray.FromEnum(EPowerState))]
	protected EPowerState m_ePowerState;
	
	[Attribute(desc: "Name displayed", uiwidget: UIWidgets.LocaleEditBox)]
	protected LocalizedString m_sPowerStateName;
	
	EPowerState GetPowerState()
	{
		return m_ePowerState;
	}
	
	string GetName()
	{
		return m_sPowerStateName;
	}
	
	void SetPowerState(EPowerState powerState)
	{
		m_ePowerState = powerState;
	}
	
	void SetName(string powerStateName)
	{
		m_sPowerStateName = powerStateName;
	}
};
