class AER_LaptopPickUpUserAction : SCR_PickUpItemAction
{
	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return super.CanBeShownScript(user);
	}

	//------------------------------------------------------------------------------------------------	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (GetGame().GetMenuManager().IsAnyDialogOpen()) // Check if Terminal UI is open
			return false;
		
		return super.CanBePerformedScript(user);
 	}
}