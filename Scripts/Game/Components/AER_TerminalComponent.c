/*

This entity component needs to be added to a computer to process terminal commands.
This component depends on these components:

  - AER_UsersComponent
  - AER_FilesystemComponent

Idea: perhaps we should create a generic 'command' class that processes the arguments

*/

[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_TerminalComponentClass : ScriptComponentClass
{
}

class AER_TerminalComponent : ScriptComponent
{
	protected AER_UsersComponent m_UsersComponent;
	protected AER_FilesystemComponent m_FilesystemComponent;
	
	protected string m_sTerminalOutputBuffer;
	protected string m_sCommandLineBuffer;

	//------------------------------------------------------------------------------------------------
	void AER_TerminalComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_UsersComponent = AER_UsersComponent.Cast(GetOwner().FindComponent(AER_UsersComponent));
		m_FilesystemComponent = AER_FilesystemComponent.Cast(GetOwner().FindComponent(AER_FilesystemComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	string GetPrompt()
	{
		if(!m_UsersComponent)
			m_UsersComponent = AER_UsersComponent.Cast(GetOwner().FindComponent(AER_UsersComponent));
		if(!m_FilesystemComponent)
			m_FilesystemComponent = AER_FilesystemComponent.Cast(GetOwner().FindComponent(AER_FilesystemComponent));
		
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
	void SetCommandLineBuffer(string commandLine)
	{
		m_sCommandLineBuffer = commandLine;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetCommandLineBuffer()
	{
		return m_sCommandLineBuffer;
	}
	
	//------------------------------------------------------------------------------------------------
	void AddOutputLine(string outputLine)
	{
		m_sTerminalOutputBuffer += outputLine + "\n";
	}
	
	//------------------------------------------------------------------------------------------------
	void ProcessCommandLine()
	{
		m_sTerminalOutputBuffer += GetPrompt() + m_sCommandLineBuffer + "\n";
		
		if (m_sCommandLineBuffer.Length() == 0)
			return;
		
		array<string> commandLineTokens = {};
		m_sCommandLineBuffer.Split(" ", commandLineTokens, true);
		
		string command = commandLineTokens[0];
		
		// remove item[0] which is command itself
		commandLineTokens.RemoveOrdered(0);
		
		switch (command)
		{
			case "cd":
				Print("cd");
				break;
	
			case "ls":
				Print("ls");
				break;

			case "echo":
				Echo(commandLineTokens);
				break;

			case "pwd":
				Pwd();
				break;
			
			case "cat":
				Cat(commandLineTokens);
				break;
				
			default:
				AddOutputLine(string.Format("sh: %1: not found", command));
				break;
		}
		
		SetCommandLineBuffer("");
	}
	
	//------------------------------------------------------------------------------------------------
	void Echo(array<string> commandLineTokens)
	{
		string outputLine = Join(" ", commandLineTokens);
		AddOutputLine(outputLine);
	}
	
	//------------------------------------------------------------------------------------------------
	void Pwd()
	{
		AddOutputLine(m_FilesystemComponent.GetWorkingDirectory());
	}
	
	//------------------------------------------------------------------------------------------------
	void Cat(array<string> commandLineTokens)
	{
		string path = Join(" ", commandLineTokens);
		
		AER_FileObject file = AER_FileObject.Cast(m_FilesystemComponent.GetFilesystemObjectByPath(path));
		if(!file)
		{
			AddOutputLine(string.Format("cat: can't open '%1': No such file or directory", path));
			return;
		}
		
		AddOutputLine(file.GetContent());
	}
	
	//------------------------------------------------------------------------------------------------
	string Join(string delimiter, array<string> stringTokens)
	{
		string joinedStr = "";
		
		foreach (string str : stringTokens)
		{
			joinedStr += str + delimiter;
		}
		
		return joinedStr.Trim();
	}
}