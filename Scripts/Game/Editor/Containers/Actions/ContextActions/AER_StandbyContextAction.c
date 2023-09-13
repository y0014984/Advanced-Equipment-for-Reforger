[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class AER_StandbyContextAction : SCR_GeneralContextAction
{
	protected AER_PowerStateComponent powerStateComponent;
	
	protected bool CanBeStandbyEnabled(notnull SCR_EditableEntityComponent selectedEntity)
	{
		powerStateComponent = AER_PowerStateComponent.Cast(selectedEntity.GetOwner().FindComponent(AER_PowerStateComponent));
		
		if(!powerStateComponent)
			return false;
		
		return (powerStateComponent.GetPowerState() == EPowerState.ON);
	}
	
	
	override bool CanBeShown(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return (selectedEntities.Count() == 1 && CanBeStandbyEnabled(selectedEntities.Get(0)));
	}
	
	override bool CanBePerformed(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition, int flags)
	{
		return true;
	}
	
	override void Perform(SCR_EditableEntityComponent hoveredEntity, notnull set<SCR_EditableEntityComponent> selectedEntities, vector cursorWorldPosition,int flags, int param = -1)
	{
		powerStateComponent.Standby();
	}
}