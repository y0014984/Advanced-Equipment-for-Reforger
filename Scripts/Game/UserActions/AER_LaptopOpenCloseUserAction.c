class AER_LaptopOpenCloseUserAction : ScriptedUserAction
{
	[Attribute( defvalue: "Laptop Top", uiwidget: UIWidgets.EditBox, desc: "Signal index of LaptopTop Cover" )]
	private string m_sSignalName; // string for pairing with the user action
	private int m_iSignalIndex = -1;

	const float MAX_SIGNAL_VALUE = 90;

	//! Signal manager to pass signals into procedural animation
	private SignalsManagerComponent m_SignalsManager;
	
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
		if (!m_SignalsManager) // Do nothing if there is no signal manager
		{
			Print("AER: No Signals Manager Component", LogLevel.ERROR);
			
			return false;
		}
		
		if (!m_OpenCloseState) // Do nothing if there is no signal manager
		{
			Print("AER: No Open/Close State Component", LogLevel.ERROR);
			
			return false;
		}

		if (m_iSignalIndex < 0) // Check if signal index is valid
		{
			m_iSignalIndex = m_SignalsManager.FindSignal(m_sSignalName);
			
			return false;
		}
		
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return true;
	}

	//---------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		// this line alternates the targetValue between 0 and MAX_SIGNAL_VALUE
		float targetValue = Math.AbsFloat((m_SignalsManager.GetSignalValue(m_iSignalIndex)) - MAX_SIGNAL_VALUE);
		
		m_SignalsManager.SetSignalValue(m_iSignalIndex, targetValue);
		
		m_OpenCloseState.ToggleOpenCloseState();
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		if((m_SignalsManager.GetSignalValue(m_iSignalIndex)) == 0)
		{
			outName = "Close";
		} else
		{
			outName = "Open";
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_SignalsManager = SignalsManagerComponent.Cast(pOwnerEntity.FindComponent(SignalsManagerComponent));
		
		m_OpenCloseState = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		
		m_PowerState = AER_PowerStateComponent.Cast(pOwnerEntity.FindComponent(AER_PowerStateComponent));
	}
}