enum EFileContentType
{
	TEXT,
	IMAGE,
	EXECUTEABLE
}

[BaseContainerProps(), SCR_BaseContainerCustomTitleField("m_sName")]
class AER_FilesystemObject
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBox, desc: "Name - must be unique in it's parent folder", params: "", category: "Advanced Equipment")]
	protected string m_sName;
	
	[Attribute(defvalue: "1", uiwidget: UIWidgets.Object, desc: "Filesystem Objects - File or Directory", params: "", category: "Advanced Equipment")];
	protected ref AER_Permissions m_Permissions;

	//------------------------------------------------------------------------------------------------
	string GetName()
	{
		return m_sName;
	}
}