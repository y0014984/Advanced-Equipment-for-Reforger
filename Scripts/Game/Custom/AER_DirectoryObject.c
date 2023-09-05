[BaseContainerProps()]
class AER_DirectoryObject : AER_FilesystemObject
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.Object, desc: "Directory - can contain files and directories", params: "", category: "Advanced Equipment")];
	protected ref array<ref AER_FilesystemObject> m_mChildren;

	//------------------------------------------------------------------------------------------------
	AER_FilesystemObject GetFilesystemObjectByPathRecursively(array<string> pathTokens)
	{
		if (pathTokens.Count() == 0)
			return null;
		
		string currentPathToken = pathTokens[0];
		
		foreach (ref AER_FilesystemObject fsObj : m_mChildren)
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
}