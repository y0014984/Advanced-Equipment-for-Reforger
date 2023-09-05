[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_FilesystemComponentClass : ScriptComponentClass
{
}

class AER_FilesystemComponent : ScriptComponent
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.Object, desc: "Filesystem Objects - File or Directory", params: "conf class=AER_FileObject", category: "Advanced Equipment")];
	protected ref array<ref AER_FilesystemObject> m_mFilesystem;
	
	protected string m_sWorkingDirectory;
	
	//------------------------------------------------------------------------------------------------
	void AddFilesystemObject(string path, AER_FilesystemObject fsObj)
	{
		m_mFilesystem.Insert(fsObj);
	}
	
	//------------------------------------------------------------------------------------------------
	AER_FilesystemObject GetFilesystemObjectByPath(string path)
	{
		array<string> pathTokens = {};
		path.Split("/", pathTokens, true);
		
		return GetFilesystemObjectByPathRecursively(pathTokens);
	}
	
	//------------------------------------------------------------------------------------------------
	private AER_FilesystemObject GetFilesystemObjectByPathRecursively(array<string> pathTokens)
	{
		if (pathTokens.Count() == 0)
			return null;
		
		string currentPathToken = pathTokens[0];
		
		foreach (ref AER_FilesystemObject fsObj : m_mFilesystem)
		{
			if (fsObj.GetName() == currentPathToken)
			{
				if (pathTokens.Count() == 1)
					return fsObj;
				else
				{
					pathTokens.RemoveOrdered(0);
					
					AER_DirectoryObject dirObj = AER_DirectoryObject.Cast(fsObj);
					
					return dirObj.GetFilesystemObjectByPathRecursively(pathTokens);
				}
			}
		}
		
		// returns NULL if not found
		return null;
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
