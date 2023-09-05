enum EFileContentType
{
	TEXT,
	IMAGE,
	EXECUTEABLE
}

[BaseContainerProps()]
class AER_FilesystemObject
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBox, desc: "Name - must be unique in it's parent folder", params: "", category: "Advanced Equipment")]
	protected string m_sName;

	//------------------------------------------------------------------------------------------------
	string GetName()
	{
		return m_sName;
	}
}