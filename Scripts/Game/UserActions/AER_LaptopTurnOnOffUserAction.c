class AER_LaptopTurnOnOffUserAction : ScriptedUserAction
{
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
		{
			return false;
		}
		
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return true;
	}

	//---------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if(m_PowerState.GetPowerState() == EPowerState.OFF)
		{
			m_PowerState.TurnOn();
		} else
		{
			m_PowerState.TurnOff();
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		if(m_PowerState.GetPowerState() == EPowerState.OFF)
		{
			outName = "Turn On";
		} else
		{
			outName = "Turn Off";
		}
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_OpenCloseState = AER_OpenCloseStateComponent.Cast(pOwnerEntity.FindComponent(AER_OpenCloseStateComponent));
		
		m_PowerState = AER_PowerStateComponent.Cast(pOwnerEntity.FindComponent(AER_PowerStateComponent));
	}
}