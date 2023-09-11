/*

This scripted user action class processes the 'Use' action of the entity. The action can only be performed if:
  - Laptop is 'open'
  - Power state is'on'
  - (No other player is using the laptop) --> needs to be added
  - No other UI is currently displayed

The action is performed on all computers. On the authority (server) the ownership of the laptop is transferred
to the user that performs the action. This user get's the terminal UI displayed on his screen.

*/

class AER_TerminalUseUserAction : ScriptedUserAction
{
	[Attribute(defvalue: "{5E3EDA618BE7FF1D}UI/layouts/AER_TerminalUI.layout")] // setup the created layout here
	protected ResourceName m_sLayout;

	protected ref Widget m_wDisplay;
	
	private AER_OpenCloseStateComponent m_OpenCloseStateComponent;
	private AER_PowerStateComponent m_PowerStateComponent;
	private AER_FilesystemComponent m_FilesystemComponent;
	private AER_TerminalComponent m_TerminalComponent;
	
	private RplComponent m_RplComponent;

	// comment from discord:
	// if HasLocalEffectOnly returns true, it will be executing only on the client where the action has been trigerred 
	// if HasLocalEffectOnly returns false, then it will be exeucted only on the client where the action has been trigered and server --> perhaps wrong
	// if HasLocalEffectOnly returns false and CanBroadcast returns true, then it will be exeucted on client where the action has been trigerred and server and everybody else.    
	
	// comment from discord:
	// if HasLocalEffectOnlyScript() TRUE: actions script run only locally.
	// if FALSE:  "CanBeShownScript()" and "CanBePerformedScript()" run locally on client but "PerformAction()" run on server
	    
	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
	    return false;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBroadcastScript()
	{
	    return true;
	}
	
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
		
		if ((m_TerminalComponent.IsInUse())) // Check if laptop is in use by another player
			return false;
		
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		/*
		This action is performed on all machines but things happen only on authority and 
		on the machine of the action performing user. Authority transfers ownership to user 
		and the user gets displayed the UI.
		*/
		
		PrintFormat("IsMaster(): %1", m_RplComponent.IsMaster()); // IsMaster() does not mean Authority
		PrintFormat("IsProxy(): %1", m_RplComponent.IsProxy());
		PrintFormat("IsOwner(): %1", m_RplComponent.IsOwner());

		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
			
		PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
				
		// Transfer ownership to the action performing user, if this is executed by the authority
		if (m_RplComponent.Role() == RplRole.Authority)
		{
			Print("This is the authority");
			
			if (playerController)
				m_RplComponent.GiveExt(playerController.GetRplIdentity(), false);
			
			m_TerminalComponent.SetInUse(true);
		}
				
		if (playerId == GetGame().GetPlayerController().GetPlayerId())
		{
			Print("This is NOT the authority; This is the action performing user");
			
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
	}

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_OpenCloseStateComponent = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		m_PowerStateComponent = AER_PowerStateComponent.Cast(pOwnerEntity.FindComponent(AER_PowerStateComponent));
		m_FilesystemComponent = AER_FilesystemComponent.Cast(pOwnerEntity.FindComponent(AER_FilesystemComponent));
		m_TerminalComponent = AER_TerminalComponent.Cast(pOwnerEntity.FindComponent(AER_TerminalComponent));
		
		m_RplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}
}