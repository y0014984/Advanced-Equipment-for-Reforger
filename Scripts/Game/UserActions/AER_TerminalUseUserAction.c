class AER_TerminalUseUserAction : ScriptedUserAction
{
	[Attribute(defvalue: "{5E3EDA618BE7FF1D}UI/layouts/AER_TerminalUI.layout")] // setup the created layout here
	protected ResourceName m_sLayout;

	protected ref Widget m_wDisplay;
	
	private AER_OpenCloseStateComponent m_OpenCloseState;
	
	private AER_PowerStateComponent m_PowerState;
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		return CanBePerformedScript(user);
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!m_OpenCloseState) // Do nothing if there is no signal manager
		{
			Print("AER: No Open/Close State Component", LogLevel.ERROR);
			
			return false;
		}

		if (!m_OpenCloseState.IsOpen()) // Check if laptop is open
			return false;
		
		if (!(m_PowerState.GetPowerState() == EPowerState.ON)) // Check if laptop is powered on
			return false;
		
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_wDisplay)
		{
			delete m_wDisplay;
			return;
		}

		MenuBase menu = GetGame().GetMenuManager().OpenDialog(ChimeraMenuPreset.AER_TerminalUI, DialogPriority.INFORMATIVE, 0, true);
		
		AER_TerminalUI terminal = AER_TerminalUI.Cast(menu);
		
		AER_OpenCloseStateComponent openCloseStateComponent = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		terminal.SetOpenCloseStateComponent(openCloseStateComponent);
	}

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_OpenCloseState = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		
		m_PowerState = AER_PowerStateComponent.Cast(pOwnerEntity.FindComponent(AER_PowerStateComponent));
	}
}