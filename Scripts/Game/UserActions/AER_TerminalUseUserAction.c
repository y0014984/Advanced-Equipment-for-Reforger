class AER_TerminalUseUserAction : ScriptedUserAction
{
	[Attribute(defvalue: "{5E3EDA618BE7FF1D}UI/layouts/AER_TerminalUI.layout")] // setup the created layout here
	protected ResourceName m_sLayout;

	protected ref Widget m_wDisplay;
	
	private AER_OpenCloseStateComponent m_OpenCloseStateComponent;
	private AER_PowerStateComponent m_PowerStateComponent;
	private AER_FilesystemComponent m_FilesystemComponent;
	private AER_TerminalComponent m_TerminalComponent;
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		return CanBePerformedScript(user);
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!m_OpenCloseStateComponent) // Do nothing if there is no signal manager
		{
			Print("AER: No Open/Close State Component", LogLevel.ERROR);
			
			return false;
		}

		if (!m_OpenCloseStateComponent.IsOpen()) // Check if laptop is open
			return false;
		
		if (!(m_PowerStateComponent.GetPowerState() == EPowerState.ON)) // Check if laptop is powered on
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
		
		AER_TerminalUI terminalUI = AER_TerminalUI.Cast(menu);
		
		terminalUI.SetOpenCloseStateComponent(m_OpenCloseStateComponent);
		terminalUI.SetPowerStateComponent(m_PowerStateComponent);
		terminalUI.SetFilesystemComponent(m_FilesystemComponent);
		terminalUI.SetTerminalComponent(m_TerminalComponent);
	}

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_OpenCloseStateComponent = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		m_PowerStateComponent = AER_PowerStateComponent.Cast(pOwnerEntity.FindComponent(AER_PowerStateComponent));
		m_FilesystemComponent = AER_FilesystemComponent.Cast(pOwnerEntity.FindComponent(AER_FilesystemComponent));
		m_TerminalComponent = AER_TerminalComponent.Cast(pOwnerEntity.FindComponent(AER_TerminalComponent));
	}
}