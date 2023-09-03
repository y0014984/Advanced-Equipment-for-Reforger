[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_FilesystemComponentClass : ScriptComponentClass
{
}

class AER_FilesystemComponent : ScriptComponent
{
	protected bool m_bIsOpen = true;
	
	//------------------------------------------------------------------------------------------------
	void ToggleOpenCloseState()
	{
		if (m_bIsOpen)
			m_bIsOpen = false;
		else
			m_bIsOpen = true;
		
		PrintFormat("AER - Open/Close-State toggled - %1", m_bIsOpen);
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsOpen()
	{
		return m_bIsOpen;
	}
}
