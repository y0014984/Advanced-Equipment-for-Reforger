[BaseContainerProps(), BaseContainerCustomTitleField("m_sDisplayName")]
class AER_PowerStateEntityTooltipDetail : SCR_EntityTooltipDetail
{
	protected TextWidget m_Text;
	
	protected AER_PowerStateComponent m_PowerStateComponent;
	
	override bool NeedUpdate()
	{
		return m_PowerStateComponent != null;
	}
	
	override bool InitDetail(SCR_EditableEntityComponent entity, Widget widget)
	{
		m_PowerStateComponent = AER_PowerStateComponent.Cast(entity.GetOwner().FindComponent(AER_PowerStateComponent));

		if (!m_PowerStateComponent)
			return false;
		
		m_Text = TextWidget.Cast(widget);
		
		return m_Text != null;
	}
	
	override void UpdateDetail(SCR_EditableEntityComponent entity)
	{
		EPowerState powerState = m_PowerStateComponent.GetPowerState();
		
		string powerStateString = "";
		
		switch (powerState)
		{
			case EPowerState.ON:
				powerStateString = "#AER-PowerState-On";
				break;
	
			case EPowerState.OFF:
				powerStateString = "#AER-PowerState-Off";
				break;
			
			case EPowerState.STANDBY:
				powerStateString = "#AER-PowerState-Standby";
				break;
	
			default:
				powerStateString = "Unknown";
				break;
		}
		
		// TODO: We could replace this with a map that contains enum values as keys and the strings as values
		// could be added at the same place where the enum is constructed
		
		m_Text.SetText(powerStateString);
	}
}