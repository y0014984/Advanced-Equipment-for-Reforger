[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_TerminalComponentClass : ScriptComponentClass
{
}

class AER_TerminalComponent : ScriptComponent
{
	[Attribute("0.5", UIWidgets.EditBox, desc: "BlaBla", params: "0.1 5", category: "my Category")]
	protected float m_fTest;
	
	protected AER_UsersComponent m_UsersComponent;
	protected AER_FilesystemComponent m_FilesystemComponent;
	
	protected string m_sTerminalOutputBuffer;

	//------------------------------------------------------------------------------------------------
	void AER_TerminalComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_UsersComponent = AER_UsersComponent.Cast(GetOwner().FindComponent(AER_UsersComponent));
		m_FilesystemComponent = AER_FilesystemComponent.Cast(GetOwner().FindComponent(AER_FilesystemComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	string GetPrompt()
	{
		string prompt = m_UsersComponent.GetUserLoggedIn() + "@armaOS:" + m_FilesystemComponent.GetWorkingDirectory() + ">";
		return prompt;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetTerminalOutputBuffer()
	{
		return m_sTerminalOutputBuffer;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetTerminalOutputBuffer(string buffer)
	{
		m_sTerminalOutputBuffer = buffer;
	}
	
	//------------------------------------------------------------------------------------------------
	void AddCommandLine(string command)
	{
		m_sTerminalOutputBuffer += GetPrompt() + command + "\n";
	}
}