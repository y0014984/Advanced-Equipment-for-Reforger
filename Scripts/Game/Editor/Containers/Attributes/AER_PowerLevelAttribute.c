[BaseContainerProps(), SCR_BaseEditorAttributeCustomTitle()]
class AER_PowerLevelAttribute : SCR_BaseFloatValueHolderEditorAttribute
{
	protected AER_PowerStateComponent m_PowerStateComponent;

	//------------------------------------------------------------------------------------------------
	protected bool IsPowerStateComponentAvailable(Managed item)
	{
		if (!m_PowerStateComponent)
		{
			SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(item);
			if (!editableEntity) return false;
			
			IEntity owner =  editableEntity.GetOwner();
			if (!owner) return false;
			
			m_PowerStateComponent = AER_PowerStateComponent.Cast(owner.FindComponent(AER_PowerStateComponent));
			if (!m_PowerStateComponent) return false;
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override SCR_BaseEditorAttributeVar ReadVariable(Managed item, SCR_AttributesManagerEditorComponent manager)
	{
		if(!IsPowerStateComponentAvailable(item))
			return null;
		
		EPowerState powerState = m_PowerStateComponent.GetPowerState();
		
		return SCR_BaseEditorAttributeVar.CreateInt(powerState);
	}
	
	//------------------------------------------------------------------------------------------------
	override void WriteVariable(Managed item, SCR_BaseEditorAttributeVar var, SCR_AttributesManagerEditorComponent manager, int playerID)
	{
		if (!var) 
			return;

		if(!IsPowerStateComponentAvailable(item))
			return;
		
		EPowerState powerState = var.GetInt();
		
		m_PowerStateComponent.SetPowerState(powerState);
	}

	//------------------------------------------------------------------------------------------------
	override int GetEntries(notnull array<ref SCR_BaseEditorAttributeEntry> outEntries)
	{
		FillValues();
		
		outEntries.Insert(new SCR_BaseEditorAttributeFloatStringValues(m_aValues));
		
		return outEntries.Count();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void FillValues()
	{
		m_aValues.Clear();
		
		array<ref AER_PowerStateName> powerStateNames = new array<ref AER_PowerStateName>;
		
		m_PowerStateComponent.GetPowerStateNames(powerStateNames);
		SCR_EditorAttributeFloatStringValueHolder value;
		
		foreach (AER_PowerStateName powerStateName: powerStateNames)
		{
			value = new SCR_EditorAttributeFloatStringValueHolder();
			value.SetName(powerStateName.GetName());
			value.SetFloatValue(powerStateName.GetPowerState());
			
			m_aValues.Insert(value);
		}
	}
}