[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_FilesystemComponentClass : ScriptComponentClass
{
}

class AER_FilesystemComponent : ScriptComponent
{
	protected ref map<string, ref AER_FilesystemObject> m_mFilesystem;
	
	protected string m_sWorkingDirectory;
	
	//------------------------------------------------------------------------------------------------
	void AER_FilesystemComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_mFilesystem = new map<string, ref AER_FilesystemObject>();
		
		AER_FilesystemObject root = new AER_FilesystemObject(EFilesystemObjectType.DIRECTORY, EFileContentType.TEXT, "");
		
		SetFilesystemObject("/", root);
		SetWorkingDirectory("/");
	}
	
	//------------------------------------------------------------------------------------------------
	void SetFilesystemObject(string path, AER_FilesystemObject fsObj)
	{
		m_mFilesystem.Set(path, fsObj);
		
		PrintFormat("New Filesystem Obj Count: %1", m_mFilesystem.Count());
	}
	
	//------------------------------------------------------------------------------------------------
	AER_FilesystemObject GetFilesystemObject(string path)
	{
		// returns NULL if not found
		return m_mFilesystem.Get(path);
	}
	
	//------------------------------------------------------------------------------------------------
	void SetWorkingDirectory(string path)
	{
		m_sWorkingDirectory = path;
	}

	//------------------------------------------------------------------------------------------------
	string GetWorkingDirectory()
	{
		return m_sWorkingDirectory;
	}
}
